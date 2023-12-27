//==========================================
//
//  �{�X�G�̃N���X(boss_main.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"
#include "layer.h"
#include "gamemanager.h"
#include "boss_sub.h"
#include "texture.h"
#include "gametime.h"
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss_Main::CBoss_Main()
{
	m_state = DEFAULT;
	m_fMove = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss_Main::~CBoss_Main()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss_Main::Init(void)
{
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//������
	HRESULT hr = CEnemy::Init();

	//�{�X�t���O
	SetType(TYPE_BOSS);

	//�e�N�X�`���̊��蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_01));
	SetAnim(4, 10, true, TYPE_U);
	SetCol(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBoss_Main::Uninit(void)
{
	CGameManager::KillBoss();
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss_Main::Update(void)
{
	//Y���W�̐���
	if (m_pos.y < 120.0f)
	{
		m_pos.y = 120.0f;
	}
	if (m_pos.y > 200.0f)
	{
		m_pos.y = 200.0f;
	}

	//�q���𐶐�
	if (m_state == DEFAULT && !m_bSub)
	{
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 50.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 100.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 150.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(m_pos.x - 100.0f, 200.0f, 0.0f), CEnemy::NORMAL);

		//�����t���O�𗧂Ă�
		m_bSub = true;
	}
	if (m_state == SECOND && !m_bSub)
	{
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.25f * nCnt - 1.0f)), 120.0f);
		}
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 200.0f, 200.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 300.0f, 100.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 200.0f, 200.0f, 0.0f), CEnemy::HOMING);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 300.0f, 100.0f, 0.0f), CEnemy::HOMING);

		//�����t���O�𗧂Ă�
		m_bSub = true;
	}
	if (m_state == THIRD && !m_bSub)
	{
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 60.0f);
		}
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.25f * nCnt - 1.0f)), 120.0f);
		}
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 100.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x - 150.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 100.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
		CEnemy::Create(D3DXVECTOR3(CGameManager::GetPlayer()->GetCenter().x + 150.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);

		//�����t���O�𗧂Ă�
		m_bSub = true;
	}

	//�ړ�����
	m_fMove += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
	m_move.y = sinf(m_fMove);
	m_move.x = cosf(m_fMove * 2.0f);

	//�q����0�ɂȂ����琶���t���O�����Z�b�g
	if (CBoss_Sub::GetNum() == 0)
	{
		//�{�X�̏�Ԃ�i�߂�
		m_state = (State)((int)m_state + 1);
		m_bSub = false;
	}

	//���j�\��ԂɂȂ����畁�ʂ̓G�����ɂ���
	if (m_state == CRUSH)
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetType(TYPE_ENEMY);
	}

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss_Main::Draw(void)
{
	CEnemy::Draw();
}
