//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "enemy_normal.h"

//==========================================
//  静的メンバ変数
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_type = NONE;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
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

	Release();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
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
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//変数宣言
	CEnemy* pEnemy = nullptr;

	//メモリを確保[
	if (pEnemy == nullptr)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;

		default:
			pEnemy = nullptr;
			break;
		}
	}

	//値を設定
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//初期化処理
	pEnemy->Init();

	return nullptr;
}
