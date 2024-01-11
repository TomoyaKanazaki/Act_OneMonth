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
//  �O���錾
//==========================================
class CCourse;

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
	static CTarget* Create(const int nNum);

private:

	// �����o�֐�
	void Move(); // �ړ�����
	void SetMove(); // �ړ���̐ݒ�
	void Limit(); // �ړ�����

	// �����o�ϐ�
	D3DXVECTOR3* m_pPosMove; // �ړ���̃|�C���g
	D3DXVECTOR3 m_move; // �ړ���
	int m_nNumCount; // �ړ��\��
	int m_nNextIdx; // ���ɍ��W��ۑ������

};

#endif
