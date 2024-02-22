//==========================================
//
//  提灯お化け(enemy_blade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_blade.h"
#include "model.h"
#include "motion.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LANTERN_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MAX_LIFE = 3.0f;
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 中心座標とオブジェクト座標の差
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Blade::CEnemy_Blade()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Blade::~CEnemy_Blade()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Blade::Init(void)
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
	CalcHitLength(m_size);

	// 体力を設定
	m_fLife = MAX_LIFE;

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Blade::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Blade::Update(void)
{
	// プレイヤーを向く
	RotateToPlayer();

	// 被撃時の処理
	Attacked();

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Blade::Draw(void)
{
	CEnemy::Draw();
}
