//==========================================
//
//  基本のブロッククラス(map_cube.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "map_cube.h"
#include "model.h"

//==========================================
//  コンストラクタ
//==========================================
CMap_Cube::CMap_Cube()
{

}

//==========================================
//  デストラクタ
//==========================================
CMap_Cube::~CMap_Cube()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMap_Cube::Init(void)
{
	//タイプの設定
	SetType(TYPE_FIELD);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::CUBE_LAYER);

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

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CMap_Cube::Uninit(void)
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

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CMap_Cube::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CMap_Cube::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CMap_Cube* CMap_Cube::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CMap_Cube* pCube  =nullptr;

	//メモリを確保
	if (pCube == nullptr)
	{
		pCube = new CMap_Cube;
	}
	else
	{
		return nullptr;
	}

	//値を設定
	pCube->m_pos = pos;

	//初期化処理
	pCube->Init();

	return nullptr;
}
