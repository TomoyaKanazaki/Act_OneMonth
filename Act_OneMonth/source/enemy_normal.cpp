//==========================================
//
//  �ʏ�̓G�̃N���X(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{

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
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

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
	//�X�N���[���O�Ȃ�X�V���Ȃ�
	if (!OnScreen())
	{
		return;
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
