//==========================================
//
//  エネミーマネージャ(enemymanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemyManager::CEnemyManager() :
	m_pInfo(nullptr),
	m_pBoss(nullptr),
	m_bPopFrag(false)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  初期化処理
//==========================================
void CEnemyManager::Init()
{
	// 情報の読み込み
	Load();
}

//==========================================
//  終了処理
//==========================================
void CEnemyManager::Uninit()
{
	// 設置情報の破棄
	if (m_pInfo != nullptr)
	{
		delete m_pInfo;
		m_pInfo = nullptr;
	}

	// 自身の削除
	delete this;
}

//==========================================
//  更新処理
//==========================================
void CEnemyManager::Update()
{
	// ボスの出現
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		if (!m_bPopFrag)
		{
			m_pBoss = CEnemy::Create(D3DXVECTOR3(1900.0f, 30.0f, 0.0f), CEnemy::BOSS
			
			);
			m_bPopFrag = true;
		}
	}

	// デバッグ専用処理
#ifdef _DEBUG

	// 提灯お化け
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_NUMPAD1))
	{
		CEnemy::Create(D3DXVECTOR3(-2000.0f, 30.0f, 0.0f), CEnemy::LANTERN);
	}

#endif
}

//==========================================
//  読み込み処理
//==========================================
void CEnemyManager::Load()
{

}

//==========================================
//  生成処理
//==========================================
CEnemyManager* CEnemyManager::Create()
{
	// インスタンス生成
	CEnemyManager* manager = new CEnemyManager;

	// NULLチェック
	if (manager == nullptr) { return nullptr; }

	// 初期化処理
	manager->Init();

	// 値を返す
	return manager;
}
