//==========================================
//
//  通常の敵のクラス(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"
#include "manager.h"
#include "gametime.h"

//==========================================
//  静的メンバ変数
//==========================================
const float CEnemy_Normal::m_fScope = 300.0f;

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{
	m_fMove = 0.0f;
	m_fSpeed = 100.0f;
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
	m_pLayer = CLayer::Set(CLayer::ENEMY_NORMAL);

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
	//デルタタイムの取得
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//移動
	m_move.x = m_fSpeed * m_fDeltaTime;

	//移動した距離を保存
	m_fMove += m_move.x;

	//移動距離
	if (fabsf(m_fMove) >= m_fScope)
	{
		m_fSpeed *= -1.0f;
		m_fMove = 0.0f;
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
