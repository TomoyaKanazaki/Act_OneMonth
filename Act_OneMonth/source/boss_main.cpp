//==========================================
//
//  ボス敵のクラス(boss_main.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"
#include "layer.h"
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CBoss_Main::CBoss_Main(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CBoss_Main::~CBoss_Main()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss_Main::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::BOSS_MAIN);

	return CEnemy::Init();
}

//==========================================
//  終了処理
//==========================================
void CBoss_Main::Uninit(void)
{
	CGameManager::KillBoss();
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss_Main::Update(void)
{
	CManager::GetManager()->GetDebugProc()->Print("ボス座標 ( %f, %f )\n", m_pos.x, m_pos.y);
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBoss_Main::Draw(void)
{
	CEnemy::Draw();
}
