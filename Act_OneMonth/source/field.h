//==========================================
//
//  床(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "object_mesh.h"

//==========================================
//  クラス定義
//==========================================
class CFeild : public CObject_Mesh
{
public:

	//メンバ関数
	CFeild(int nPriority = 0);
	~CFeild();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CFeild* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv);

private: 

};

#endif
