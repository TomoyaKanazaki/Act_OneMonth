//==========================================
//
//  消える敵(enemy_invincible.h)
//  Author : Tomoya Kanazkai
//
//==========================================
#ifndef _ENEMY_INVINCIBLE_H_
#define _ENEMY_INVINCIBLE_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Invincible : public CEnemy
{
public:

	//メンバ関数
	CEnemy_Invincible();
	~CEnemy_Invincible();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	float m_fClear;
	float m_fAlpha;

};

#endif
