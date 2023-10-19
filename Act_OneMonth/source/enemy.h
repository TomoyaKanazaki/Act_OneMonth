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
		NORMAL = 0, //通常の敵
		MAX,
		NONE
	};

	//メンバ関数
	CEnemy(int nPriority = 3);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static int GetNum(void) { return m_nNum; }

protected:

	//モデル情報
	CModel** m_ppModel; //モデル情報
	CLayer::LAYERDATA* m_pLayer; //階層構造情報
	CMotion* m_pMotion;

private:

	//メンバ変数
	CEnemy::TYPE m_type;

	//静的メンバ変数
	static int m_nNum;

};

#endif
