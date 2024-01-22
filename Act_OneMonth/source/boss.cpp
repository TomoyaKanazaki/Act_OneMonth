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

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f);
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
	//タイプの設定
	SetType(TYPE_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	//m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// サイズを設定
	m_size = BOSS_SIZE;

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
	// カメラ外だと抜ける
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		return;
	}

	// プレイヤーを見る
	RotateToPlayer();

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
