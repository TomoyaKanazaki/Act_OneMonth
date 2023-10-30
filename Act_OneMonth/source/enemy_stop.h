//==========================================
//
//  停止している敵(enemy_stop.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_STOP_H_
#define _ENEMY_STOP_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Stop : public CEnemy
{
public:

	//メンバ関数
	CEnemy_Stop();
	~CEnemy_Stop();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

#endif
