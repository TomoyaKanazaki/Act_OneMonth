//==========================================
//
//  �Q�[���V�[���̃J����(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraGame::CCameraGame()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraGame::Init(void)
{
	//�v���C���[���W���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�����_��ݒ�
	m_posR = posPlayer;

	//���_��ݒ�
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraGame::Update(void)
{
	//�f�o�b�O���͍X�V���Ȃ�
	if (!m_bDebug)
	{
		//�v���C���[���W���擾
		D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

		//�����_���X�V
		m_posR = posPlayer;
	}

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);

	CCamera::Update();
}
