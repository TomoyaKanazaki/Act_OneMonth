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

	//�{�X�̏��
	enum State
	{
		DEFAULT = 0, //���G���
		SECOND, //���`��
		THIRD, //��O�`��
		CRUSH, //���j�\
		MAX
	};

	//�����o�֐�
	CBoss_Main();
	~CBoss_Main();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	State m_state;
	bool m_bSub;
	float m_fMove;

};

#endif
