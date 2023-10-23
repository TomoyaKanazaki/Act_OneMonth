//==========================================
//
//  �{�X�̂��Ƃ�(boss_sub.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_SUB_H_
#define _BOSS_SUB_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CBoss_Sub : public CEnemy
{
public:

	//�����o�֐�
	CBoss_Sub(int nPriority = 3);
	~CBoss_Sub();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBoss_Sub* Create(D3DXVECTOR3 rot, float Length);
	static int GetNum(void) { return m_nNum; }

private:

	//�����o�ϐ�
	float m_fLength;

	//�ÓI�����o�ϐ�
	static int m_nNum;

};

#endif
