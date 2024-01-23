//==========================================
//
//  提灯お化け(enemy_lantern.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_lantern.h"
#include "model.h"
#include "motion.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LANTERN_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MAX_LIFE = 10.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Lantern::CEnemy_Lantern()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Lantern::~CEnemy_Lantern()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Lantern::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_LANTERN);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// サイズを設定
	m_size = LANTERN_SIZE;

	// 体力を設定
	m_fLife = MAX_LIFE;

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Lantern::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Lantern::Update(void)
{
	// プレイヤーを向く
	RotateToPlayer();

	// 被撃時の処理
	Attacked();

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Lantern::Draw(void)
{
	CEnemy::Draw();
}
