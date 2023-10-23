//==========================================
//
//  紋章クラス(icon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ICON_H_
#define _ICON_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CIcon : CObject3D
{
public:

	//メンバ関数
	CIcon(int nPriority = 7);
	~CIcon();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	float GetLIfe(void) { return m_fLife; }

	//静的メンバ関数
	static CIcon* Create(void);

private:

	//メンバ変数
	float m_fLife;

	//静的メンバ変数
	static const float m_fMaxLife;

};

#endif
