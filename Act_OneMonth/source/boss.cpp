//==========================================
//
//  ボスクラス(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "gametime.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f); // ボスの大きさ
	const float MAX_LIFE = 10.0f; // 体力の最大値
	const float DAMAGE = 1.0f; // 一回の攻撃から受けるダメージ量
	const float INVINCIBLE_TIME = 0.1f; // 無敵時間
}

//==========================================
//  コンストラクタ
//==========================================
CBoss::CBoss(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss::Init(void)
{
	// タイプの設定
	SetType(TYPE_ENEMY);

	// 階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	// モーション情報にモデルを渡す
	//m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// サイズを設定
	m_size = BOSS_SIZE;

	// 体力を設定
	m_fLife = MAX_LIFE;

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBoss::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss::Update(void)
{
	// 被撃時の処理
	Attacked();

	// プレイヤーを見る
	RotateToPlayer();

	// デバッグ表示
	DebugProc::Print("ボスの体力 : %f\n", m_fLife);

	// 更新
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  被撃時の処理
//==========================================
void CBoss::Attacked()
{
	// 状態毎の処理
	if (m_ObjState == ATTACKED)
	{
		m_fLife -= DAMAGE;
		m_ObjState = INVINCIBLE;
		WhiteOut(true);
		return;
	}
	else if (m_ObjState == INVINCIBLE)
	{
		// 時間の加算
		m_fInvincible += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// 無敵時間の解除
		if (m_fInvincible >= INVINCIBLE_TIME)
		{
			m_ObjState = NORMAL;
			m_fInvincible = 0.0f;
			WhiteOut(false);
		}
	}
}
