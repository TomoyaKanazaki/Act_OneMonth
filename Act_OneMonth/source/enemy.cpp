//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "boss_main.h"
#include "enemy_normal.h"
#include "enemy_homing.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject_Char(nPriority)
{
	m_type = NONE;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	return CObject_Char::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	//集中状態の時スローになる
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		m_move *= 0.1f;
	}

	//移動量の適用
	if (m_ObjState == MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_DASH)
		{
			Uninit();
			return;
		}
	}
	else
	{
		m_pos += m_move;
	}

	CObject_Char::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//変数宣言
	CEnemy* pEnemy = nullptr;

	//メモリを確保[
	if (pEnemy == nullptr)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;

		case HOMING:
			pEnemy = new CEnemy_Homing;
			break;

		case BOSS_MAIN:
			pEnemy = new CBoss_Main;
			break;

		default:
			pEnemy = nullptr;
			break;
		}
	}

	//値を設定
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//初期化処理
	pEnemy->Init();

	return pEnemy;
}
