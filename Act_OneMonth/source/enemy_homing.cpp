//==========================================
//
//  �Ǐ]�̓G�N���X(enemy_homing.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_homing.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "gametime.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Homing::CEnemy_Homing()
{
	m_fSpeed = 100.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Homing::~CEnemy_Homing()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Homing::Init(void)
{
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//����������
	HRESULT hr = CEnemy::Init();

	//�e�N�X�`���̊��蓖��
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_03));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Homing::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Homing::Update(void)
{
	//�Ώۂ̍��W���擾����
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�x�N�g���̎Z�o
	D3DXVECTOR3 vec = m_pos - pos;

	//�x�N�g���̑傫�����r����
	if (500.0f * 500.0f <= (vec.x * vec.x + vec.y * vec.y))
	{
		return;
	}

	//�Ǐ]����
	Homing();

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Homing::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �Ǐ]���鏈��
//==========================================
void CEnemy_Homing::Homing(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�x�N�g���̐��K��
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//�f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//�ŏI�I�Ȉړ��ʂ��Z�o
	m_move = vecToPlayer * m_fSpeed * m_fDeltaTime;
}
