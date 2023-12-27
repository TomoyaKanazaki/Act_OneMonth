//==========================================
//
//  チュートリアル状態での壁(tutorial_wall.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_wall.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CTutorialWall::CTutorialWall()
{

}

//==========================================
//  デストラクタ
//==========================================
CTutorialWall::~CTutorialWall()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTutorialWall::Init(void)
{
	//値を設定
	m_pos = D3DXVECTOR3(-1000.0f, 100.0f, 0.0f);
	m_size = D3DXVECTOR3(30.0f, 120.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObject3D::Init();

	return E_NOTIMPL;
}

//==========================================
//  終了処理
//==========================================
void CTutorialWall::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorialWall::Update(void)
{
	m_rot.y += 0.02f;
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorialWall::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D::Draw();

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  生成処理
//==========================================
CTutorialWall* CTutorialWall::Create()
{
	// インスタンス生成
	CTutorialWall* pBlock = new CTutorialWall;

	// NULLチェック
	if (pBlock == nullptr) { return nullptr; }

	// 初期化処理
	pBlock->Init();

	//テクスチャを割り当て
	pBlock->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::OHUDA));

	// 値を返す
	return pBlock;
}
