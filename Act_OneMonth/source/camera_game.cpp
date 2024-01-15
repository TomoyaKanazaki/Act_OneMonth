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
	//プレイヤーを向く
	MovePlayer();

	CCamera::Update();
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CCameraGame::MovePlayer(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	D3DXVECTOR3 Dest = CGameManager::GetPlayer()->GetPos(); //目標の位置
	D3DXVECTOR3 Diff = {}; //目標と現在の位置の差
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot(); //プレイヤーの方向
	float fDistance = sinf(rot.y) * PLAYER_DISTANCE;

	//差分を調整
	Dest.x -= fDistance;

	//移動補正
	Diff = Dest - Pos;	//目標までの移動方向の差分

	//適用
	m_posR += Diff * 0.1f;

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);
}
