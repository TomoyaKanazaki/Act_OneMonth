//==========================================
//
//  停止する敵(enemy_stop.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_stop.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Stop::CEnemy_Stop()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Stop::~CEnemy_Stop()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Stop::Init(void)
{
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//初期化処理
	HRESULT hr = CEnemy::Init();

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_02));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Stop::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Stop::Update(void)
{
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Stop::Draw(void)
{
	CEnemy::Draw();
}
