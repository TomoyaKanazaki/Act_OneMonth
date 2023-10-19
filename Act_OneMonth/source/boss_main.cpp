//==========================================
//
//  �{�X�G�̃N���X(boss_main.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"
#include "layer.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss_Main::CBoss_Main(int nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss_Main::~CBoss_Main()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss_Main::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BOSS_MAIN);

	return CEnemy::Init();
}

//==========================================
//  �I������
//==========================================
void CBoss_Main::Uninit(void)
{
	CGameManager::KillBoss();
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss_Main::Update(void)
{
	CManager::GetManager()->GetDebugProc()->Print("�{�X���W ( %f, %f )\n", m_pos.x, m_pos.y);
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss_Main::Draw(void)
{
	CEnemy::Draw();
}
