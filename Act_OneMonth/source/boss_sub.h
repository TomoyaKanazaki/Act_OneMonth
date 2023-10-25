//==========================================
//
//  ボスのおとも(boss_sub.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_SUB_H_
#define _BOSS_SUB_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CBoss_Sub : public CEnemy
{
public:

	//メンバ関数
	CBoss_Sub();
	~CBoss_Sub();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBoss_Sub* Create(D3DXVECTOR3 rot, float Length);
	static int GetNum(void) { return m_nNum; }

private:

	//メンバ変数
	float m_fLength;

	//静的メンバ変数
	static int m_nNum;

};

#endif
