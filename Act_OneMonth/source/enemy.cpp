//==========================================
//
//  �G�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "boss_main.h"
#include "enemy_normal.h"
#include "enemy_homing.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "cut.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CEnemy::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject3D_Anim(nPriority)
{
	m_type = NONE;
	pTexturePass = nullptr;
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�W����Ԃ̎��X���[�ɂȂ�
	if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE || CGameManager::GetState() == CGameManager::STATE_DASH)
	{
		m_move *= 0.1f;
	}

	//�ړ��ʂ̓K�p
	if (m_ObjState == MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_DASH)
		{
			CCut::Create(m_pos, m_size, pTexturePass, GetAnimPattern());
			Uninit();
			return;
		}
	}
	else
	{
		m_pos += m_move;
	}

	//��]
	Rotate();

	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D_Anim::Draw();

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//�ϐ��錾
	CEnemy* pEnemy = nullptr;

	//���������m��[
	if (pEnemy == nullptr)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;

		case HOMING:
			pEnemy = new CEnemy_Homing;
			break;

		case BOSS_MAIN:
			pEnemy = new CBoss_Main;
			break;

		default:
			pEnemy = nullptr;
			break;
		}
	}

	//�l��ݒ�
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//����������
	pEnemy->Init();

	return pEnemy;
}

//==========================================
//  �ړ�����������
//==========================================
void CEnemy::Rotate(void)
{
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (m_move.x == 0.0f)
	{
		return;
	}

	//�E�ɐi�ގ��͉E������
	if (m_move.x > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}

	//���ɐi�ނƂ��͍�������
	if (m_move.x < 0.0f)
	{
		m_rot.y = 0.0f;
	}
}
