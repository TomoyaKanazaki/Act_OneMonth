//==========================================
//
//  �Ǐ]�̓G�N���X(enemy_homing.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_HOMING_H_
#define _ENEMY_HOMING_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Homing : public CEnemy
{
public:

	//�����o�֐�
	CEnemy_Homing(int nPriority = 3);
	~CEnemy_Homing();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Homing(void);

	//�����o�ϐ�
	float m_fSpeed;

};

#endif
