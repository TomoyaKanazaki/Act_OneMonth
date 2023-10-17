//==========================================
//
//  �}�b�v�Ǘ��c�[��(map.cpp)
//  Autho : Tomoya Kanazaki
//
//==========================================
#include "map.h"
#include "object.h"
#include "manager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CMap::Tips CMap::m_Tips[2048] = {};

//==========================================
//  �R���X�g���N�^
//==========================================
CMap::CMap()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CMap::~CMap()
{

}

//==========================================
//  ����������
//==========================================
void CMap::Init(void)
{

}

//==========================================
//  �I������
//==========================================
void CMap::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CMap::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CMap::Draw(void)
{
}

//==========================================
//  �����o������
//==========================================
void CMap::Save(void)
{
	//���[�J���ϐ��錾
	int nNumTips = 0; //�}�b�v�`�b�v�̑�����ۑ�����ϐ�

	//�n�`�̃f�[�^���擾����
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�擪�̃A�h���X���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject* pNext = pObj->GetNext();

			if (pObj->GetMap()) //�}�b�v�`�b�v�̏ꍇ
			{
				//���W���擾
				m_Tips[nNumTips].pos = pObj->GetPos();

				//�p�x���擾
				m_Tips[nNumTips].rot = pObj->GetRot();

				//��ނ��擾
				m_Tips[nNumTips].type = pObj->GetType();

				//�g�p�������Z
				nNumTips++;

				//�x��
				if (nNumTips == 2047)
				{
					MessageBox(CManager::GetManager()->GetWindowHandle(), "Failed to save", "�f�[�^�e�ʒ���", MB_OK);
					return;
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
