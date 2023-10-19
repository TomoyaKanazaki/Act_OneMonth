//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "scene.h"

//==========================================
//  �O���錾
//==========================================
class CPlayer;
class CEnemy;
class CCamera;
class CLight;
class CUi;

//==========================================
//  �Q�[���}�l�[�W���N���X��`
//==========================================
class CGameManager : public CScene
{
public:

	//�Q�[�����
	enum State
	{
		STATE_NORMAL = 0, //�ʏ���
		STATE_CONCENTRTTE, //�W�����
		STATE_DASH, //�_�b�V�����
		MAX,
		NONE
	};

	CGameManager(); //�R���X�g���N�^
	~CGameManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	

	//�ÓI�����o�֐�
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CEnemy* GetEnemy(void) { return m_pBoss; }
	static void KillBoss(void) { m_pBoss = nullptr; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CUi* GetUi(void) { return m_pUi; }
	static State GetState(void) { return m_State; }

private:

	//�����o�ϐ�

	//�ÓI�����o�ϐ�
	static CPlayer* m_pPlayer;
	static CEnemy* m_pBoss;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CUi *m_pUi;
	static State m_State; //�Q�[���̏��

};

#endif
