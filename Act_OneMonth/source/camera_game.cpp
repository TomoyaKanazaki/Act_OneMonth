//==========================================
//
//  ゲームシーンのカメラ(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "input.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float PLAYER_DISTANCE = 50.0f; //プレイヤーから注視点の距離
	const float REVISION_SPEED_FOV = 0.1f; // 視野角の拡縮速度
	const float REVISION_SPEED_POS = 0.05f; // 始点の移動速度
	const D3DXVECTOR3 LOCK_BOSS = D3DXVECTOR3(1800.0f, 200.0f, 0.0f);
}

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
	m_posR.y = V_HEIGHT; // 高さを補正する

	//視点を設定
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraGame::Update(void)
{
	// 状態毎の処理
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		// カメラを固定する
		LockBoss();
	}
	else
	{
		//プレイヤーを向く
		MovePlayer();
	}

	//ローカル変数宣言
	float fDiff = DEFAULT_FAV - m_fFov; //差分

	//差分を加算
	m_fFov += fDiff * REVISION_SPEED_FOV;

	CCamera::Update();
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CCameraGame::MovePlayer(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	m_posR.y = V_HEIGHT; // 高さを補正する
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
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}

//==========================================
//  ボス戦のカメラ固定処理
//==========================================
void CCameraGame::LockBoss(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	D3DXVECTOR3 Dest = LOCK_BOSS; //目標の位置
	D3DXVECTOR3 Diff = {}; //目標と現在の位置の差

	//移動補正
	Diff = Dest - Pos;	//目標までの移動方向の差分

	//適用
	m_posR += Diff * REVISION_SPEED_POS;

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}
