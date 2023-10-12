//==========================================
//
//  ダッシュの軌跡クラス(orbit.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class COrbit : public CObject3D
{
public:

	//メンバ関数
	COrbit(int nPriority = 5); //コンストラクタ
	~COrbit(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static COrbit* Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, float fHeight);

private:

	//メンバ変数宣言
	D3DXVECTOR3 m_offset[2];
	float m_fHeight;

};

#endif
