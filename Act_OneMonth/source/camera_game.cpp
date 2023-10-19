//==========================================
//
//  ゲームシーンのカメラ(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  コンストラクタ
//==========================================
CCameraGame::CCameraGame()
{

}

//==========================================
//  デストラクタ
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraGame::Init(void)
{
	//プレイヤー座標を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//注視点を設定
	m_posR = posPlayer;

	//視点を設定
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraGame::Update(void)
{
	//デバッグ中は更新しない
	if (!m_bDebug)
	{
		//プレイヤー座標を取得
		D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

		//注視点を更新
		m_posR = posPlayer;
	}

	//高さ上限
	if (m_posR.y > 450.0f)
	{
		m_posR.y = 450.0f;
	}

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);

	CCamera::Update();
}
