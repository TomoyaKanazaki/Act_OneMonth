//==========================================
//
//  �w�i�N���X(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBg::CBg()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBg::~CBg()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBg::Init(void)
{
	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CBg::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBg::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBg::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CBg* pBG = nullptr;

	//���������m��
	if (pBG == nullptr)
	{
		pBG = new CBg;
	}
	else
	{
		return nullptr;
	}

	//�l��ۑ�
	pBG->m_pos = pos;
	pBG->m_size = size;

	//������
	pBG->Init();

	//�e�N�X�`�������蓖�Ă�
	pBG->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::BG));

	return pBG;
}
