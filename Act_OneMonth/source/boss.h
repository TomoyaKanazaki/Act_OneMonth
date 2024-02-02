//==========================================
//
//  ボスクラス(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "enemy.h"

//==========================================
//  前方宣言
//==========================================
class CBossEffect;

//==========================================
//  クラス定義
//==========================================
class CBoss : public CEnemy
{
public:

	//メンバ関数
	CBoss(int nPriority = 5);
	~CBoss();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// メンバ関数
	void Attacked() override;

	// メンバ変数
	CBossEffect* m_pEffect;

};

#endif
