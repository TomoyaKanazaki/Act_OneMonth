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
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CBoss_Sub::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss_Sub::CBoss_Sub()
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
	//�T�C�Y��ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	//�{�X�̈ʒu���擾
	D3DXVECTOR3 pos = CGameManager::GetBoss()->GetPos();

	//���W��ݒ�
	m_pos = pos + D3DXVECTOR3(cosf(m_rot.z) * m_fLength, sinf(m_rot.z)* m_fLength, 0.0f);

	//����������
	HRESULT hr = CEnemy::Init();

	//�e�N�X�`���̊��蓖��
	SetTex(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ENEMY_00));
	SetAnim(4, 10, true, TYPE_U);

	return hr;
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
	if (m_ObjState != MARKING)
	{
		if (CGameManager::GetState() == CGameManager::STATE_CONCENTRATE)
		{
			m_rot.z += 0.001f;
		}
		else
		{
			m_rot.z += 0.01f;
		}
	}

	//�p�x�̕␳
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += (-D3DX_PI * 2);
	}
	else if (m_rot.z <= -D3DX_PI)
	{
		m_rot.z += (D3DX_PI * 2);
	}

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
