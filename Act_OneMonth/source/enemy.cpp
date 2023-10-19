//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "enemy_normal.h"

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

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

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

	return nullptr;
}
