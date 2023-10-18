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

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_vecStick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_bDash = false;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	//モデル用のメモリの確保
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//必要なモデルを生成
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//空にする
		m_ppModel[nCnt] = NULL;

		//親が存在しない場合
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//モーション情報の生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}
	
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	//モデルのポインタを破棄
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//モーションのポインタを破棄
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//経過時間を取得する
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//ダッシュ時の処理
	Hit();

	//ダッシュの処理
	Dash();

	if (!m_bDash)
	{
		//ジャンプ!
		Jump();

		//移動の処理
		Move();

		//回転の処理
		Rotate();
	}

	//移動制限
	Limit();

	//実体を移動する
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	//モーションを更新する
	m_pMotion->Update();

	//重力
	Gravity();

	//前回座標に保存
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//デバッグ表示
	CManager::GetManager()->GetDebugProc()->Print("移動量 ( %f, %f )\n", m_move.x, m_move.y);
	CManager::GetManager()->GetDebugProc()->Print("座標 ( %f, %f )\n", m_pos.x, m_pos.y);
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw(void)
{

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
//  移動制限
//==========================================
void CPlayer::Limit(void)
{
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_bRand = true;
	}
}

//==========================================
//  移動の処理
//==========================================
void CPlayer::Move(void)
{
	//パッド移動量を取得
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickL(0.1f);

	//キーボード移動量の取得
	if (move.x == 0.0f)
	{
		move = CManager::GetManager()->GetKeyboard()->GetWASD();
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

	//パッドの入力情報を取得
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.3f);

	//入力角度を算出
	float fAngle = atan2f(move.y, move.x);

	if (m_vecStick == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (move.x != 0.0f || move.y != 0.0f)
		{
			m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
			m_bDash = true;
		}
	}

	//今回の入力情報を保存する
	m_vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.2f);

	//入力角度を保存する
	m_fDashAngle = fAngle;

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
	COrbit::Create(oldpos, pos, PLAYER_HEIGHT);
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
				//対象の座標を取得する
				D3DXVECTOR3 pos = pObj->GetPos();

				//前回座標との距離を計算する
				D3DXVECTOR3 vecToPosOld = m_oldPos - pos;
				float fLength = sqrtf(vecToPosOld.x * vecToPosOld.x + vecToPosOld.y * vecToPosOld.y);

				//今回座標との距離を加算する
				D3DXVECTOR3 vecToPos = m_pos - pos;
				fLength += sqrtf(vecToPos.x * vecToPos.x + vecToPos.y * vecToPos.y);

				//判定内の判定を取る
				if (HIT_RANGE >= fLength)
				{
					pObj->Uninit();
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
