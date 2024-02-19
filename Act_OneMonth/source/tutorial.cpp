//==========================================
//
//  ������@(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "enemymanager.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 TUTORIAL_SIZE = D3DXVECTOR3(250.0f, 70.0f, 0.0f); // �|���S���T�C�Y
	const D3DXVECTOR3 TUTORIAL_POS = D3DXVECTOR3(130.0f, 50.0f, 0.0f); // �|���S�����W
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorial::CTutorial(int nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTutorial::~CTutorial()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CTutorial::Init(void)
{
	// �ʒu��ݒ�
	m_pos = TUTORIAL_POS;

	// �傫����ݒ�
	m_size = TUTORIAL_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL));

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorial::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorial::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CTutorial* CTutorial::Create()
{
	// �C���X�^���X����
	CTutorial* pTutorial = new CTutorial;

	// NULL�`�F�b�N
	if (pTutorial == nullptr) { return nullptr; }

	// ����������
	pTutorial->Init();

	return pTutorial;
}
