//==========================================
//
//  �`���[�g���A����Ԃł̕�(tutorial_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_blobk.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorialBlock::CTutorialBlock()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTutorialBlock::~CTutorialBlock()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTutorialBlock::Init(void)
{
	CTutorialBlock::Init();
	return E_NOTIMPL;
}

//==========================================
//  �I������
//==========================================
void CTutorialBlock::Uninit(void)
{
	CTutorialBlock::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorialBlock::Update(void)
{
	CTutorialBlock::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorialBlock::Draw(void)
{
	CTutorialBlock::Draw();
}

//==========================================
//  ��������
//==========================================
CTutorialBlock* CTutorialBlock::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTutorialBlock* pBlock = new CTutorialBlock;

	// NULL�`�F�b�N
	if (pBlock == nullptr) { return nullptr; }

	// �l��ݒ�
	pBlock->m_pos = pos;

	// ����������
	pBlock->Init();

	//�e�N�X�`�������蓖��
	pBlock->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::OHUDA));

	// �l��Ԃ�
	return pBlock;
}
