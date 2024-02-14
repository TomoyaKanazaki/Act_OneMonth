//==========================================
//
//  �̗͕\���̊Ǘ��N���X(lifemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "lifemanager.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "life.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(600.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(300.0f, FLOAT_SCREEN_HEIGHT - 50.0f, 0.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CLifeManager::CLifeManager(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLifeManager::~CLifeManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLifeManager::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = FRAME_SIZE;

	// �ʒu��ݒ�
	m_pos = FRAME_POS;

	// ������
	HRESULT hr = CObject2D::Init();

	// �F��ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::PLAYER_FRAME));

	// �̗͂�\��
	for (int i = 0; i < 10; ++i)
	{
		CLife::Create();
	}

	return hr;
}

//==========================================
//  �I������
//==========================================
void CLifeManager::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLifeManager::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLifeManager::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CLifeManager* CLifeManager::Create()
{
	// �C���X�^���X����
	CLifeManager* pLife = new CLifeManager;

	// ����������
	pLife->Init();

	return pLife;
}