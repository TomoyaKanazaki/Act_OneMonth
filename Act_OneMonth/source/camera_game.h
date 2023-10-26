//==========================================
//
//  ゲームシーンのカメラ(camera_game.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "camera.h"

//==========================================
//  クラス定義
//==========================================
class CCameraGame : public CCamera
{
public:

	//メンバ関数
	CCameraGame();
	~CCameraGame();

	HRESULT Init(void) override;
	void Update(void) override;

private:

	//定数定義
#define REVISION_BIG (0.05f) //補正速度
#define REVISION_SMALL (0.01f) //補正速度
#define PLAYER_DISTANCE (50.0f) //プレイヤーから注視点の距離

	//メンバ関数
	void MovePlayer(void);

};

#endif
