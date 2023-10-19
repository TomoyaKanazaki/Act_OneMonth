//==========================================
//
//  �{�X�G�̃N���X(boss_main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_MAIN_H_
#define _BOSS_MAIN_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CBoss_Main : public CEnemy
{
public:

	//�����o�֐�
	CBoss_Main(int nPriority = 3);
	~CBoss_Main();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
