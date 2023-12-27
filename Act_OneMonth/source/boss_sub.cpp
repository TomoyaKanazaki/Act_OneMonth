//==========================================
//
//  ボスのおとも(boss_sub,cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_sub.h"
#include "gamemanager.h"
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  静的メンバ変数
//==========================================
int CBoss_Sub::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CBoss_Sub::CBoss_Sub()
{
	m_nNum++;
	m_fLength = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CBoss_Sub::~CBoss_Sub()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss_Sub::Init(void)
{
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//ボスの位置を取得
	D3DXVECTOR3 pos = CGameManager::GetBoss()->GetPos();

	//座標を設定
	m_pos = pos + D3DXVECTOR3(cosf(m_rot.z) * m_fLength, sinf(m_rot.z)* m_fLength, 0.0f);

	//初期化処理
	HRESULT hr = CEnemy::Init();

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::LEAF));
	SetAnim(1, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBoss_Sub::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss_Sub::Update(void)
{
	//ボスの位置を取得
	D3DXVECTOR3 pos = CGameManager::GetBoss()->GetPos();

	//座標を設定
	m_pos = pos + D3DXVECTOR3(cosf(m_rot.z) * m_fLength, sinf(m_rot.z) * m_fLength, 0.0f);

	//角度の更新
	if (m_ObjState != MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
		{
			m_rot.z -= 0.001f;
		}
		else
		{
			m_rot.z -= 0.01f;
		}
	}

	//角度の補正
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += (-D3DX_PI * 2);
	}
	else if (m_rot.z <= -D3DX_PI)
	{
		m_rot.z += (D3DX_PI * 2);
	}

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBoss_Sub::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  生成処理
//==========================================
CBoss_Sub* CBoss_Sub::Create(D3DXVECTOR3 rot, float Length)
{
	//変数宣言
	CBoss_Sub* pBossSub = nullptr;

	//インスタンス生成
	pBossSub = new CBoss_Sub;

	//値を保存
	pBossSub->m_fLength = Length;
	pBossSub->m_rot = rot;

	//初期化処理
	pBossSub->Init();

	return nullptr;
}
