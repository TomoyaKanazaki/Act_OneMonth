//==========================================
//
//  �`���[�g���A����Ԃł̕�(tutorial_wall.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_WALL_H_
#define _TUTORIAL_WALL_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTutorialWall : public CObject3D
{
public:

	// �����o�֐�
	CTutorialWall();
	~CTutorialWall();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�ϐ��錾
	static CTutorialWall* Create();

private:

};

#endif
