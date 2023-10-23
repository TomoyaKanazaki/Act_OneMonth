//==========================================
//
//  ��̓N���X(icon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "icon.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CIcon::m_fMaxLife = 5.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CIcon::CIcon(int nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CIcon::~CIcon()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CIcon::Init(void)
{
	//���W��ݒ�
	m_pos = CGameManager::GetPlayer()->GetCenter();

	//������ݒ�
	m_fLife = m_fMaxLife;

	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_size *= m_fLife;

	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CIcon::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CIcon::Update(void)
{
	//����0�Ȃ�E��
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}

	//����������
	m_fLife -= CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�T�C�Y������
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f) * m_fLife;

	//���W��ݒ�
	m_pos = CGameManager::GetPlayer()->GetCenter();

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CIcon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CIcon* CIcon::Create(void)
{
	//�ϐ��錾
	CIcon* pIcon = nullptr;

	//�C���X�^���X����
	pIcon = new CIcon;

	//����������
	pIcon->Init();

	//�e�N�X�`�������蓖��
	pIcon->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::KATANA));

	return pIcon;
}
