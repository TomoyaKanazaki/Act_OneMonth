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

//==========================================
//  コンストラクタ
//==========================================
CBoss_Main::CBoss_Main()
{
	m_state = DEFAULT;
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
	SetTex(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	SetAnim(4, 10, true, TYPE_U);

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
	//スクリーン外なら更新しない
	if (!OnScreen())
	{
		return;
	}

	//子分を生成
	if (m_state == DEFAULT && !m_bSub)
	{
		//おともの生成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 150.0f);
		}

		//生成フラグを立てる
		m_bSub = true;
	}

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
