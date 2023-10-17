//==========================================
//
//  �J�����N���X(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, HEIGHT, CAMERA_DISTANCE);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, HEIGHT, CAMERA_DISTANCE);
	m_bDebug = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCamera::~CCamera()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCamera::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CCamera::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CCamera::Update(void)
{
	CManager::GetManager()->GetDebugProc()->Print("���_ : ( %f, %f, %f )\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetManager()->GetDebugProc()->Print("�����_ : ( %f, %f, %f )\n", m_posR.x, m_posR.y, m_posR.z);
}

//==========================================
//  �ݒ菈��
//==========================================
void CCamera::SetCamera(void)
{

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(54.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		20000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X���v�Z
	CreateViewMatrix();

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  �r���[�}�g���b�N�X�̐���
//==========================================
D3DXMATRIX CCamera::CreateViewMatrix(void)
{
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	return m_mtxView;
}

//==========================================
//  ��l�̎��_�̑���
//==========================================
void CCamera::FirstPerson(void)
{
	//���_�̒l���X�V
	m_rot.x += CManager::GetManager()->GetManager()->GetMouse()->GetMouseMove().x;
	m_rot.z += CManager::GetManager()->GetManager()->GetMouse()->GetMouseMove().y;

	//�p�x�̕␳
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//�p�x���X�V
	m_posR.x = m_posV.x + (sinf(m_rot.z) * cosf(m_rot.x)) * CAMERA_DISTANCE;
	m_posR.y = m_posV.y + cosf(m_rot.z) * CAMERA_DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * CAMERA_DISTANCE;
}

//==========================================
//  �O�l�̎��_�̑���
//==========================================
void CCamera::ThirdPerson(void)
{
	//�����_���X�V
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//���_�̒l���X�V
	m_rot.y += CManager::GetManager()->GetManager()->GetMouse()->GetMouseMove().x;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//���_���X�V
	m_posV.x = posPlayer.x + (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posV.y = posPlayer.y + HEIGHT;
	m_posV.z = posPlayer.z + (cosf(m_rot.y) * CAMERA_DISTANCE);

	//�����_���X�V
	m_posR.x = posPlayer.x - (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posR.y = posPlayer.y;
	m_posR.z = posPlayer.z - (cosf(m_rot.y) * CAMERA_DISTANCE);
}

//==========================================
//  �ړ�
//==========================================
void CCamera::Move(void)
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ɃJ������Ǐ]������
	m_posV = pos;
	m_posR = pos;

	//�v���C���[����J�����𗣂�
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}