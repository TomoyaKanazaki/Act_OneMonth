//==========================================
//
//  敵クラス(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy : public CObject3D_Anim
{
public:

	//列挙型定義
	enum TYPE
	{
		NORMAL = 0, //通常の敵
		STOP, //停止している敵
		HOMING, //追従の敵
		INVINCIBLE, //消える敵
		BOSS_MAIN, //ボス
		MAX,
		NONE
	};

	//メンバ関数
	CEnemy(int nPriority = 5);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static int GetNum(void) { return m_nNum; }

private:

	//メンバ関数
	void Rotate(void);

	//メンバ変数
	CEnemy::TYPE m_type;

	//静的メンバ変数
	static int m_nNum;

};

#endif
