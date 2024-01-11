//==========================================
//
//  �v���C���[�N���X(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object_char.h"

//==========================================
//  �O���錾
//==========================================
class CArrow;

//==========================================
//  �v���C���[�N���X�̒�`
//==========================================
class CPlayer : public CObject_Char
{
public:

	//��Ԓ�`
	enum State
	{
		NEUTRAL = 0, //�ҋ@���
		WALK, //���s���
		JUMP, //�W�����v���
		FALL, //�������
		IAI, //�������
		DEATH, //���S���
		MAX
	};

	CPlayer(int nPriority = 4); //�R���X�g���N�^
	~CPlayer(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetCenter(void) { return m_CenterPos; }
	bool GetDeath(void) { return m_State == DEATH ? true : false; }
	State GetState(void) { return m_State; }

	//�ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�萔��`
#define PLAYER_SPEED (350.0f) //�v���C���[�̈ړ����x
#define PLAYER_HEIGHT (40.0f) //�v���C���[�̍���
#define DASH_DISTANCE (200.0f) //�_�b�V���̈ړ�����
#define HIT_RANGE (220.0f) //�q�b�g����͈�
#define JUMP_MOVE (750.0f) //�W�����v��
#define GRAVITY (25.0f) //�d��
#define CAMERA_WIDTH (420.0f) //�J�������痣�����͈�
#define CAMERA_HEIGHT (220.0f) //�J�������痣�����͈�
#define MAX_LEVEL (10) // ���x�����

	//�����o�֐�
	void Motion(void);
	void Limit(void);
	void Move(void);
	void Rotate(void);
	void Jump(void);
	void Gravity(void);
	void Dash(void);
	void Death(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_CenterPos; //���S���W
	D3DXVECTOR3 m_vecStick; //�O��̉E�X�e�B�b�N����
	float m_fDashAngle; //�O��̉E�X�e�B�b�N����
	bool m_bRand;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;
	CArrow* m_pArrow;
	State m_State;
	State m_oldState;

	//���f�����
	D3DXVECTOR3 m_oldposModel;

	//�ÓI�����o�ϐ�
	static const float m_fHitLength;

};

#endif
