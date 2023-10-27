//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "motion.h"
#include "layer.h"
#include "gamemanager.h"
#include "orbit.h"
#include "camera.h"
#include "gametime.h"
#include "arrow.h"
#include "marker.h"
#include "slice.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CPlayer::m_fHitLength = 25.0f;

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject_Char(nPriority)
{
	m_CenterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecStick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_bDash = false;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pArrow = nullptr;
	m_State = NEUTRAL;
	m_oldState = NEUTRAL;
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(void)
{
	//タイプの設定
	SetType(TYPE_PLAYER);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	//中心座標を設定
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//経過時間を取得する
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//ゲーム状態の取得
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		m_fDeltaTime *= 0.0f;
	}

	//ダッシュ時の処理
	Hit();

	//ダッシュの処理
	Dash();

	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		//ジャンプ!
		Jump();

		//移動の処理
		Move();
	}

	//回転の処理
	Rotate();

	//移動制限
	Limit();

	//重力
	Gravity();

	//モーション
	Motion();

	//殺す
	Death();

	//前回座標に保存
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//中心座標を設定
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//デバッグ表示
	CManager::GetManager()->GetDebugProc()->Print("移動量 ( %f, %f )\n", m_move.x, m_move.y);
	CManager::GetManager()->GetDebugProc()->Print("座標 ( %f, %f )\n", m_pos.x, m_pos.y);

	CObject_Char::Update();

#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_Q))
	{
		m_State = NEUTRAL;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_1))
	{
		m_State = DEATH;
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  オブジェクト生成処理
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CPlayer;
	}

	//各種情報の保存
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//ポインタを返す
	return pPlayer;
}

//==========================================
//  モーションの更新
//==========================================
void CPlayer::Motion(void)
{
	//状態が切り替わった瞬間にモーションを切り替える
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE && CGameManager::GetOldState() == CGameManager::STATE_NORMAL)
	{
		m_State = IAI;
	}
	if (CGameManager::GetState() == CGameManager::STATE_NORMAL && CGameManager::GetOldState() != CGameManager::STATE_NORMAL)
	{
		m_State = NEUTRAL;
	}

	//状態更新
	if (m_State == DEATH || CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		//更新しない
	}
	else if (!m_bRand) //着地してない状態
	{
		if (m_move.y > 0.0f)
		{
			m_State = JUMP;
		}
		else
		{
			m_State = FALL;
		}
	}
	else if (m_move.x != 0.0f) //移動している状態
	{
		m_State = WALK;
	}
	else //上記のどれでもない状態
	{
		m_State = NEUTRAL;
	}

	//モーションを更新
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case IAI:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		case JUMP:
			m_pMotion->Set(CMotion::PLAYER_JUMP);
			break;
		case FALL:
			m_pMotion->Set(CMotion::PLAYER_FALL);
			break;
		case WALK:
			m_pMotion->Set(CMotion::PLAYER_WALK);
			break;
		case NEUTRAL:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
			break;
		case DEATH:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
		}
	}

	//現在の状態を保存
	m_oldState = m_State;
}

//==========================================
//  移動制限
//==========================================
void CPlayer::Limit(void)
{
	//X座標の制限
	if (CGameManager::GetState() != CGameManager::STATE_START && CGameManager::GetState() != CGameManager::STATE_END)
	{
		if (m_pos.x < -2250.0f)
		{
			m_pos.x = -2250.0f;
		}
		if (m_pos.x > 2250.0f)
		{
			m_pos.x = 2250.0f;
		}
	}

	//Y座標の制限
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.y > 600.0f)
	{
		m_pos.y = 600.0f;
	}
	if (m_pos.y <= 0.0f)
	{
		m_bRand = true;
	}

	//集中状態中の移動制限
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		//基準点の取得
		D3DXVECTOR3 pos = CGameManager::GetCamera()->GetPosR();

		//基準点からプレイヤーのベクトルを取得
		D3DXVECTOR3 vec = pos - m_pos;

		//基準点から離れていたら引き戻す
		if (vec.x < -CAMERA_WIDTH)
		{
			m_pos.x = pos.x + CAMERA_WIDTH;
		}
		if (vec.x > CAMERA_WIDTH)
		{
			m_pos.x = pos.x - CAMERA_WIDTH;
		}
		if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
		{
			if (vec.y < -CAMERA_HEIGHT)
			{
				m_pos.y = pos.y + CAMERA_HEIGHT;
			}
		}
	}
}

//==========================================
//  移動の処理
//==========================================
void CPlayer::Move(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_State != DEATH)
	{
		//パッド移動量を取得
		move = CManager::GetManager()->GetJoyPad()->GetStickL(0.1f);

		//キーボード移動量の取得
		if (move.x == 0.0f)
		{
			move = CManager::GetManager()->GetKeyboard()->GetWASD();
		}
	}

	//自動歩行
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		move.x = 1.0f;
		move.y = 0.0f;
	}

	//移動量の適用
	m_move.x = move.x * PLAYER_SPEED;

	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//移動量を適用
	m_pos += m_move * m_fDeltaTime;
}

//==========================================
//  回転処理
//==========================================
void CPlayer::Rotate(void)
{
	//移動してない時は回転しない
	if (m_move.x == 0.0f)
	{
		return;
	}

	//ローカル変数宣言
	float fRotMove = m_rot.y; //現在の角度
	float fRotDest = 0.0f; //目標の角度
	float fRotDiff = 0.0f; //目標と現在の角度の差

	//右に進む時は右を向く
	if (m_move.x > 0.0f)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}

	//左に進むときは左を向く
	if (m_move.x < 0.0f)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//移動補正
	fRotDiff = fRotDest - fRotMove;	//目標までの移動方向の差分

	//角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//方向転換
	m_rot.y += fRotDiff * 0.2f;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}

//==========================================
//  ジャンプの処理
//==========================================
void CPlayer::Jump(void)
{
	if (m_State == DEATH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

	//着地フラグがオフの時
	if (!m_bRand)
	{
		return;
	}

	//ジャンプ!
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		m_move.y = JUMP_MOVE;
		m_bRand = false;
	}
}

//==========================================
//  重力の処理
//==========================================
void CPlayer::Gravity(void)
{
	//重力の無効条件
	if (m_pos.y <= 0.0f)
	{
		m_move.y = 0.0f;
		return;
	}
	else if (m_move.y <= -JUMP_MOVE)
	{
		m_move.y = -JUMP_MOVE;
		return;
	}

	//集中状態の時
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		m_move.y = 0.0f;
		return;
	}

	//移動量の減少
	m_move.y -= GRAVITY;
}

//==========================================
//  ダッシュの処理
//==========================================
void CPlayer::Dash(void)
{
	//ダッシュフラグのリセット
	m_bDash = false;

	//集中状態でのみ発動
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		if (m_pArrow != nullptr)
		{
			m_pArrow->Uninit();
			m_pArrow = nullptr;
		}
		return;
	}

	//矢印を生成
	if (m_pArrow == nullptr)
	{
		m_pArrow = CArrow::Create();
	}

	//パッドの入力情報を取得
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);

	//入力角度を算出
	float fAngle = atan2f(move.y, move.x);
	m_move = D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);

	if (CManager::GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_RB))
	{
		m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
		m_bDash = true;
		m_bRand = false;
	}

	//デバッグ用ダッシュ
#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_UP))
	{
		m_pos.y += DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_DOWN))
	{
		m_pos.y -= DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RIGHT))
	{
		m_pos.x += DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		m_pos.x -= DASH_DISTANCE;
		m_bDash = true;
	}
#endif

	//移動制限
	Limit();

	//移動がなかった場合はダッシュをキャンセル
	if (m_oldPos == m_pos)
	{
		m_bDash = false;
	}
}

//==========================================
//  軌跡の発生
//==========================================
void CPlayer::Orbit(void)
{
	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//モデル情報の取得
	D3DXMATRIX mtxWorld = m_ppModel[3]->GetMtx();
	D3DXVECTOR3 pos = m_ppModel[3]->GetPos();
	D3DXVECTOR3 oldpos;

	//現在座標を抽出
	pos = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//前回座標の反映
	D3DXMatrixTranslation(&mtxTrans, m_oldposModel.x, m_oldposModel.y, m_oldposModel.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//現在座標を抽出
	oldpos = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	//軌跡を生成
	COrbit::Create(oldpos, pos);
}

//==========================================
//  敵を巻き込む処理
//==========================================
void CPlayer::Hit(void)
{
	//ダッシュしてない場合
	if (!m_bDash)
	{
		return;
	}

	//軌跡を発生
	Orbit();

	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //敵の場合
			{
				if (pObj->GetObjState() == CObject::NORMAL)
				{
					//対象の座標を取得する
					D3DXVECTOR3 pos = pObj->GetPos();

					//前回座標との距離を計算する
					D3DXVECTOR3 vecToPosOld = m_oldposModel - pos;
					float fLength = sqrtf(vecToPosOld.x * vecToPosOld.x + vecToPosOld.y * vecToPosOld.y);

					//今回座標との距離を加算する
					D3DXVECTOR3 vecToPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43) - pos;
					fLength += sqrtf(vecToPos.x * vecToPos.x + vecToPos.y * vecToPos.y);

					//判定内の判定を取る
					if (HIT_RANGE >= fLength)
					{
						CMarker::Create(pos);
						CSlice::Create(pos, m_size * 3.0f);
						pObj->SetState(CObject::MARKING);
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  殺す
//==========================================
void CPlayer::Death(void)
{
	//通常状態でしか死なない
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //敵の場合
			{
				//対象の座標を取得する
				D3DXVECTOR3 pos = pObj->GetPos();

				//ベクトルの算出
				D3DXVECTOR3 vec = m_CenterPos - pos;

				//ベクトルの大きさを比較する
				if (m_fHitLength * m_fHitLength >= (vec.x * vec.x + vec.y * vec.y))
				{
					m_State = DEATH;
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
