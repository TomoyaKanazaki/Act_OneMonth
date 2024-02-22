//==========================================
//
//  提灯お化け(enemy_blade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_BLADE_H_
#define _ENEMY_BLADE_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Blade : public CEnemy
{
public:

	// メンバ関数
	CEnemy_Blade();
	~CEnemy_Blade();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
