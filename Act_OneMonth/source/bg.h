//==========================================
//
//  �w�i�N���X(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CBg : public CObject3D
{
public:
	
	//�����o�֐�
	CBg();
	~CBg();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�ÓI�����o�֐�
	static CBg* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:

};

#endif
