//==========================================
//
//  ボス敵のクラス(boss_main.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"
#include "layer.h"
#include "gamemanager.h"
#include "boss_sub.h"
#include "texture.h"
#include "gametime.h"
#include "player.h"

//==========================================
//  コンストラクタ
//==========================================
CBoss_Main::CBoss_Main()
{
	m_state = DEFAULT;
	m_fMove = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CBoss_Main::~CBoss_Main()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss_Main::Init(void)
{
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//初期化
	HRESULT hr = CEnemy::Init();

	//ボスフラグ
	SetType(TYPE_BOSS);

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_01));
	SetAnim(4, 10, true, TYPE_U);
	SetCol(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBoss_Main::Uninit(void)
{
	CGameManager::KillBoss();
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss_Main::Update(void)
{
	//Y座標の制限
	if (m_pos.y < 120.0f)
	{
		m_pos.y = 120.0f;
	}
	if (m_pos.y > 200.0f)
	{
		m_pos.y = 200.0f;
	}

	//子分を生成
	if (m_state == DEFAULT && !m_bSub)
	{
		//おともの生成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 50.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 100.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 150.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 200.0f, 0.0f), CEnemy::NORMAL);

		//生成フラグを立てる
		m_bSub = true;
	}
	if (m_state == SECOND && !m_bSub)
	{
		//おともの生成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		//おともの生成
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.25f * nCnt - 1.0f)), 120.0f);
		}
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 200.0f, 200.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 300.0f, 100.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 200.0f, 200.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 300.0f, 100.0f, 0.0f), CEnemy::HOMING);

		//生成フラグを立てる
		m_bSub = true;
	}
	if (m_state == THIRD && !m_bSub)
	{
		//おともの生成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		//おともの生成
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.25f * nCnt - 1.0f)), 120.0f);
		}
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 100.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 150.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 100.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 150.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);

		//生成フラグを立てる
		m_bSub = true;
	}

	//移動する
	m_fMove += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
	m_move.y = sinf(m_fMove);
	m_move.x = cosf(m_fMove * 2.0f);

	//子分が0になったら生成フラグをリセット
	if (CBoss_Sub::GetNum() == 0)
	{
		//ボスの状態を進める
		m_state = (State)((int)m_state + 1);
		m_bSub = false;
	}

	//撃破可能状態になったら普通の敵扱いにする
	if (m_state == CRUSH)
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetType(TYPE_ENEMY);
	}

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBoss_Main::Draw(void)
{
	CEnemy::Draw();
}
