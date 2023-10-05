//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "motion.h"
#include "layer.h"
#include "gamemanager.h"
#include "orbit.h"
#include "camera.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_SPEED (2.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)
#define PLAYER_HEIGHT (40.0f) //�v���C���[�̍���

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CPlayer::mc_fExplosion = 5000.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nLife = 0;
	m_nDeadCounter = 0;
	m_nBladeLife = 10;
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	m_fSwing = 0.3f;
	m_bRand = true;
	m_bDead = false;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
	m_orbit = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CPlayer::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//���f���p�̃������̊m��
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���[�V�������̐���
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}
	
	//���[�V�������Ƀ��f����ǉ�����
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);

	//�r��O���Ɍ�����
	m_ppModel[3]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//���[�V�����̃|�C���^��j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�O�Ղ�j��
	if (m_orbit != NULL)
	{
		m_orbit->Uninit();
		delete m_orbit;
		m_orbit = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//�ړ��ʂ��擾
	D3DXVECTOR3 move = CManager::GetKeyboard()->GetWASD();
	m_move.x += move.x;

	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//�ړ��ʂ�K�p
	m_pos += m_move;

	//���̂��ړ�����
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		m_pos.x -= 100.0f;
	}

	//���[�V�������X�V����
	m_pMotion->Update();

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�ړ��� : %f\n", m_move.x);
	CManager::GetDebugProc()->Print("���ݍ��W : %f\n", m_pos.x);
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw()
{

}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CPlayer *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{
		//���������m��
		pPlayer = new CPlayer;
	}

	//�e����̕ۑ�
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//������
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//�|�C���^��Ԃ�
	return pPlayer;
}
