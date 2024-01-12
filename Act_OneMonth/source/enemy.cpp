//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "boss_main.h"
#include "enemy_normal.h"
#include "enemy_homing.h"
#include "enemy_stop.h"
#include "enemy_invincible.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "cut.h"
#include "effect3D.h"
#include "slice.h"

//==========================================
//  静的メンバ変数
//==========================================
int CEnemy::m_nNum = 0;
int CEnemy::m_nDeath = 0;

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SLICE_SCALE = 1.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) :
	CObject3D_Anim(nPriority),
	m_pEffect(nullptr)
{
	m_type = NONE;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	// エフェクトを終了
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect = nullptr;
	}

	// 終了
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	//集中状態の時スローになる
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		m_move *= 0.1f;

		// エフェクトを生成
		if (m_pEffect == nullptr)
		{
			m_pEffect = CEffect3D::Create(m_pos, true);
			m_pEffect->SetSize(m_size * 2.0f);
		}
		else
		{
			// 移動
			m_pEffect->SetPos(m_pos);
		}
	}

	// エフェクトの削除
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		if (m_pEffect != nullptr)
		{
			m_pEffect->Uninit();
			m_pEffect = nullptr;
		}
	}

	// 状態毎の処理
	if (m_ObjState == MARKING) // マーキングされたとき
	{
		if (CGameManager::GetState() == CGameManager::STATE_NORMAL)
		{
			CSlice::Create(m_pos, m_size * SLICE_SCALE);
			CCut::Create(m_pos, m_size, m_pTexture, GetAnimPattern());
			++m_nDeath;
			Uninit();
			return;
		}
	}
	else // その他
	{
		m_pos += m_move;
	}

	//回転
	Rotate();

	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D_Anim::Draw();

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//変数宣言
	CEnemy* pEnemy = nullptr;

	//メモリを確保
	switch (type)
	{
	case NORMAL:
		pEnemy = new CEnemy_Normal;
		break;

	case STOP:
		pEnemy = new CEnemy_Stop;
		break;

	case HOMING:
		pEnemy = new CEnemy_Homing;
		break;

	case INVINCIBLE:
		pEnemy = new CEnemy_Invincible;
		break;

	case BOSS_MAIN:
		pEnemy = new CBoss_Main;
		break;

	default:
		pEnemy = nullptr;
		break;
	}

	// NULLチェック
	if (pEnemy == nullptr) { return nullptr; }

	//値を設定
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//初期化処理
	pEnemy->Init();

	return pEnemy;
}

//==========================================
//  移動方向を向く
//==========================================
void CEnemy::Rotate(void)
{
	//移動してない時は回転しない
	if (m_move.x == 0.0f)
	{
		return;
	}

	//右に進む時は右を向く
	if (m_move.x > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}

	//左に進むときは左を向く
	if (m_move.x < 0.0f)
	{
		m_rot.y = 0.0f;
	}
}
