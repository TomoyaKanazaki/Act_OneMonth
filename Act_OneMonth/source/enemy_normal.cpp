//==========================================
//
//  �ʏ�̓G�̃N���X(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"
#include "manager.h"
#include "gametime.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
const float CEnemy_Normal::m_fScope = 300.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{
	m_fMove = 0.0f;
	m_fSpeed = 100.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Normal::~CEnemy_Normal()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Normal::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_NORMAL);

	return CEnemy::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy_Normal::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Normal::Update(void)
{
	//�f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�ړ�
	m_move.x = m_fSpeed * m_fDeltaTime;

	//�ړ�����������ۑ�
	m_fMove += m_move.x;

	//�ړ�����
	if (fabsf(m_fMove) >= m_fScope)
	{
		m_fSpeed *= -1.0f;
		m_fMove = 0.0f;
	}

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
