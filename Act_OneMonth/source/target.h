//==========================================
//
//  �^�[�Q�b�g�N���X(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTarget : public CObject3D
{
public:

	//�����o�֐�
	CTarget(int nPriority = 6); //�R���X�g���N�^
	~CTarget(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTarget* Create(const D3DXVECTOR3 pos);

private:

	// �����o�ϐ�
	D3DXVECTOR3* m_pPosMove; // �ړ���̃|�C���g
	int m_nNumCount; // �ړ��\��

};

#endif
