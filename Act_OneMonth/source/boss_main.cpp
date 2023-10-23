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

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss_Main::CBoss_Main(int nPriority)
{
	m_state = DEFAULT;
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
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BOSS_MAIN);

	//������
	HRESULT hr = CEnemy::Init();

	//�{�X�t���O
	SetType(TYPE_BOSS);

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
	//�X�N���[���O�Ȃ�X�V���Ȃ�
	if (!OnScreen())
	{
		return;
	}

	//�q���𐶐�
	if (m_state == DEFAULT && !m_bSub)
	{
		//���Ƃ��̐���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			CBoss_Sub::Create(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * (0.5f * nCnt - 1.0f)), 150.0f);
		}

		//�����t���O�𗧂Ă�
		m_bSub = true;
	}

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
