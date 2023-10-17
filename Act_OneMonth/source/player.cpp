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
#include "gametime.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_vecStick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
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

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//�o�ߎ��Ԃ��擾����
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�O����W��ۑ�
	m_oldPos = m_pos;

	//�ړ��̏���
	Move();

	//�_�b�V���̏���
	Dash();

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

	//���[�V�������X�V����
	m_pMotion->Update();
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

//==========================================
//  �ړ��̏���
//==========================================
void CPlayer::Move(void)
{
	//�p�b�h�ړ��ʂ��擾
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickL(0.1f);

	//�L�[�{�[�h�ړ��ʂ̎擾
	if (move.x == 0.0f)
	{
		move = CManager::GetManager()->GetKeyboard()->GetWASD();
	}

	//�ړ��ʂ̓K�p
	m_move.x = move.x * PLAYER_SPEED * m_fDeltaTime;

	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//�ړ��ʂ�K�p
	m_pos += m_move;
}

//==========================================
//  �_�b�V���̏���
//==========================================
void CPlayer::Dash(void)
{
	//�p�b�h�̓��͏����擾
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.3f);

	//���͊p�x���Z�o
	float fAngle = atan2f(move.y, move.x);

	if (m_vecStick == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (move.x != 0.0f || move.y != 0.0f)
		{
			m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
			COrbit::Create(m_oldPos, m_pos, PLAYER_HEIGHT);
			Hit();
		}
	}

	//����̓��͏���ۑ�����
	m_vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.2f);

	//���͊p�x��ۑ�����
	m_fDashAngle = fAngle;

	//�f�o�b�O�p�_�b�V��
#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		m_pos.x += DASH_DISTANCE;
		COrbit::Create(m_oldPos, m_pos, PLAYER_HEIGHT);
		Hit();
	}
#endif
}

//==========================================
//  �G���������ޏ���
//==========================================
void CPlayer::Hit(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�擪�̃A�h���X���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				//�Ώۂ̍��W���擾����
				D3DXVECTOR3 pos = pObj->GetPos();

				//�O����W�Ƃ̋������v�Z����
				D3DXVECTOR3 vecToPosOld = m_oldPos - pos;
				float fLength = sqrtf(vecToPosOld.x * vecToPosOld.x + vecToPosOld.y * vecToPosOld.y);

				//������W�Ƃ̋��������Z����
				D3DXVECTOR3 vecToPos = m_pos - pos;
				fLength += sqrtf(vecToPos.x * vecToPos.x + vecToPos.y * vecToPos.y);

				//������̔�������
				if (HIT_RANGE >= fLength)
				{
					pObj->Uninit();
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
