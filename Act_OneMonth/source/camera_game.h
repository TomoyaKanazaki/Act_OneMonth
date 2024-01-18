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

	//メンバ関数
	void MovePlayer(void);

};

#endif
