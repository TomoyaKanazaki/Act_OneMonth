//==========================================
//
//  �{�X�N���X(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CBoss : public CEnemy
{
public:

	//�����o�֐�
	CBoss(int nPriority = 5);
	~CBoss();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// �����o�֐�
	void Attacked() override;

};

#endif
