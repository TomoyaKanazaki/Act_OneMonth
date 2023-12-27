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
#include "texture.h"

//==========================================
//  静的メンバ変数
//==========================================
const float CEnemy_Normal::m_fScope = 300.0f;

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Normal::CEnemy_Normal()
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
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//初期化処理
	HRESULT hr = CEnemy::Init();

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
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
	//移動した距離を保存
	m_fMove += m_move.x;

	//移動距離
	if (fabsf(m_fMove) >= m_fScope)
	{
		m_fSpeed *= -1.0f;
		m_fMove = 0.0f;
	}

	//デルタタイムの取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	//移動
	m_move.x = m_fSpeed * m_fDeltaTime;

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
