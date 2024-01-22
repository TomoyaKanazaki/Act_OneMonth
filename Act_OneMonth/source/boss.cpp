//==========================================
//
//  �{�X�N���X(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss::CBoss(int nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// ������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	//m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// �T�C�Y��ݒ�
	m_size = BOSS_SIZE;

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBoss::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss::Update(void)
{
	// �J�����O���Ɣ�����
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		return;
	}

	// �v���C���[������
	RotateToPlayer();

	// �X�V
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss::Draw(void)
{
	CEnemy::Draw();
}
