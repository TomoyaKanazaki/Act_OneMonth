//==========================================
//
//  �Q�[�������Ԍv���̃N���X(gametime.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gametime.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CGameTime::CGameTime()
{
	m_nCurrentTime = 0;
	m_nOldTime = 0;
	m_nDeltaTime = 0;
	m_fDelta = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CGameTime::~CGameTime()
{

}

//==========================================
//  ����������
//==========================================
void CGameTime::Init(void)
{
	//���ݎ��Ԃ��擾
	m_nCurrentTime = timeGetTime();
	
	//���ݎ��Ԃ�O�񎞊Ԃɕۑ�
	m_nOldTime = m_nCurrentTime;
}

//==========================================
//  �I������
//==========================================
void CGameTime::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CGameTime::Update(void)
{
	//�O�񎞊Ԃ�ۑ�����
	m_nOldTime = m_nCurrentTime;

	//���ݎ��Ԃ��擾����
	m_nCurrentTime = timeGetTime();

	//�O�񎞊Ԃƌ��ݎ��Ԃ̍��������߂�
	m_nDeltaTime = m_nCurrentTime - m_nOldTime;

	//�o�ߎ��Ԃ̊��������߂�
	m_fDelta = (float)m_nDeltaTime / 1000.0f;

	//�f�o�b�O�\��
	DebugProc::Print("�O�񎞍� : %d\n", m_nOldTime);
	DebugProc::Print("���ݎ��� : %d\n", m_nCurrentTime);
	DebugProc::Print("�o�ߎ��� : %d\n", m_nDeltaTime);
	DebugProc::Print("�o�ߊ��� : %f\n", m_fDelta);
}
