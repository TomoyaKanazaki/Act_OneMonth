//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_
#include "scene.h"

//==========================================
//  �O���錾
//==========================================
class CLight;
class CCamera;

//==========================================
//  �^�C�g���}�l�[�W���N���X��`
//==========================================
class CResultManager : public CScene
{
public:
	CResultManager(); //�R���X�g���N�^
	~CResultManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	float m_fCntScene;
	int m_nRank;

	//�ÓI�����o�ϐ�
	static CLight* m_pLight;
	static CCamera* m_pCamera;

};

#endif
