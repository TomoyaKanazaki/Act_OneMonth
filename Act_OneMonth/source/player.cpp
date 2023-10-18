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
	m_bDash = false;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	//�_�b�V�����̏���
	Hit();

	//�_�b�V���̏���
	Dash();

	if (!m_bDash)
	{
		//�W�����v!
		Jump();

		//�ړ��̏���
		Move();

		//��]�̏���
		Rotate();
	}

	//�ړ�����
	Limit();

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

	//�d��
	Gravity();

	//�O����W�ɕۑ�
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//�f�o�b�O�\��
	CManager::GetManager()->GetDebugProc()->Print("�ړ��� ( %f, %f )\n", m_move.x, m_move.y);
	CManager::GetManager()->GetDebugProc()->Print("���W ( %f, %f )\n", m_pos.x, m_pos.y);
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw(void)
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
//  �ړ�����
//==========================================
void CPlayer::Limit(void)
{
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_bRand = true;
	}
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
	m_move.x = move.x * PLAYER_SPEED;

	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//�ړ��ʂ�K�p
	m_pos += m_move * m_fDeltaTime;
}

//==========================================
//  ��]����
//==========================================
void CPlayer::Rotate(void)
{
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (m_move.x == 0.0f)
	{
		return;
	}

	//���[�J���ϐ��錾
	float fRotMove = m_rot.y; //���݂̊p�x
	float fRotDest = 0.0f; //�ڕW�̊p�x
	float fRotDiff = 0.0f; //�ڕW�ƌ��݂̊p�x�̍�

	//�E�ɐi�ގ��͉E������
	if (m_move.x > 0.0f)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}

	//���ɐi�ނƂ��͍�������
	if (m_move.x < 0.0f)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//�ړ��␳
	fRotDiff = fRotDest - fRotMove;	//�ڕW�܂ł̈ړ������̍���

	//�p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//�����]��
	m_rot.y += fRotDiff * 0.2f;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}

//==========================================
//  �W�����v�̏���
//==========================================
void CPlayer::Jump(void)
{
	//���n�t���O���I�t�̎�
	if (!m_bRand)
	{
		return;
	}

	//�W�����v!
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		m_move.y = JUMP_MOVE;
		m_bRand = false;
	}
}

//==========================================
//  �d�͂̏���
//==========================================
void CPlayer::Gravity(void)
{
	//�d�̖͂�������
	if (m_pos.y <= 0.0f)
	{
		m_move.y = 0.0f;
		return;
	}

	//�ړ��ʂ̌���
	m_move.y -= GRAVITY;
}

//==========================================
//  �_�b�V���̏���
//==========================================
void CPlayer::Dash(void)
{
	//�_�b�V���t���O�̃��Z�b�g
	m_bDash = false;

	//�p�b�h�̓��͏����擾
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.3f);

	//���͊p�x���Z�o
	float fAngle = atan2f(move.y, move.x);

	if (m_vecStick == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (move.x != 0.0f || move.y != 0.0f)
		{
			m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
			m_bDash = true;
		}
	}

	//����̓��͏���ۑ�����
	m_vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.2f);

	//���͊p�x��ۑ�����
	m_fDashAngle = fAngle;

	//�f�o�b�O�p�_�b�V��
#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_UP))
	{
		m_pos.y += DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_DOWN))
	{
		m_pos.y -= DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RIGHT))
	{
		m_pos.x += DASH_DISTANCE;
		m_bDash = true;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		m_pos.x -= DASH_DISTANCE;
		m_bDash = true;
	}
#endif

	//�ړ�����
	Limit();

	//�ړ����Ȃ������ꍇ�̓_�b�V�����L�����Z��
	if (m_oldPos == m_pos)
	{
		m_bDash = false;
	}
}

//==========================================
//  �O�Ղ̔���
//==========================================
void CPlayer::Orbit(void)
{
	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���f�����̎擾
	D3DXMATRIX mtxWorld = m_ppModel[3]->GetMtx();
	D3DXVECTOR3 pos = m_ppModel[3]->GetPos();
	D3DXVECTOR3 oldpos;

	//���ݍ��W�𒊏o
	pos = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�O����W�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_oldposModel.x, m_oldposModel.y, m_oldposModel.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���ݍ��W�𒊏o
	oldpos = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	//�O�Ղ𐶐�
	COrbit::Create(oldpos, pos, PLAYER_HEIGHT);
}

//==========================================
//  �G���������ޏ���
//==========================================
void CPlayer::Hit(void)
{
	//�_�b�V�����ĂȂ��ꍇ
	if (!m_bDash)
	{
		return;
	}

	//�O�Ղ𔭐�
	Orbit();

	//�����蔻��̐���
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
