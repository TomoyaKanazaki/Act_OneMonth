//==========================================
//
//  �}�l�L���N���X(running.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RUNNING_H_
#define _RUNNING_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CRunning : public CObject_Char
{
public:

	//�����o�֐�
	CRunning(int nPriority = 4); //�R���X�g���N�^
	~CRunning(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Dash(void);

	//�ÓI�����o�֐�
	static CRunning* Create();

};

#endif
