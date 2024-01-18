//==========================================
//
//  �Q�[���V�[���̃J����(camera_game.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "camera.h"

//==========================================
//  �N���X��`
//==========================================
class CCameraGame : public CCamera
{
public:

	//�����o�֐�
	CCameraGame();
	~CCameraGame();

	HRESULT Init(void) override;
	void Update(void) override;

private:

	//�����o�֐�
	void MovePlayer(void);

};

#endif
