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

	//ボスの状態
	enum State
	{
		DEFAULT = 0, //無敵状態
		CRUSH, //撃破可能
		MAX
	};

	//メンバ関数
	CBoss_Main(int nPriority = 3);
	~CBoss_Main();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	State m_state;
	bool m_bSub;

};

#endif
