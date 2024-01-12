//==========================================
//
//  �^�[�Q�b�g�N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "input.h"
#include "gametime.h"
#include "debugproc.h"
#include "camera.h"
#include "course.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MOVE_SPEED = 350.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority),
m_pPosMove(nullptr),
m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_nNumCount(0),
m_nNextIdx(0)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTarget::~CTarget()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTarget::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = POLYGON_SIZE;

	// �����ʒu���v���C���[���W�ɐݒ肷��
	m_pos = CGameManager::GetPlayer()->GetCenter();

	// �ړ��\�� + 1 �̍��W�f�[�^�𐶐�����
	if (m_pPosMove == nullptr)
	{
		m_pPosMove = new D3DXVECTOR3[m_nNumCount];

		// �l������������
		for (int i = 0; i < m_nNumCount; ++i)
		{
			m_pPosMove[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// �n�_���v���C���[���W�ɐݒ肷��
		m_pPosMove[0] = m_pos;

		// �ۑ���C���f�b�N�X���P�i�߂�
		++m_nNextIdx;
	}

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::KATANA));

	// ������
	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CTarget::Uninit(void)
{
	// ���W�f�[�^�̍폜
	if (m_pPosMove != nullptr)
	{
		delete m_pPosMove;
		m_pPosMove = nullptr;
	}

	// �I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTarget::Update(void)
{
	// �O�񂩂�̌o�ߎ��Ԃ��擾
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// �ړ�
	Move();

	// �ړ���ݒ�
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_RB)||
		CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		SetMove();
		CGameManager::GetPlayer()->SetMovePos(m_pos);
	}

	// �X�V
	CObject3D::Update();

	// �f�o�b�O�\��
	DebugProc::Print("�^�[�Q�b�g���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	DebugProc::Print("�ۑ���C���f�b�N�X [ %d ]\n", m_nNextIdx);
	DebugProc::Print("�ۑ��ł�����W [ %d ]\n", m_nNumCount);
	for (int i = 0; i < m_nNumCount; ++i)
	{
		DebugProc::Print("�ۑ����ꂽ���W [ %d ] : ( %f, %f, %f )\n", i, m_pPosMove[i].x, m_pPosMove[i].y, m_pPosMove[i].z);
	}
	DebugProc::Print("\n");
}

//==========================================
//  �`�揈��
//==========================================
void CTarget::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CTarget* CTarget::Create(const int nNum)
{
	// �C���X�^���X����
	CTarget* pTarget = new CTarget;

	// NULL�`�F�b�N
	if (pTarget == nullptr) { return nullptr; }

	// �l��ݒ�
	pTarget->m_nNumCount = nNum + 1;

	// ����������
	pTarget->Init();

	// �l��Ԃ�
	return pTarget;
}

//==========================================
//  �ړ��̏���
//==========================================
void CTarget::Move(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�p�b�h�ړ��ʂ��擾
	move = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);

	//�L�[�{�[�h�ړ��ʂ̎擾
	if (move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		move = CManager::GetInstance()->GetKeyboard()->GetWASD();
	}

	//�ړ��ʂ̓K�p
	m_move.x = move.x * MOVE_SPEED;
	m_move.y = move.z * MOVE_SPEED;

	//�ړ��ʂ�K�p
	m_pos += m_move * m_fDeltaTime;

	// �ړ�����
	Limit();
}

//==========================================
//  �ړ���̐ݒ�
//==========================================
void CTarget::SetMove()
{
	// �ݒ�\���Ǝ��̃C���f�b�N�X���r
	if (m_nNumCount <= m_nNextIdx)
	{
		return;
	}

	// ���݂̍��W�����̈ړ���ɕۑ�����
	m_pPosMove[m_nNextIdx] = m_pos;

	// �ړ��̋O�Ղ𐶐�
	CCourse::Create(m_pPosMove[m_nNextIdx - 1], m_pPosMove[m_nNextIdx]);

	// �ۑ���C���f�b�N�X���P�i�߂�
	++m_nNextIdx;
}

//==========================================
//  �ړ�����
//==========================================
void CTarget::Limit()
{
	// y����0������␳
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}

	// �X�N���[���O�̔���
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		m_pos = m_oldPos;
	}
}
