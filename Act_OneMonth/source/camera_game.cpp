//==========================================
//
//  �Q�[���V�[���̃J����(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float PLAYER_DISTANCE = 50.0f; //�v���C���[���璍���_�̋���
	const float REVISION_SPEED = 0.1f; // ����p�̊g�k���x
	const D3DXVECTOR3 LOCK_BOSS = D3DXVECTOR3(1800.0f, 200.0f, 0.0f);
}

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
	m_posR.y = V_HEIGHT; // ������␳����

	//���_��ݒ�
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraGame::Update(void)
{
	//�W����ԂŎ���p�̊g��
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		//���[�J���ϐ��錾
		float fDiff = MAX_FAV - m_fFov; //����

		//���������Z
		m_fFov += fDiff * REVISION_SPEED;

		// �J�������Œ肷��
		LockBoss();
	}
	else
	{
		//���[�J���ϐ��錾
		float fDiff = DEFAULT_FAV - m_fFov; //����

		//���������Z
		m_fFov += fDiff * REVISION_SPEED;

		//�v���C���[������
		MovePlayer();
	}

	CCamera::Update();
}

//==========================================
//  �v���C���[����������
//==========================================
void CCameraGame::MovePlayer(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
	m_posR.y = V_HEIGHT; // ������␳����
	D3DXVECTOR3 Dest = CGameManager::GetPlayer()->GetPos(); //�ڕW�̈ʒu
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̈ʒu�̍�
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot(); //�v���C���[�̕���
	float fDistance = sinf(rot.y) * PLAYER_DISTANCE;

	//�����𒲐�
	Dest.x -= fDistance;

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	m_posR += Diff * 0.1f;

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}

//==========================================
//  �{�X��̃J�����Œ菈��
//==========================================
void CCameraGame::LockBoss(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
	D3DXVECTOR3 Dest = LOCK_BOSS; //�ڕW�̈ʒu
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̈ʒu�̍�

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	m_posR += Diff * 0.1f;

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}
