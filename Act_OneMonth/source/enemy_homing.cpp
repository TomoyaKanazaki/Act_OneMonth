//==========================================
//
//  �Ǐ]�̓G�N���X(enemy_homing.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_homing.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "gametime.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Homing::CEnemy_Homing(int nPriority)
{
	m_fSpeed = 100.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Homing::~CEnemy_Homing()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Homing::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_HOMING);

	return CEnemy::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy_Homing::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Homing::Update(void)
{
	//��ʓ�����
	if (!OnScreen())
	{
		return;
	}

	//�Ǐ]����
	Homing();

	//�ړ��ʂ̓K�p
	m_pos += m_move;

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Homing::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �Ǐ]���鏈��
//==========================================
void CEnemy_Homing::Homing(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�x�N�g���̐��K��
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//�f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�ŏI�I�Ȉړ��ʂ��Z�o
	m_move = vecToPlayer * m_fSpeed * m_fDeltaTime;
}
