//==========================================
//
//  通常の敵のクラス(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Normal::~CEnemy_Normal()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Normal::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	return CEnemy::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Normal::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Normal::Update(void)
{
	//スクリーン外なら更新しない
	if (!OnScreen())
	{
		return;
	}

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
