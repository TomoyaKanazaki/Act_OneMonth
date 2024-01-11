//==========================================
//
//  �ړ����q����(course.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "course.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "sound.h"
#include "marker.h"
#include "gamemanager.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float POLYGON_HEIGHT = 40.0f;
	const float HIT_LENGTH = 300.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCourse::CCourse(int nPriority) : CObject3D(nPriority),
m_start(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_end(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCourse::~CCourse()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCourse::Init(void)
{
	// ������
	HRESULT hr = CObject3D::Init();

	// �F�̐ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	Hit();

	// ������
	return hr;
}

//==========================================
//  �I������
//==========================================
void CCourse::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CCourse::Update(void)
{
	// ��Ԃ��؂�ւ������폜����
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		Uninit();
	}

	// �X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CCourse::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CObject3D::Draw();

	// �A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CCourse* CCourse::Create(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// �C���X�^���X����
	CCourse* pCourse = new CCourse;

	// NULL�`�F�b�N
	if (pCourse == nullptr) { return nullptr; }

	// �l��ݒ�
	pCourse->SetInfo(start, end);

	// ����������
	pCourse->Init();

	// �l��Ԃ�
	return nullptr;
}

//==========================================
//  �|���S���̏���ݒ肷��
//==========================================
void CCourse::SetInfo(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// �|���S���̒[��ۑ�
	m_start = start;
	m_end = end;

	// ���S���W��ݒ�
	m_pos = (start + end) * 0.5f;

	// �|���S���̒[����[�ւ̃x�N�g�����쐬
	D3DXVECTOR3 vecPolygon = end - start;

	// �x�N�g���̌������Z�o
	m_rot.z = atan2f(vecPolygon.y, vecPolygon.x);

	// �|���S���̉������Z�o
	m_size.x = sqrtf((vecPolygon.x * vecPolygon.x) + (vecPolygon.y * vecPolygon.y));
	m_size.y = POLYGON_HEIGHT;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
void CCourse::Hit()
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
					D3DXVECTOR3 vecLine = m_end - m_start;

					// �n�_����ڕW�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecToPos = pos - m_start;

					// �e�x�N�g���̑傫�������߂�
					float lengthLine = sqrtf(vecLine.x * vecLine.x) + (vecLine.y * vecLine.y);
					float lengthToPos = sqrtf(vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y);

					// �}��ϐ�t�����߂�
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// �ڕW�_���璼���ɐ��������������̌�_�����߂�
					D3DXVECTOR3 posCross = m_start + (t * vecLine);

					// ��_����ڕW�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecToCross = pos - posCross;

					// ���苗���̔�r
					if (HIT_LENGTH * HIT_LENGTH >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
					{
						// �����̔���
						if (0.0f <= t && t <= 1.0f)
						{
							// �������Ă������̉��o�n����
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							CMarker::Create(pos);
							pObj->SetState(CObject::MARKING);
						}
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
