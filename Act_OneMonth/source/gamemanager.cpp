//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "debugproc.h"
#include "bg.h"
#include "map_cube.h"
#include "ui.h"
#include "enemy.h"
#include "field.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CPlayer *CGameManager::m_pPlayer = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CUi* CGameManager::m_pUi = NULL;
CGameManager::State CGameManager::m_State = NONE;

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	
}

//==========================================
//  �f�X�g���N�^
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CGameManager::Init(void)
{
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	CEnemy::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), CEnemy::NORMAL);

	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1500.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f));

	////���̐���
	//CMap_Cube::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//UI�̐���
#ifdef _DEBUG
	if (m_pUi == NULL)
	{
		m_pUi = new CUi;
		m_pUi->Init();
	}
#endif

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CGameManager::Uninit(void)
{
	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	m_pCamera = NULL;

	//UI�̏I��
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
	}

	//BGM�̒�~
	CManager::GetManager()->GetManager()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CGameManager::Update(void)
{
#if _DEBUG
	//��ʑJ�ڃe�X�g
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetManager()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

	//��ʑJ�ڃe�X�g
	//if (CEnemy::GetNum() == 0)
	//{
	//	CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	//	return;
	//}

#endif

	//��Ԃ̐؂�ւ�
	if (CManager::GetManager()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_LT, 100))
	{
		m_State = STATE_CONCENTRTTE;
	}
	else
	{
		m_State = STATE_NORMAL;
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//UI�̍X�V
	if (m_pUi != NULL)
	{
		m_pUi->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{
	//UI�̍X�V
	if (m_pUi != NULL)
	{
		m_pUi->Draw();
	}
}
