//==========================================
//
//  �a���G�t�F�N�g(slash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 SLASH_SIZE = D3DXVECTOR3(2000.0f, 50.0f, 0.0f); // �|���S���T�C�Y
	const float CLEAR_TIME = 4.0f; // 1 / n �b
}

//==========================================
//  �R���X�g���N�^
//==========================================
CSlash::CSlash(int nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CSlash::~CSlash()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSlash::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = SLASH_SIZE;

	// �|���S���̍��[�̍��W���Z�o
	m_posLeft.x = m_pos.x + (cosf(m_rot.z) * m_size.x);
	m_posLeft.y = m_pos.y + (sinf(m_rot.z) * m_size.x);

	// �|���S���̉E�[�̍��W���Z�o
	m_posRight.x = m_pos.x - (cosf(m_rot.z) * m_size.x);
	m_posRight.y = m_pos.y - (sinf(m_rot.z) * m_size.x);

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	// ������
	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CSlash::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSlash::Update(void)
{
	// ���S�ɓ��߂��Ă����ꍇ�I������
	if (m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	// �s�����x��������
	m_col.a -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;

	// �U������
	Hit();

	// �f�o�b�O�\��
	DebugProc::Print("���[ : %f, %f\n", m_posLeft.x, m_posLeft.y);
	DebugProc::Print("�E�[ : %f, %f\n", m_posRight.x, m_posRight.y);

	// �X�V����
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSlash::Draw(void)
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
CSlash* CSlash::Create(const D3DXVECTOR3 pos, const float rot, const D3DXCOLOR col)
{
	// �C���X�^���X����
	CSlash* pSlash = new CSlash;

	// NULL�`�F�b�N
	if (pSlash == nullptr) { return nullptr; }

	// �l�̐ݒ�
	pSlash->m_pos = pos;
	pSlash->m_rot.z = rot;
	pSlash->m_col = col;

	// ����������
	pSlash->Init();

	// �l��Ԃ�
	return pSlash;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
void CSlash::Hit()
{
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
				if (pObj->GetObjState() == CObject::NORMAL) // �ʏ��Ԃ̏ꍇ
				{
					// �ڕW�_���擾����
					D3DXVECTOR3 pos = pObj->GetPos();

					// �n�_����I�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecLine = m_posRight - m_posLeft;

					// �n�_����ڕW�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecToPos = pos - m_posLeft;

					// �e�x�N�g���̑傫�������߂�
					float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
					float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

					// �}��ϐ�t�����߂�
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// �����̔���
					if (0.0f <= t && t <= 1.0f)
					{
						// �ڕW�_���璼���ɐ��������������̌�_�����߂�
						D3DXVECTOR3 posCross = m_posLeft + (t * vecLine);

						// ��_����ڕW�_�܂ł̃x�N�g�������߂�
						D3DXVECTOR3 vecToCross = pos - posCross;

						// ���苗���̔�r
						if (SLASH_SIZE.y * SLASH_SIZE.y >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
						{
							// �������Ă������̉��o�n����
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							pObj->SetState(CObject::ATTACKED);
						}
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
