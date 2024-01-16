//==========================================
//
//  �G�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "slice.h"
#include "player.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SLICE_SCALE = 1.0f;
	const D3DXVECTOR3 ENEMY_SIZE_DEFAULT = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) :
m_type(NONE)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	// ������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	// �T�C�Y��ݒ�
	m_size = ENEMY_SIZE_DEFAULT;

	// ���S���W��ݒ�
	m_posCenter = m_pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	// �I��
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	// ��Ԗ��̏���
	if (m_ObjState == MARKING) // �}�[�L���O���ꂽ�Ƃ�
	{
		if (CGameManager::GetPlayer()->GetState() != CPlayer::IAI)
		{
			CSlice::Create(m_posCenter, m_size * SLICE_SCALE, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			Uninit();
			return;
		}
	}
	else // ���̑�
	{
		m_pos += m_move;
	}

	// ���S���W��ݒ�
	m_posCenter = m_pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	//��]
	Rotate();

	CObject_Char::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject_Char::Draw();

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

	//���������m��
	switch (type)
	{
	case NORMAL:
		pEnemy = new CEnemy;
		//pEnemy = new CEnemy_Normal;
		break;

	default:
		pEnemy = nullptr;
		break;
	}

	// NULL�`�F�b�N
	if (pEnemy == nullptr) { return nullptr; }

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
