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
#include "enemy.h"
#include "field.h"
#include "gametime.h"
#include "icon.h"
#include "build.h"
#include "tutorial.h"
#include "tutorial_wall.h"
#include "fog.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CEnemy* CGameManager::m_pBoss = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CGameManager::Progress CGameManager::m_Progress = TUTORIAL_ENEMY;
CIcon* CGameManager::m_pIcon = nullptr;
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

	//�{�X�̐���
	m_pBoss = CEnemy::Create(D3DXVECTOR3(1800.0f, 100.0f, 0.0f), CEnemy::BOSS_MAIN);

	//�G�̔z�u
	CEnemy::Create(D3DXVECTOR3(-1300.0f, 100.0f, 0.0f), CEnemy::STOP);
	CEnemy::Create(D3DXVECTOR3(-900.0f, 100.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-750.0f, 150.0f, 0.0f), CEnemy::STOP);
	CEnemy::Create(D3DXVECTOR3(-900.0f, 200.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-300.0f, 100.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-300.0f, 200.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-200.0f, 100.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-100.0f, 200.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-50.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(-50.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(50.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(50.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);

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

	m_pCamera = NULL;

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
	//��ʑJ�ڃe�X�g
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

	//�G
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_E))
	{
		CEnemy::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f), CEnemy::NORMAL);
	}
#endif

	// ��ԊǗ�
	TaskState();

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//�Q�[���N���A
	if (m_pBoss == nullptr)
	{
		m_State = STATE_END;
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

		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
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
	if (m_pPlayer->GetPos().x >= -1500.0f && m_Progress == TUTORIAL_ENEMY)
	{
		//�`���[�g���A���̐���
		if (m_pTutorial == nullptr)
		{
			m_pTutorial = CTutorial::Create();
			m_Progress = TUTORIAL_ARROW;

			// �ړ������𐶐�
			D3DXVECTOR3 pos = m_pPlayer->GetPos();
			pos.x += 500.0f;
			m_pTutorialWall = CTutorialWall::Create();
		}
	}
	if (m_pTutorial != nullptr)
	{
		if (m_Progress == TUTORIAL_ARROW)
		{
			if (m_State == STATE_CONCENTRATE)
			{
				m_pTutorial->NextProgress();

				m_Progress = TUTORIAL_DASH;
			}
		}
		if (m_Progress == TUTORIAL_DASH)
		{
			if (CManager::GetInstance()->GetJoyPad()->GetStickR(0.3f) != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_pTutorial->NextProgress();
				m_Progress = END;
			}
		}
		if (m_Progress == END)
		{
			if (m_State == STATE_NORMAL)
			{
				m_pTutorial->NextProgress();
				m_pTutorial = nullptr;

				// �ړ�����������
				if (m_pTutorialWall != nullptr)
				{
					m_pTutorialWall->Uninit();
					m_pTutorialWall = nullptr;
				}
			}
		}
	}
}

//==========================================
//  ��ԊǗ��̏���
//==========================================
void CGameManager::TaskState()
{
	// ��Ԃ̐؂�ւ�
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		if (m_State == STATE_NORMAL) // �W��
		{
			m_State = STATE_CONCENTRATE;
			Fog::Set(true); // �t�H�O��ݒ�
		}
		else if (m_State == STATE_CONCENTRATE) // �_�b�V��
		{
			m_State = STATE_DASH;
			m_fTimer = 0.0f; // ���Ԃ̃��Z�b�g
			Fog::Set(false); // �t�H�O��ݒ�
		}
	}

	// �_�b�V���̉���
	if (m_State == STATE_DASH)
	{
		// �o�ߎ��Ԃ����Z
		m_fTimer += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// �������ԂŒʏ��ԂɕύX
		if (m_fDashTime <= m_fTimer)
		{
			m_State = STATE_NORMAL;
		}
	}

	// �Q�[�����X�^�[�g
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}
}
