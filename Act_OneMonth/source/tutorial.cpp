//==========================================
//
//  �`���[�g���A��(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CTutorial::mc_fHeight = 80.0f;
const D3DXVECTOR3 CTutorial::mc_size = D3DXVECTOR3(405.0f, 60.0f, 0.0f);

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorial::CTutorial(int nPriority) : CObject3D(nPriority)
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
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�����𒲐�����
	pos.y += mc_fHeight;

	//�ʒu��K�p����
	m_pos = pos;

	//�T�C�Y��ݒ肷��
	m_size = mc_size;

	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CTutorial::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorial::Update(void)
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�����𒲐�����
	pos.y += mc_fHeight;

	//�ʒu��K�p����
	m_pos = pos;

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorial::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CTutorial* CTutorial::Create(void)
{
	//�C���X�^���X����
	CTutorial* pTutorial = new CTutorial;

	//����������
	pTutorial->Init();

	//�e�N�X�`�������蓖��
	pTutorial->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_00));

	return pTutorial;
}

//==========================================
//  �`���[�g���A�������ɐi�߂�
//==========================================
void CTutorial::NextProgress(void)
{
	//�I���
	if (m_pTexture == CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_02))
	{
		Uninit();
	}

	//�i�߂�
	if (m_pTexture == CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_01))
	{
		BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_02));
	}

	//�i�߂�
	if (m_pTexture == CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_00))
	{
		BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::TUTORIAL_01));
	}
}
