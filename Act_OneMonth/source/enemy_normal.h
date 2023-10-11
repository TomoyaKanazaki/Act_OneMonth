//==========================================
//
//  通常の敵クラス(enemy_normal.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Normal : public CEnemy
{
public:

	//メンバ関数
	CEnemy_Normal(int nPriority = 3);
	~CEnemy_Normal();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:


};

#endif
