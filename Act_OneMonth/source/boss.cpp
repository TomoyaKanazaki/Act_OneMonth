//==========================================
//
//  �{�X�N���X(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "gametime.h"
#include "boss_effect.h"
#include "texture.h"
#include "orbit.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f); // �{�X�̑傫��
	const float MAX_LIFE = 100.0f; // �̗͂̍ő�l
	const float DAMAGE = 1.0f; // ���̍U������󂯂�_���[�W��
	const float INVINCIBLE_TIME = 0.1f; // ���G����
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 40.0f, 0.0f); // ���S���W�ƃI�u�W�F�N�g���W�̍�
	const float MOVE_SPEED = 100.0f; // �ړ����x
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss::CBoss(int nPriority) : CEnemy(nPriority),
m_State(POP),
m_MoveTimer(0.0f)
{
	m_pOrbit[0] = m_pOrbit[1] = nullptr;
} 

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss::Init(void)
{
	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	// �K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// ������
	HRESULT hr = CObject_Char::Init();

	// ���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::BOSS_WAIT);

	// �T�C�Y��ݒ�
	m_size = BOSS_SIZE;
	CalcHitLength(m_size);

	// �̗͂�ݒ�
	m_fLife = MAX_LIFE;

	// �o���G�t�F�N�g�̔���
	CBossEffect::Create(m_pos);

	// �F�ύX�t���O�𗧂Ă�
	ChangeColor(true);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// ���S���W�̐ݒ�
	m_posCenter = m_pos + CENTER_POS;

	// ���ɋO�Ղ�t����
	if (m_pOrbit[0] == nullptr)
	{
		m_pOrbit[0] = COrbit::Create(m_ppModel[4], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -110.0f), 30);
		m_pOrbit[0]->SwitchDraw(false);
	}
	if (m_pOrbit[1] == nullptr)
	{
		m_pOrbit[1] = COrbit::Create(m_ppModel[5], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -110.0f), 30);
		m_pOrbit[1]->SwitchDraw(false);
	}
	return hr;
}

//==========================================
//  �I������
//==========================================
void CBoss::Uninit(void)
{
	// �O�Ղ̏I��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->Uninit();
			m_pOrbit[i] = nullptr;
		}
	}

	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss::Update(void)
{
	// �s�����x�����Z����
	if (m_col.a < 1.0f)
	{
		m_col.a += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;

		if (m_col.a > 1.0f) // �o������
		{
			m_col.a = 1.0f;
			ChangeColor(false);
			m_State = NEUTRAL;

			// �O�Ղ𔭐�
			for (int i = 0; i < 2; ++i)
			{
				if (m_pOrbit[i] != nullptr)
				{
					m_pOrbit[i]->SwitchDraw(true);
				}
			}
		}
	}

	// �팂���̏���
	Attacked();

	// �ҋ@��Ԃ̎��̂݃v���C���[������
	if (m_State == NEUTRAL)
	{
		RotateToPlayer();
		Move();
	}

	// ���S����
	if (m_fLife <= 0.0f)
	{
		m_State = DEATH;
	}

	// �f�o�b�O�\��
	DebugProc::Print("�{�X�̗̑� : %f\n", m_fLife);

	// �X�V
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �팂���̏���
//==========================================
void CBoss::Attacked()
{
	// �o����Ԃ���юu�]��Ԓ��͍U�����󂯂Ȃ�
	if (m_State == POP || m_State == DEATH)
	{
		return;
	}

	// ��Ԗ��̏���
	if (m_ObjState == ATTACKED)
	{
		m_fLife -= DAMAGE;
		m_AllDamage += DAMAGE;
		m_ObjState = INVINCIBLE;
		WhiteOut(true);
		return;
	}
	else if (m_ObjState == INVINCIBLE)
	{
		// ���Ԃ̉��Z
		m_fInvincible += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// ���G���Ԃ̉���
		if (m_fInvincible >= INVINCIBLE_TIME)
		{
			m_ObjState = NORMAL;
			m_fInvincible = 0.0f;
			WhiteOut(false);
		}
	}
}

//==========================================
//  �ړ�����
//==========================================
void CBoss::Move()
{
	// �ړ��ʂ̌v�Z
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
	m_MoveTimer += m_fDeltaTime;
	m_move.x = sinf(m_MoveTimer * 0.5f) * MOVE_SPEED * m_fDeltaTime;
	m_move.y = cosf(m_MoveTimer) * MOVE_SPEED * m_fDeltaTime;
}
