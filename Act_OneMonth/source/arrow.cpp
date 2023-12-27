//==========================================
//
//  ���N���X(arrow.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "arrow.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "input.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CArrow::m_fPlayerLenge = 50.0f;
const D3DXVECTOR3 CArrow::m_cSize = D3DXVECTOR3(120.0f, 40.0f, 0.0f);

//==========================================
//  �R���X�g���N�^
//==========================================
CArrow::CArrow(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CArrow::~CArrow()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CArrow::Init(void)
{
	//�X�e�B�b�N�̊p�x���擾
	D3DXVECTOR3 vecStick = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = atan2f(vecStick.x, vecStick.y);

	//�v���C���[���W�̎擾
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//�����̍��W���Z�o
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	//�T�C�Y��ݒ�
	m_size = m_cSize;

	//����������
	HRESULT hr = CObject3D::Init();

	//�F�̐ݒ�
	SetCol(D3DXCOLOR(-1.0f, 1.0f, 0.3f, 1.0f));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CArrow::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CArrow::Update(void)
{
	//�X�e�B�b�N�̊p�x���擾
	D3DXVECTOR3 vecStick = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = -fAngle;

	//�v���C���[���W�̎擾
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//�����̍��W���Z�o
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CArrow::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  ��������
//==========================================
CArrow* CArrow::Create()
{
	//�ϐ��錾
	CArrow* pArrow = nullptr;

	//�C���X�^���X����
	pArrow = new CArrow;

	//����������
	pArrow->Init();

	//�e�N�X�`���̊��蓖��
	pArrow->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	return pArrow;
}
