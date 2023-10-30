//==========================================
//
//  ��~���Ă���G(enemy_stop.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_STOP_H_
#define _ENEMY_STOP_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Stop : public CEnemy
{
public:

	//�����o�֐�
	CEnemy_Stop();
	~CEnemy_Stop();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

#endif
