//==========================================
//
//  �񓔂�����(enemy_lantern.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_lantern.h"
#include "model.h"
#include "motion.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 LANTERN_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Lantern::CEnemy_Lantern()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Lantern::~CEnemy_Lantern()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Lantern::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_LANTERN);

	// ������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// �T�C�Y��ݒ�
	m_size = LANTERN_SIZE;

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Lantern::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Lantern::Update(void)
{
	RotateToPlayer();

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Lantern::Draw(void)
{
	CEnemy::Draw();
}