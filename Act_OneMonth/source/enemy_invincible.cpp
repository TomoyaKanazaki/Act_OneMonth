//==========================================
//
//  ������G(enemy_invincible.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_invincible.h"
#include "manager.h"
#include "texture.h"
#include "gametime.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Invincible::CEnemy_Invincible()
{
	m_fClear = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Invincible::~CEnemy_Invincible()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Invincible::Init(void)
{
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//����������
	HRESULT hr = CEnemy::Init();

	//�e�N�X�`���̊��蓖��
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_04));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Invincible::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Invincible::Update(void)
{
	//�F�̍X�V
	if (CGameManager::GetState() == CGameManager::STATE_NORMAL && OnScreen())
	{
		m_fClear += CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;
	}
	float fAlpha = (sinf(m_fClear) + 1.0f) * 0.5f;
	D3DXCOLOR col = GetCol();
	col.a = fAlpha;
	SetCol(col);

	//�F�������Ƃ��͖��G
	if (col.a <= 0.3f)
	{
		SetType(CObject::TYPE_BOSS);
	}
	else
	{
		SetType(CObject::TYPE_ENEMY);
	}

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Invincible::Draw(void)
{
	CEnemy::Draw();
}
