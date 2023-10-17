//==========================================
//
//  �Q�[�������Ԍv���̃N���X(gametime.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMETIME_H_
#define _GAMETIME_H_

//==========================================
//  �N���X��`
//==========================================
class CGameTime
{
public:

	//�����o�֐�
	CGameTime();
	~CGameTime();

	void Init(void);
	void Uninit(void);
	void Update(void);

	int GetDeltaTimeInt(void) { return m_nDeltaTime; }
	float GetDeltaTimeFloat(void) { return m_fDelta; }

private:

	//�����o�ϐ�
	int m_nCurrentTime; //���ݎ���
	int m_nOldTime; //�O�񎞊�
	int m_nDeltaTime; //���ݎ��� - �O�񎞊�
	float m_fDelta; //1�b���ɂ�����o�ߎ��Ԃ̊���

};

#endif
