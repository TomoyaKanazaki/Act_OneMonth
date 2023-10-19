//==========================================
//
//  背景クラス(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CBg::CBg(int nPriority) : CObject_Mesh(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CBg::~CBg()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBg::Init(void)
{
	return CObject_Mesh::Init();
}

//==========================================
//  終了処理
//==========================================
void CBg::Uninit(void)
{
	CObject_Mesh::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBg::Update(void)
{
	CObject_Mesh::Update();
}

//==========================================
//  描画処理
//==========================================
void CBg::Draw(void)
{
	CObject_Mesh::Draw();
}

//==========================================
//  生成処理
//==========================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumPorygon)
{
	//インスタンス生成
	CBg* pBG = nullptr;

	//メモリを確保
	if (pBG == nullptr)
	{
		pBG = new CBg;
	}
	else
	{
		return nullptr;
	}

	//値を保存
	pBG->m_pos = pos;
	pBG->m_size = size;
	pBG->m_Mesh.nNumMesh_U = nNumPorygon;
	pBG->m_Mesh.nNumMesh_V = 1;
	pBG->m_rot.x = -D3DX_PI * 0.5f;

	//初期化
	pBG->Init();

	//テクスチャを割り当てる
	pBG->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::BG));

	return pBG;
}
