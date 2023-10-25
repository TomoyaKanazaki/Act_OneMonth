//==========================================
//
//  斬撃エフェクトクラス(slice.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLICE_H_
#define _SLICE_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CSlice : public CObject3D_Anim
{
public:

	//メンバ関数
	CSlice(int nPriority = 6); //コンストラクタ
	~CSlice(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CSlice* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);

private:

	//メンバ変数

};

#endif
