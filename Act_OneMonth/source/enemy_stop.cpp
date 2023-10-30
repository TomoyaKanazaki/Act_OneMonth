//==========================================
//
//  ��~����G(enemy_stop.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_stop.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Stop::CEnemy_Stop()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Stop::~CEnemy_Stop()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Stop::Init(void)
{
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//����������
	HRESULT hr = CEnemy::Init();

	//�e�N�X�`���̊��蓖��
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_02));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Stop::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Stop::Update(void)
{
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Stop::Draw(void)
{
	CEnemy::Draw();
}
