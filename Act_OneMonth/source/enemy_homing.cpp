//==========================================
//
//  追従の敵クラス(enemy_homing.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_homing.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "gametime.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Homing::CEnemy_Homing(int nPriority)
{
	m_fSpeed = 100.0f;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Homing::~CEnemy_Homing()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Homing::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_HOMING);

	return CEnemy::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Homing::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Homing::Update(void)
{
	//画面内判定
	if (!OnScreen())
	{
		return;
	}

	//追従処理
	Homing();

	//移動量の適用
	m_pos += m_move;

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Homing::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  追従する処理
//==========================================
void CEnemy_Homing::Homing(void)
{
	//プレイヤーの位置を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーへのベクトルを算出
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//ベクトルの正規化
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//デルタタイムの取得
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//最終的な移動量を算出
	m_move = vecToPlayer * m_fSpeed * m_fDeltaTime;
}
