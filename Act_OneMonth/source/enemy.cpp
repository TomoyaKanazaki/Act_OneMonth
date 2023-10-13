//==========================================
//
//  �G�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "enemy_normal.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
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

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//���[�V�����̃|�C���^��j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//���̂��ړ�����
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{

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

	return nullptr;
}
