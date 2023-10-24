//==========================================
//
//  �G�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "boss_main.h"
#include "enemy_normal.h"
#include "enemy_homing.h"
#include "gamemanager.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject_Char(nPriority)
{
	m_type = NONE;
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	return CObject_Char::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�W����Ԃ̎��X���[�ɂȂ�
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		m_move *= 0.1f;
	}

	//�ړ��ʂ̓K�p
	if (m_ObjState == MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_DASH)
		{
			Uninit();
			return;
		}
	}
	else
	{
		m_pos += m_move;
	}

	CObject_Char::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//�ϐ��錾
	CEnemy* pEnemy = nullptr;

	//���������m��[
	if (pEnemy == nullptr)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;

		case HOMING:
			pEnemy = new CEnemy_Homing;
			break;

		case BOSS_MAIN:
			pEnemy = new CBoss_Main;
			break;

		default:
			pEnemy = nullptr;
			break;
		}
	}

	//�l��ݒ�
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//����������
	pEnemy->Init();

	return pEnemy;
}
