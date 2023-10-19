//==========================================
//
//  ボス敵のクラス(boss_main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_MAIN_H_
#define _BOSS_MAIN_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CBoss_Main : public CEnemy
{
public:

	//メンバ関数
	CBoss_Main(int nPriority = 3);
	~CBoss_Main();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
