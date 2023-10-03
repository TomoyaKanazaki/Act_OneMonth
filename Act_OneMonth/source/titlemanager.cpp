//==========================================
//
//  �^�C�g���}�l�[�W��(titlemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "titlemanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sound.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CLight *CTitleManager::m_pLight = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitleManager::Init(void)
{
	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleManager::Uninit(void)
{
	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//BGM�̒�~
	CManager::GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CTitleManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	//m_nCntScene++;

	//��ʑJ��
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetMouse()->GetTrigger(CMouse::BUTTON_LEFT))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTitleManager::Draw(void)
{

}
