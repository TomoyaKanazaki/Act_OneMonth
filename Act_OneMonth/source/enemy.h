//==========================================
//
//  敵クラス(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy : public CObject_Char
{
public:

	//列挙型定義
	enum TYPE
	{
		LANTERN = 0, //通常の敵
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

protected:

	//メンバ関数
	void RotateToMove(); // 移動方向を向く
	void RotateToPlayer(); // プレイヤーを向く

private:

	//メンバ変数
	CEnemy::TYPE m_type;
	D3DXVECTOR3 m_posCenter; // 見た目の中心

};

#endif
