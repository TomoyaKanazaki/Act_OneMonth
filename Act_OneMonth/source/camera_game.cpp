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
	//�W����ԂŎ���p�̊g��
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE/* || CGameManager::GetState() == CGameManager::STATE_DASH*/)
	{
		//���[�J���ϐ��錾
		float fDiff = MAX_FAV - m_fFov; //����

		//���������Z
		m_fFov += fDiff * REVISION_BIG;

		return;
	}
	else
	{
		//���[�J���ϐ��錾
		float fDiff = DEFAULT_FAV - m_fFov; //����

		//���������Z
		m_fFov += fDiff * REVISION_SMALL;
	}

	//�v���C���[������
	MovePlayer();

	CCamera::Update();
}

//==========================================
//  �v���C���[����������
//==========================================
void CCameraGame::MovePlayer(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
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

	//�������
	if (m_posR.y > 450.0f)
	{
		m_posR.y = 450.0f;
	}

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, HEIGHT, -CAMERA_DISTANCE);
}
