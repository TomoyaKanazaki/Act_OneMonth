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

	//�T�C�Y��ݒ肷��
	float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
	m_size.x = fLength;
	m_size.y = m_fHeight;

	//�ʒu��ݒ�
	m_pos = (m_offset[0] + m_offset[1]) * 0.5f;

	//������
	HRESULT hr = CObject3D::Init();

	//�F��ݒ�
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

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
	m_fHeight -= 0.2f;
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�`��
	CObject3D::Draw();

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  ��������
//==========================================
COrbit* COrbit::Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, float fHeight)
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
	pOrbit->m_fHeight = fHeight;

	//����������
	pOrbit->Init();

	return pOrbit;
}
