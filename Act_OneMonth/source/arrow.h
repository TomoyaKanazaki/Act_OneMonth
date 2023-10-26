//==========================================
//
//  矢印クラス(arrow.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ARROW_H_
#define _ARROW_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CArrow : public CObject3D
{
public:

	//メンバ関数
	CArrow(int nPriority = 7);
	~CArrow();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CArrow* Create();

private:

	//定数定義
	static const float m_fPlayerLenge;
	static const D3DXVECTOR3 m_cSize;

	//メンバ変数

};

#endif
