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
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSlice::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CObject3D_Anim::Draw();

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CSlice* CSlice::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�ϐ��錾
	CSlice* pSlice = nullptr;

	//�C���X�^���X����
	pSlice = new CSlice;

	//�l��ۑ�
	pSlice->m_pos = pos;
	pSlice->m_size = size;

	//����������
	pSlice->Init();

	//�e�N�X�`�������蓖��
	pSlice->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::SLICE));

	return pSlice;
}
