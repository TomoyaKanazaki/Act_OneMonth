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

	//�萔��`
#define REVISION_BIG (0.05f) //�␳���x
#define REVISION_SMALL (0.005f) //�␳���x
#define PLAYER_DISTANCE (50.0f) //�v���C���[���璍���_�̋���

	//�����o�֐�
	void MovePlayer(void);

};

#endif
