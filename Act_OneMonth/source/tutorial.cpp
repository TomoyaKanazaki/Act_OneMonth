//==========================================
//
//  操作方法(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "enemymanager.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 TUTORIAL_SIZE = D3DXVECTOR3(250.0f, 70.0f, 0.0f); // ポリゴンサイズ
	const D3DXVECTOR3 TUTORIAL_POS = D3DXVECTOR3(130.0f, 50.0f, 0.0f); // ポリゴン座標
}

//==========================================
//  コンストラクタ
//==========================================
CTutorial::CTutorial(int nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CTutorial::~CTutorial()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CTutorial::Init(void)
{
	// 位置を設定
	m_pos = TUTORIAL_POS;

	// 大きさを設定
	m_size = TUTORIAL_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL));

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorial::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorial::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTutorial* CTutorial::Create()
{
	// インスタンス生成
	CTutorial* pTutorial = new CTutorial;

	// NULLチェック
	if (pTutorial == nullptr) { return nullptr; }

	// 初期化処理
	pTutorial->Init();

	return pTutorial;
}
