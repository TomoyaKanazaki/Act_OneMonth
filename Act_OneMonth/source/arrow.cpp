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

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CArrow::m_fPlayerLenge = 50.0f;
const D3DXVECTOR3 CArrow::m_cSize = D3DXVECTOR3(30.0f, 10.0f, 0.0f);

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
	D3DXVECTOR3 vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = atan2f(vecStick.x, vecStick.y);

	//�v���C���[���W�̎擾
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//�����̍��W���Z�o
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	//�T�C�Y��ݒ�
	m_size = m_cSize;

	return CObject3D::Init();
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
	D3DXVECTOR3 vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);
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
	CObject3D::Draw();
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
	pArrow->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ARROW));

	return pArrow;
}
