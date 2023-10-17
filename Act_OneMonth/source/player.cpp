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
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
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
	
	//モーション情報にモデルを追加する
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);

	//腕を前方に向ける
	m_ppModel[3]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

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

	//前回座標を保存
	m_oldPos = m_pos;

	//移動の処理
	Move();

	//ダッシュの処理
	Dash();

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
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw()
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
	m_move.x = move.x * PLAYER_SPEED * m_fDeltaTime;

	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//移動量を適用
	m_pos += m_move;
}

//==========================================
//  ダッシュの処理
//==========================================
void CPlayer::Dash(void)
{
	//パッドの入力情報を取得
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.3f);

	//入力角度を算出
	float fAngle = atan2f(move.y, move.x);

	if (m_vecStick == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (move.x != 0.0f || move.y != 0.0f)
		{
			m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
			COrbit::Create(m_oldPos, m_pos, PLAYER_HEIGHT);
			Hit();
		}
	}

	//今回の入力情報を保存する
	m_vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.2f);

	//入力角度を保存する
	m_fDashAngle = fAngle;

	//デバッグ用ダッシュ
#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		m_pos.x += DASH_DISTANCE;
		COrbit::Create(m_oldPos, m_pos, PLAYER_HEIGHT);
		Hit();
	}
#endif
}

//==========================================
//  敵を巻き込む処理
//==========================================
void CPlayer::Hit(void)
{
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
