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
#include "debugproc.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f);
	const float MAX_LIFE = 10.0f;
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
	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	// �K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// ������
	HRESULT hr = CObject_Char::Init();

	// ���[�V�������Ƀ��f����n��
	//m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::LANTERN_WAIT);

	// �T�C�Y��ݒ�
	m_size = BOSS_SIZE;

	// �̗͂�ݒ�
	m_fLife = MAX_LIFE;

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

	// �f�o�b�O�\��
	DebugProc::Print("�{�X�̗̑� : %f\n", m_fLife);

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
