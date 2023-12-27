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
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Homing::CEnemy_Homing()
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
	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//初期化処理
	HRESULT hr = CEnemy::Init();

	//テクスチャの割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_03));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
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
	//対象の座標を取得する
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//ベクトルの算出
	D3DXVECTOR3 vec = m_pos - pos;

	//ベクトルの大きさを比較する
	if (500.0f * 500.0f <= (vec.x * vec.x + vec.y * vec.y))
	{
		return;
	}

	//追従処理
	Homing();

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
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetCenter();

	//プレイヤーへのベクトルを算出
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//ベクトルの正規化
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//デルタタイムの取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	//最終的な移動量を算出
	m_move = vecToPlayer * m_fSpeed * m_fDeltaTime;
}
