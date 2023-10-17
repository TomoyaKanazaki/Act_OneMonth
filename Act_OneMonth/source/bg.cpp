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
CBg::CBg()
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
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CBg::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBg::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBg::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  生成処理
//==========================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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

	//初期化
	pBG->Init();

	//テクスチャを割り当てる
	pBG->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::BG));

	return pBG;
}
