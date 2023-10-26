//==========================================
//
//  ���N���X(arrow.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ARROW_H_
#define _ARROW_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CArrow : public CObject3D
{
public:

	//�����o�֐�
	CArrow(int nPriority = 7);
	~CArrow();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CArrow* Create();

private:

	//�萔��`
	static const float m_fPlayerLenge;
	static const D3DXVECTOR3 m_cSize;

	//�����o�ϐ�

};

#endif
