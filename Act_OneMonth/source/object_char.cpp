//==========================================
//
//  オブジェクトキャラクター(object_char.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_char.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "motion.h"

//==========================================
//  コンストラクタ
//==========================================
CObject_Char::CObject_Char(int nPriority) : CObject(nPriority)
{
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
	m_mtxWorld = {};
}

//==========================================
//  デストラクタ
//==========================================
CObject_Char::~CObject_Char()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject_Char::Init(void)
{
	//モデル用のメモリの確保
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel * [m_pLayer->nNumModel];
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
void CObject_Char::Uninit(void)
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
void CObject_Char::Update(void)
{
	//モーションを更新する
	m_pMotion->Update();
}

//==========================================
//  描画処理
//==========================================
void CObject_Char::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Draw();
			}
		}
	}
}
