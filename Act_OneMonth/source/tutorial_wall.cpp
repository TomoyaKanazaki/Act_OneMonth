//==========================================
//
//  �`���[�g���A����Ԃł̕�(tutorial_wall.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_wall.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorialWall::CTutorialWall()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTutorialWall::~CTutorialWall()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTutorialWall::Init(void)
{
	//�l��ݒ�
	m_pos = D3DXVECTOR3(-1000.0f, 100.0f, 0.0f);
	m_size = D3DXVECTOR3(30.0f, 120.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObject3D::Init();

	return E_NOTIMPL;
}

//==========================================
//  �I������
//==========================================
void CTutorialWall::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorialWall::Update(void)
{
	m_rot.y += 0.02f;
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorialWall::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D::Draw();

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  ��������
//==========================================
CTutorialWall* CTutorialWall::Create()
{
	// �C���X�^���X����
	CTutorialWall* pBlock = new CTutorialWall;

	// NULL�`�F�b�N
	if (pBlock == nullptr) { return nullptr; }

	// ����������
	pBlock->Init();

	//�e�N�X�`�������蓖��
	pBlock->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::OHUDA));

	// �l��Ԃ�
	return pBlock;
}
