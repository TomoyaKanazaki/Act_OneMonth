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
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "cut.h"

//==========================================
//  静的メンバ変数
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject3D_Anim(nPriority)
{
	m_type = NONE;
	pTexturePass = nullptr;
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
	}

	//移動量の適用
	if (m_ObjState == MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_DASH)
		{
			CCut::Create(m_pos, m_size, pTexturePass, GetAnimPattern());
			Uninit();
			return;
		}
	}
	else
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

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

	//メモリを確保[
	if (pEnemy == nullptr)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;

		case HOMING:
			pEnemy = new CEnemy_Homing;
			break;

		case BOSS_MAIN:
			pEnemy = new CBoss_Main;
			break;

		default:
			pEnemy = nullptr;
			break;
		}
	}

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
