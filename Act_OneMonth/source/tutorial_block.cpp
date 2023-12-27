//==========================================
//
//  チュートリアル状態での壁(tutorial_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_block.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CTutorialBlock::CTutorialBlock()
{

}

//==========================================
//  デストラクタ
//==========================================
CTutorialBlock::~CTutorialBlock()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTutorialBlock::Init(void)
{
	CObject3D::Init();
	return E_NOTIMPL;
}

//==========================================
//  終了処理
//==========================================
void CTutorialBlock::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorialBlock::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorialBlock::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTutorialBlock* CTutorialBlock::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTutorialBlock* pBlock = new CTutorialBlock;

	// NULLチェック
	if (pBlock == nullptr) { return nullptr; }

	// 値を設定
	pBlock->m_pos = pos;

	// 初期化処理
	pBlock->Init();

	//テクスチャを割り当て
	pBlock->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::OHUDA));

	// 値を返す
	return pBlock;
}
