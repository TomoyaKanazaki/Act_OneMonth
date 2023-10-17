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
#include "logo.h"
#include "texture.h"

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
	CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::TITLE);

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
	//�V�[���o�ߎ��Ԃ����Z
	//m_nCntScene++;

	//��ʑJ��
	if (CManager::GetManager()->GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetManager()->GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::GAME);
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
