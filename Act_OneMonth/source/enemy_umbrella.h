//==========================================
//
//  ���}������(enemy_umbrella.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_UMBRELLA_H_
#define _ENEMY_UMBRELLA_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Umbrella : public CEnemy
{
public:

	// �����o�֐�
	CEnemy_Umbrella();
	~CEnemy_Umbrella();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
