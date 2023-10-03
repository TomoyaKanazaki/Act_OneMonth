//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "sound.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
	m_nRank = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CResultManager::Init(void)
{
	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CResultManager::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CResultManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	m_nCntScene++;

	//��ʑJ��
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 1500)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}

	CManager::GetDebugProc()->Print("���� : %d\n", m_nRank);
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
