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
#include "bg.h"
#include "field.h"
#include "gametime.h"
#include "build.h"
#include "tutorial.h"
#include "tutorial_wall.h"
#include "fog.h"
#include "enemy.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CGameManager::Progress CGameManager::m_Progress = TUTORIAL_ENEMY;
CTutorial* CGameManager::m_pTutorial = nullptr;
CTutorialWall* CGameManager::m_pTutorialWall = nullptr;

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float END_FOG = 560.0f;
	const float START_FOG = 150.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
	m_Progress = TUTORIAL_ENEMY;
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
	// �t�H�O�̋�����ݒ�
	Fog::SetStart(START_FOG);
	Fog::SetEnd(END_FOG);

	//��Ԃ̏�����
	m_State = STATE_START;

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-2500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �G�̐���
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 20.0f, 0.0f), CEnemy::BOSS);

	//�����̐���
	CBuild::Create();

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);
	
	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

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

	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_GAME);

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

	//�`���[�g���A�����I��
	m_pTutorial = nullptr;

	// �J�����̏I��
	m_pCamera = NULL;

	// �t�H�O���I��
	Fog::Set(false);

	//BGM�̒�~
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CGameManager::Update(void)
{
	//�O��̏�Ԃ�ۑ�����
	m_oldState = m_State;

#if _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		CEnemy::Create(D3DXVECTOR3(-2000.0f, 20.0f, 0.0f), CEnemy::LANTERN);
		CEnemy::Create(D3DXVECTOR3(-1900.0f, 20.0f, 0.0f), CEnemy::LANTERN);
		CEnemy::Create(D3DXVECTOR3(-1950.0f, 20.0f, 0.0f), CEnemy::LANTERN);
	}
#endif

	// ��ԊǗ�
	TaskState();

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

#ifndef _DEBUG
	//�`���[�g���A���̐i�s
	TaskTutorial();
#endif

	//���U���g�ɑJ��
	if (m_pPlayer->GetPos().x >= 2300.0f || m_pPlayer->GetDeath())
	{
		if (m_pPlayer->GetDeath())
		{
			CSceneManager::SetClear(false);
		}
		else if (m_pPlayer->GetPos().x >= 2300.0f)
		{
			CSceneManager::SetClear(true);
		}

		// �J��
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//��ʑJ�ڃe�X�g
	if (CManager::GetInstance()->GetJoyPad()->GetPress(CJoyPad::BUTTON_A))
	{
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{

}

//==========================================
//  �`���[�g���A������
//==========================================
void CGameManager::TaskTutorial()
{

}

//==========================================
//  ��ԊǗ��̏���
//==========================================
void CGameManager::TaskState()
{
	// �Q�[�����X�^�[�g
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}
}
