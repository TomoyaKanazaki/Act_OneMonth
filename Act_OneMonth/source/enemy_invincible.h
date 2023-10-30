//==========================================
//
//  ������G(enemy_invincible.h)
//  Author : Tomoya Kanazkai
//
//==========================================
#ifndef _ENEMY_INVINCIBLE_H_
#define _ENEMY_INVINCIBLE_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Invincible : public CEnemy
{
public:

	//�����o�֐�
	CEnemy_Invincible();
	~CEnemy_Invincible();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	float m_fClear;
	float m_fAlpha;

};

#endif
