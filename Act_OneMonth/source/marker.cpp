//==========================================
//
//  �q�b�g�}�[�J�[(marker.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "marker.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "gamemanager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const D3DXVECTOR3 CMarker::mc_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

//==========================================
//  �R���X�g���N�^
//==========================================
CMarker::CMarker(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CMarker::~CMarker()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CMarker::Init(void)
{
	//�T�C�Y�̐ݒ�
	m_size = mc_size;

	//������
	HRESULT hr = CObject3D::Init();

	//�J���[�̐ݒ�
	SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CMarker::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CMarker::Update(void)
{
	//�W����Ԓ��̂�
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		Uninit();
	}

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CMarker::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
CMarker* CMarker::Create(const D3DXVECTOR3 pos)
{
	//�ϐ��錾
	CMarker* pMarker = nullptr;

	//�C���X�^���X����
	pMarker = new CMarker;

	//�l��ݒ�
	pMarker->m_pos = pos;

	//����������
	pMarker->Init();

	//�e�N�X�`�������蓖��
	pMarker->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::MARKER));

	return pMarker;
}
