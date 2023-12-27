//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "gametime.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "sound.h"
#include "logo.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{
	m_fCntScene = 0.0f;
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
	if (CSceneManager::GetClear())
	{
		CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::CLEAR);
	}
	else
	{
		CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::OVER);
	}

	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CResultManager::Uninit(void)
{
	//BGM�̒�~
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CResultManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	m_fCntScene += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	//��ʑJ��
	if (CManager::GetInstance()->GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || m_fCntScene >= 15.0f || CManager::GetInstance()->GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
