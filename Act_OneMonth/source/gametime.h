//==========================================
//
//  ゲーム内時間計測のクラス(gametime.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMETIME_H_
#define _GAMETIME_H_

//==========================================
//  クラス定義
//==========================================
class CGameTime
{
public:

	//メンバ関数
	CGameTime();
	~CGameTime();

	void Init(void);
	void Uninit(void);
	void Update(void);

	int GetDeltaTimeInt(void) { return m_nDeltaTime; }
	float GetDeltaTimeFloat(void) { return m_fDelta; }

private:

	//メンバ変数
	int m_nCurrentTime; //現在時間
	int m_nOldTime; //前回時間
	int m_nDeltaTime; //現在時間 - 前回時間
	float m_fDelta; //1秒感における経過時間の割合

};

#endif
