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
CIcon::CIcon(int nPriority) : CObject3D(nPriority),
	m_fLife(0.0f)
{
	m_Default = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_size = m_Default;
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
	m_size = m_Default * m_fLife;

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

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject3D::Draw();

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

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
CIcon* CIcon::Create(D3DXVECTOR3 size)
{
	//�ϐ��錾
	CIcon* pIcon = nullptr;

	//�C���X�^���X����
	pIcon = new CIcon;

	//�l��ݒ�
	pIcon->m_Default = size;

	//����������
	pIcon->Init();

	//�e�N�X�`�������蓖��
	pIcon->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::KATANA));

	return pIcon;
}
