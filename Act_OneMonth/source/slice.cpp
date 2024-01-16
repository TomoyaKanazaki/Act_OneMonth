//==========================================
//
//  �a���G�t�F�N�g�N���X(slice.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slice.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CSlice::CSlice(int nPriority) : CObject3D_Anim(nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CSlice::~CSlice()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CSlice::Init(void)
{
	//�l��ݒ�
	SetAnim(10, 3, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CSlice::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSlice::Update(void)
{
	DebugProc::Print("\n\n\n\n�p�x : %f, %f, %f\n", m_rot.x, m_rot.y, m_rot.z);
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSlice::Draw(void)
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

	// �J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�`��
	CObject3D_Anim::Draw();

	// �J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

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
CSlice* CSlice::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, bool bRandRot)
{
	//�ϐ��錾
	CSlice* pSlice = nullptr;

	//�C���X�^���X����
	pSlice = new CSlice;

	//�l��ۑ�
	pSlice->m_pos = pos;
	pSlice->m_size = size;
	pSlice->m_rot = rot;

	// �����_�����b�g
	if (bRandRot)
	{
		pSlice->m_rot.x = (rand() % 628) * 0.01f;
		pSlice->m_rot.y = (rand() % 628) * 0.01f;
		pSlice->m_rot.y = (rand() % 628) * 0.01f;
	}

	//����������
	pSlice->Init();

	//�e�N�X�`�������蓖��
	pSlice->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SLICE));

	return pSlice;
}
