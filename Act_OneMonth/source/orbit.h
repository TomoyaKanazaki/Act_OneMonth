//==========================================
//
//  �_�b�V���̋O�ՃN���X(orbit.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class COrbit : public CObject3D
{
public:

	//�����o�֐�
	COrbit(int nPriority = 6); //�R���X�g���N�^
	~COrbit(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static COrbit* Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_offset[2];
	float m_fHeight;

	//�ÓI�����o�ϐ��錾
	static const float m_fDefaultHeight;

};

#endif
