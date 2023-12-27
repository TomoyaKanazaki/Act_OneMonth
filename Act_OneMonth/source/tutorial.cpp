//==========================================
//
//  チュートリアル(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CTutorial::mc_fHeight = 80.0f;
const D3DXVECTOR3 CTutorial::mc_size = D3DXVECTOR3(405.0f, 60.0f, 0.0f);

//==========================================
//  コンストラクタ
//==========================================
CTutorial::CTutorial(int nPriority) : CObject3D(nPriority)
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
	//プレイヤーの座標を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//高さを調整する
	pos.y += mc_fHeight;

	//位置を適用する
	m_pos = pos;

	//サイズを設定する
	m_size = mc_size;

	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTutorial::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorial::Update(void)
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//高さを調整する
	pos.y += mc_fHeight;

	//位置を適用する
	m_pos = pos;

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorial::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTutorial* CTutorial::Create(void)
{
	//インスタンス生成
	CTutorial* pTutorial = new CTutorial;

	//初期化処理
	pTutorial->Init();

	//テクスチャを割り当て
	pTutorial->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_00));

	return pTutorial;
}

//==========================================
//  チュートリアルを次に進める
//==========================================
void CTutorial::NextProgress(void)
{
	//終わる
	if (m_pTexture == CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_02))
	{
		Uninit();
	}

	//進める
	if (m_pTexture == CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_01))
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_02));
	}

	//進める
	if (m_pTexture == CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_00))
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL_01));
	}
}
