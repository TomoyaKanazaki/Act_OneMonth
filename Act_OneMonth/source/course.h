//==========================================
//
//  �ړ����q����(course.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _COURSE_H_
#define _COURSE_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CCourse : public CObject3D
{
public:

	//�����o�֐�
	CCourse(int nPriority = 6); //�R���X�g���N�^
	~CCourse(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CCourse* Create(D3DXVECTOR3 start, D3DXVECTOR3 end);

private:

	// �����o�֐�
	void SetInfo(D3DXVECTOR3 start, D3DXVECTOR3 end); // �|���S���̏���ݒ�

	// �����o�ϐ�


};

#endif
