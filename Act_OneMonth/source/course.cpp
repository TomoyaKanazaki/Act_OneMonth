//==========================================
//
//  �ړ����q����(course.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "course.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float POLYGON_HEIGHT = 30.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCourse::CCourse(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCourse::~CCourse()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCourse::Init(void)
{
	// ������
	HRESULT hr = CObject3D::Init();

	// �F�̐ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	// ������
	return hr;
}

//==========================================
//  �I������
//==========================================
void CCourse::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CCourse::Update(void)
{
	// �X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CCourse::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
}

//==========================================
//  ��������
//==========================================
CCourse* CCourse::Create(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// �C���X�^���X����
	CCourse* pCourse = new CCourse;

	// NULL�`�F�b�N
	if (pCourse == nullptr) { return nullptr; }

	// �l��ݒ�
	pCourse->SetInfo(start, end);

	// ����������
	pCourse->Init();

	// �l��Ԃ�
	return nullptr;
}

//==========================================
//  �|���S���̏���ݒ肷��
//==========================================
void CCourse::SetInfo(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// ���S���W��ݒ�
	m_pos = (start + end) * 0.5f;

	// �|���S���̒[����[�ւ̃x�N�g�����쐬
	D3DXVECTOR3 vecPolygon = end - start;

	// �x�N�g���̌������Z�o
	m_rot.z = atan2f(vecPolygon.y, vecPolygon.x);

	// �|���S���̉������Z�o
	m_size.x = sqrtf((vecPolygon.x * vecPolygon.x) + (vecPolygon.y * vecPolygon.y));
	m_size.y = POLYGON_HEIGHT;
}
