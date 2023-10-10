//==========================================
//
//  ��{�̃u���b�N�N���X(map_cube.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "map_cube.h"
#include "model.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CMap_Cube::CMap_Cube()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CMap_Cube::~CMap_Cube()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CMap_Cube::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_FIELD);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::CUBE_LAYER);

	//���f���p�̃������̊m��
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel * [m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���̂��ړ�����
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CMap_Cube::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CMap_Cube::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CMap_Cube::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CMap_Cube* CMap_Cube::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CMap_Cube* pCube  =nullptr;

	//���������m��
	if (pCube == nullptr)
	{
		pCube = new CMap_Cube;
	}
	else
	{
		return nullptr;
	}

	//�l��ݒ�
	pCube->m_pos = pos;

	//����������
	pCube->Init();

	return nullptr;
}
