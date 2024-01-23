//==========================================
//
//  �G�l�~�[�}�l�[�W��(enemymanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyManager::CEnemyManager() :
	m_pInfo(nullptr),
	m_pBoss(nullptr),
	m_bPopFrag(false)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  ����������
//==========================================
void CEnemyManager::Init()
{
	// ���̓ǂݍ���
	Load();
}

//==========================================
//  �I������
//==========================================
void CEnemyManager::Uninit()
{
	// �ݒu���̔j��
	if (m_pInfo != nullptr)
	{
		delete m_pInfo;
		m_pInfo = nullptr;
	}

	// ���g�̍폜
	delete this;
}

//==========================================
//  �X�V����
//==========================================
void CEnemyManager::Update()
{
	// �{�X�̏o��
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		if (!m_bPopFrag)
		{
			m_pBoss = CEnemy::Create(D3DXVECTOR3(1900.0f, 30.0f, 0.0f), CEnemy::BOSS
			
			);
			m_bPopFrag = true;
		}
	}

	// �f�o�b�O��p����
#ifdef _DEBUG

	// �񓔂�����
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_NUMPAD1))
	{
		CEnemy::Create(D3DXVECTOR3(-2000.0f, 30.0f, 0.0f), CEnemy::LANTERN);
	}

#endif
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CEnemyManager::Load()
{

}

//==========================================
//  ��������
//==========================================
CEnemyManager* CEnemyManager::Create()
{
	// �C���X�^���X����
	CEnemyManager* manager = new CEnemyManager;

	// NULL�`�F�b�N
	if (manager == nullptr) { return nullptr; }

	// ����������
	manager->Init();

	// �l��Ԃ�
	return manager;
}
