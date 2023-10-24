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
class CIcon;

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
		STATE_CONCENTRATE, //�W�����
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
	static CEnemy* GetBoss(void) { return m_pBoss; }
	static void KillBoss(void) { m_pBoss = nullptr; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static State GetState(void) { return m_State; }
	static State GetOldState(void) { return m_oldState; }
	static CIcon *GetIcon(void) { return m_pIcon; }

private:

	//�����o�ϐ�
	float m_fTimer;

	//�ÓI�����o�ϐ�
	static const float m_fDashTime;
	static CPlayer* m_pPlayer;
	static CEnemy* m_pBoss;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static State m_State; //�Q�[���̏��
	static State m_oldState; //�O�t���[���ł̃Q�[���̏��
	static CIcon *m_pIcon;

};

#endif
