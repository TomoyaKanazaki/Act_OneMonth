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
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̊p�x
	D3DXVECTOR3 Dest = {}; //�ڕW�̊p�x
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̊p�x�̍�

	//�f�o�b�O���͍X�V���Ȃ�
	if (!m_bDebug)
	{
		//�v���C���[���W���擾
		D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

		//�����_���X�V
		Dest = posPlayer;
	}

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	if (CGameManager::GetState() == CGameManager::STATE_NORMAL)
	{
		m_posR += Diff;
	}
	else
	{
		m_posR += Diff * 0.1f;
	}

	//�������
	if (m_posR.y > 450.0f)
	{
		m_posR.y = 450.0f;
	}

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);

	CCamera::Update();
}
