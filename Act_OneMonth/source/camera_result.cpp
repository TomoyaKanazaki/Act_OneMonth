//==========================================
//
//  �^�C�g���V�[���̃J����(camera_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_result.h"
#include "player.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POS_V = D3DXVECTOR3(0.0f, 100.0f, -350.0f); // ���_�ʒu
	const D3DXVECTOR3 POS_R = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����_�ʒu
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraResult::CCameraResult()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraResult::~CCameraResult()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraResult::Init(void)
{
	// �ʒu��ݒ�
	m_posV = POS_V;
	m_posR = POS_R;

	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraResult::Update(void)
{
	CCamera::Update();
}
