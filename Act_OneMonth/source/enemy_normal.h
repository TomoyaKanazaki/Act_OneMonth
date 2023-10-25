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
	CEnemy_Normal();
	~CEnemy_Normal();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	float m_fMove;
	float m_fSpeed;

	//静的メンバ変数
	static const float m_fScope; //移動範囲

};

#endif
