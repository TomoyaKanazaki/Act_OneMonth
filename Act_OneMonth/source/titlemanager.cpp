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
#include "title.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CLight* CTitleManager::m_pLight = NULL;
CTitle* CTitleManager::m_pTitle = NULL;

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
	//�^�C�g�����S
	m_pTitle =  CTitle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f));

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

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
	CManager::GetManager()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CTitleManager::Update(void)
{
	//��ʑJ��
	if (CManager::GetManager()->GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetManager()->GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::GAME))
		{
			m_pTitle->CutTitle();
		}
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::RANKING);
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
