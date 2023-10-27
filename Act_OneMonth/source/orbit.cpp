//==========================================
//
//  �_�b�V���̋O�ՃN���X
//  Author : Tomoya Kanazaki
//
//==========================================
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "slice.h"
#include "gamemanager.h"
#include "icon.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float COrbit::m_fDefaultHeight = 20.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
COrbit::COrbit(int nPriority) : CObject3D(nPriority)
{
	m_offset[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offset[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fHeight = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
COrbit::~COrbit()
{

}

//==========================================
//  ����������
//==========================================
HRESULT COrbit::Init(void)
{
	//�p�x��ݒ肷��
	D3DXVECTOR3 vec = m_offset[1] - m_offset[0];
	m_rot.z = atan2f(vec.y, vec.x);

	//������ݒ肷��
	float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
	m_size.x = fLength;

	//������ݒ肷��
	m_fHeight = m_fDefaultHeight;
	if (CGameManager::GetIcon() != nullptr)
	{
		m_fHeight *= CGameManager::GetIcon()->GetLIfe();
	}
	m_size.y = m_fHeight;

	//�ʒu��ݒ�
	m_pos = (m_offset[0] + m_offset[1]) * 0.5f;

	//������
	HRESULT hr = CObject3D::Init();

	//�F��ݒ�
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//�e�N�X�`�������蓖�Ă�
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::SLASH));

	return hr;
}

//==========================================
//  �I������
//==========================================
void COrbit::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void COrbit::Update(void)
{
	//����������
	if (CGameManager::GetIcon() != nullptr)
	{
		m_fHeight = m_fDefaultHeight * CGameManager::GetIcon()->GetLIfe();
	}
	m_size.y = m_fHeight;

	//�������Ȃ��������
	if (m_size.y <= 0.0f)
	{
		Uninit();
	}

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void COrbit::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  ��������
//==========================================
COrbit* COrbit::Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1)
{
	//�ϐ��錾
	COrbit* pOrbit = nullptr;

	//���������m��
	if (pOrbit == nullptr)
	{
		pOrbit = new COrbit;
	}

	//�l��ݒ�
	pOrbit->m_offset[0] = offset0;
	pOrbit->m_offset[1] = offset1;

	//����������
	pOrbit->Init();

	return pOrbit;
}
