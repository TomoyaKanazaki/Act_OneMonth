//==========================================
//
//  �{�X�̂��Ƃ�(boss_sub,cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_sub.h"
#include "gamemanager.h"
#include "boss_main.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CBoss_Sub::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss_Sub::CBoss_Sub(int nPriority)
{
	m_nNum++;
	m_fLength = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss_Sub::~CBoss_Sub()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CBoss_Sub::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BOSS_SUB);

	//�{�X�̈ʒu���擾
	D3DXVECTOR3 pos = CGameManager::GetBoss()->GetPos();

	//���W��ݒ�
	m_pos = pos + D3DXVECTOR3(cosf(m_rot.z) * m_fLength, sinf(m_rot.z)* m_fLength, 0.0f);

	return CEnemy::Init();
}

//==========================================
//  �I������
//==========================================
void CBoss_Sub::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss_Sub::Update(void)
{
	//�{�X�̈ʒu���擾
	D3DXVECTOR3 pos = CGameManager::GetBoss()->GetPos();

	//���W��ݒ�
	m_pos = pos + D3DXVECTOR3(cosf(m_rot.z) * m_fLength, sinf(m_rot.z) * m_fLength, 0.0f);

	//�p�x�̍X�V
	m_rot.z += 0.01f;

	//�p�x�̕␳
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += (-D3DX_PI * 2);
	}
	else if (m_rot.z <= -D3DX_PI)
	{
		m_rot.z += (D3DX_PI * 2);
	}

	CManager::GetManager()->GetDebugProc()->Print("�q�����W ( %f, %f )\n", m_pos.x, m_pos.y);
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss_Sub::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  ��������
//==========================================
CBoss_Sub* CBoss_Sub::Create(D3DXVECTOR3 rot, float Length)
{
	//�ϐ��錾
	CBoss_Sub* pBossSub = nullptr;

	//�C���X�^���X����
	pBossSub = new CBoss_Sub;

	//�l��ۑ�
	pBossSub->m_fLength = Length;
	pBossSub->m_rot = rot;

	//����������
	pBossSub->Init();

	return nullptr;
}