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
#include "arrow.h"
#include "marker.h"
#include "slice.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CPlayer::m_fHitLength = 25.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject_Char(nPriority)
{
	m_CenterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecStick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_bDash = false;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pArrow = nullptr;
	m_State = NEUTRAL;
	m_oldState = NEUTRAL;
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

	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	//���S���W��ݒ�
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//�o�ߎ��Ԃ��擾����
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�Q�[����Ԃ̎擾
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		m_fDeltaTime *= 0.0f;
	}

	//�_�b�V�����̏���
	Hit();

	//�_�b�V���̏���
	Dash();

	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		//�W�����v!
		Jump();

		//�ړ��̏���
		Move();
	}

	//��]�̏���
	Rotate();

	//�ړ�����
	Limit();

	//�d��
	Gravity();

	//���[�V����
	Motion();

	//�E��
	Death();

	//�O����W�ɕۑ�
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//���S���W��ݒ�
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	//�f�o�b�O�\��
	CManager::GetManager()->GetDebugProc()->Print("�ړ��� ( %f, %f )\n", m_move.x, m_move.y);
	CManager::GetManager()->GetDebugProc()->Print("���W ( %f, %f )\n", m_pos.x, m_pos.y);

	CObject_Char::Update();

#ifdef _DEBUG
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_Q))
	{
		m_State = NEUTRAL;
	}
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_1))
	{
		m_State = DEATH;
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw(void)
{
	CObject_Char::Draw();
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
//  ���[�V�����̍X�V
//==========================================
void CPlayer::Motion(void)
{
	//��Ԃ��؂�ւ�����u�ԂɃ��[�V������؂�ւ���
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE && CGameManager::GetOldState() == CGameManager::STATE_NORMAL)
	{
		m_State = IAI;
	}
	if (CGameManager::GetState() == CGameManager::STATE_NORMAL && CGameManager::GetOldState() != CGameManager::STATE_NORMAL)
	{
		m_State = NEUTRAL;
	}

	//��ԍX�V
	if (m_State == DEATH || CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		//�X�V���Ȃ�
	}
	else if (!m_bRand) //���n���ĂȂ����
	{
		if (m_move.y > 0.0f)
		{
			m_State = JUMP;
		}
		else
		{
			m_State = FALL;
		}
	}
	else if (m_move.x != 0.0f) //�ړ����Ă�����
	{
		m_State = WALK;
	}
	else //��L�̂ǂ�ł��Ȃ����
	{
		m_State = NEUTRAL;
	}

	//���[�V�������X�V
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case IAI:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		case JUMP:
			m_pMotion->Set(CMotion::PLAYER_JUMP);
			break;
		case FALL:
			m_pMotion->Set(CMotion::PLAYER_FALL);
			break;
		case WALK:
			m_pMotion->Set(CMotion::PLAYER_WALK);
			break;
		case NEUTRAL:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
			break;
		case DEATH:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
		}
	}

	//���݂̏�Ԃ�ۑ�
	m_oldState = m_State;
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Limit(void)
{
	//X���W�̐���
	if (CGameManager::GetState() != CGameManager::STATE_START && CGameManager::GetState() != CGameManager::STATE_END)
	{
		if (m_pos.x < -2250.0f)
		{
			m_pos.x = -2250.0f;
		}
		if (m_pos.x > 2250.0f)
		{
			m_pos.x = 2250.0f;
		}
	}

	//Y���W�̐���
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.y > 600.0f)
	{
		m_pos.y = 600.0f;
	}
	if (m_pos.y <= 0.0f)
	{
		m_bRand = true;
	}

	//�W����Ԓ��̈ړ�����
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		//��_�̎擾
		D3DXVECTOR3 pos = CGameManager::GetCamera()->GetPosR();

		//��_����v���C���[�̃x�N�g�����擾
		D3DXVECTOR3 vec = pos - m_pos;

		//��_���痣��Ă���������߂�
		if (vec.x < -CAMERA_WIDTH)
		{
			m_pos.x = pos.x + CAMERA_WIDTH;
		}
		if (vec.x > CAMERA_WIDTH)
		{
			m_pos.x = pos.x - CAMERA_WIDTH;
		}
		if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
		{
			if (vec.y < -CAMERA_HEIGHT)
			{
				m_pos.y = pos.y + CAMERA_HEIGHT;
			}
		}
	}
}

//==========================================
//  �ړ��̏���
//==========================================
void CPlayer::Move(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_State != DEATH)
	{
		//�p�b�h�ړ��ʂ��擾
		move = CManager::GetManager()->GetJoyPad()->GetStickL(0.1f);

		//�L�[�{�[�h�ړ��ʂ̎擾
		if (move.x == 0.0f)
		{
			move = CManager::GetManager()->GetKeyboard()->GetWASD();
		}
	}

	//�������s
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		move.x = 1.0f;
		move.y = 0.0f;
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
	if (m_State == DEATH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

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
	else if (m_move.y <= -JUMP_MOVE)
	{
		m_move.y = -JUMP_MOVE;
		return;
	}

	//�W����Ԃ̎�
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
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

	//�W����Ԃł̂ݔ���
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		if (m_pArrow != nullptr)
		{
			m_pArrow->Uninit();
			m_pArrow = nullptr;
		}
		return;
	}

	//���𐶐�
	if (m_pArrow == nullptr)
	{
		m_pArrow = CArrow::Create();
	}

	//�p�b�h�̓��͏����擾
	D3DXVECTOR3 move = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);

	//���͊p�x���Z�o
	float fAngle = atan2f(move.y, move.x);
	m_move = D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);

	if (CManager::GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_RB))
	{
		m_pos += D3DXVECTOR3(cosf(fAngle) * DASH_DISTANCE, -sinf(fAngle) * DASH_DISTANCE, 0.0f);
		m_bDash = true;
		m_bRand = false;
	}

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
	COrbit::Create(oldpos, pos);
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
				if (pObj->GetObjState() == CObject::NORMAL)
				{
					//�Ώۂ̍��W���擾����
					D3DXVECTOR3 pos = pObj->GetPos();

					//�O����W�Ƃ̋������v�Z����
					D3DXVECTOR3 vecToPosOld = m_oldposModel - pos;
					float fLength = sqrtf(vecToPosOld.x * vecToPosOld.x + vecToPosOld.y * vecToPosOld.y);

					//������W�Ƃ̋��������Z����
					D3DXVECTOR3 vecToPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43) - pos;
					fLength += sqrtf(vecToPos.x * vecToPos.x + vecToPos.y * vecToPos.y);

					//������̔�������
					if (HIT_RANGE >= fLength)
					{
						CMarker::Create(pos);
						CSlice::Create(pos, m_size * 3.0f);
						pObj->SetState(CObject::MARKING);
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}

//==========================================
//  �E��
//==========================================
void CPlayer::Death(void)
{
	//�ʏ��Ԃł������ȂȂ�
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

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

				//�x�N�g���̎Z�o
				D3DXVECTOR3 vec = m_CenterPos - pos;

				//�x�N�g���̑傫�����r����
				if (m_fHitLength * m_fHitLength >= (vec.x * vec.x + vec.y * vec.y))
				{
					m_State = DEATH;
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
