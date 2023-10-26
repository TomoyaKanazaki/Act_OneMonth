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
#include "enemy.h"
#include "field.h"
#include "gametime.h"
#include "icon.h"
#include "build.h"

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
CIcon* CGameManager::m_pIcon = nullptr;

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
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
	//��Ԃ̏�����
	m_State = STATE_NORMAL;

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	//�{�X�̐���
	m_pBoss = CEnemy::Create(D3DXVECTOR3(1000.0f, 30.0f, 0.0f), CEnemy::BOSS_MAIN);

	//�G���G�̐���
	CEnemy::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-150.0f, 150.0f, 0.0f), CEnemy::HOMING);

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

	//BGM�̒�~
	CManager::GetManager()->GetManager()->GetSound()->Stop();
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
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetManager()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

#endif

	//��Ԃ̐؂�ւ�
	if (CManager::GetManager()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_LT, 100) || CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		if (m_State == STATE_NORMAL)
		{
			m_State = STATE_CONCENTRATE;

			//��͂�����
			if (m_pIcon == nullptr)
			{
				D3DXVECTOR3 size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
				m_pIcon = CIcon::Create(size);
			}
		}
	}

	//��Ԃ��X�V
	if (m_pIcon != nullptr)
	{
		if (m_pIcon->GetLIfe() <= 0.0f && m_State == STATE_CONCENTRATE)
		{
			m_State = STATE_DASH;
			m_pIcon = nullptr;
		}
	}

	//��Ԃ��X�V
	if (m_State == STATE_DASH)
	{
		if (m_fTimer >= m_fDashTime)
		{
			m_fTimer = 0.0f;
			m_State = STATE_NORMAL;
		}
		m_fTimer += CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//�Q�[���N���A
	if (m_pBoss == nullptr)
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{

}
