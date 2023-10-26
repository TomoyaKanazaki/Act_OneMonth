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
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
const float CEnemy_Normal::m_fScope = 300.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Normal::CEnemy_Normal()
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
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//����������
	HRESULT hr = CEnemy::Init();

	//�e�N�X�`���̊��蓖��
	SetTex(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
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
	//�ړ�����������ۑ�
	m_fMove += m_move.x;

	//�ړ�����
	if (fabsf(m_fMove) >= m_fScope)
	{
		m_fSpeed *= -1.0f;
		m_fMove = 0.0f;
	}

	//�f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�ړ�
	m_move.x = m_fSpeed * m_fDeltaTime;

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
