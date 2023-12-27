//==========================================
//
//  消える敵(enemy_invincible.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_invincible.h"
#include "manager.h"
#include "texture.h"
#include "gametime.h"
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Invincible::CEnemy_Invincible()
{
	m_fClear = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Invincible::~CEnemy_Invincible()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Invincible::Init(void)
{
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//初期化処理
	HRESULT hr = CEnemy::Init();

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_04));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Invincible::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Invincible::Update(void)
{
	//色の更新
	if (CGameManager::GetState() == CGameManager::STATE_NORMAL && OnScreen())
	{
		m_fClear += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;
	}
	float fAlpha = (sinf(m_fClear) + 1.0f) * 0.5f;
	D3DXCOLOR col = GetCol();
	col.a = fAlpha;
	SetCol(col);

	//色が薄いときは無敵
	if (col.a <= 0.3f)
	{
		SetType(CObject::TYPE_BOSS);
	}
	else
	{
		SetType(CObject::TYPE_ENEMY);
	}

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Invincible::Draw(void)
{
	CEnemy::Draw();
}
