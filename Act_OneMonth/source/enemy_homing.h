//==========================================
//
//  追従の敵クラス(enemy_homing.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_HOMING_H_
#define _ENEMY_HOMING_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Homing : public CEnemy
{
public:

	//メンバ関数
	CEnemy_Homing();
	~CEnemy_Homing();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Homing(void);

	//メンバ変数
	float m_fSpeed;

};

#endif
