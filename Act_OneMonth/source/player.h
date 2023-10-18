//==========================================
//
//  �v���C���[�N���X(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CMotion;
class CArrow;

//==========================================
//  �v���C���[�N���X�̒�`
//==========================================
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4); //�R���X�g���N�^
	~CPlayer(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetCenter(void) { return m_CenterPos; }

	//�ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�萔��`
#define PLAYER_SPEED (400.0f) //�v���C���[�̈ړ����x
#define PLAYER_HEIGHT (40.0f) //�v���C���[�̍���
#define DASH_DISTANCE (300.0f) //�_�b�V���̈ړ�����
#define HIT_RANGE (350.0f) //�q�b�g����͈�
#define JUMP_MOVE (1000.0f) //�W�����v��
#define GRAVITY (25.0f) //�d��

	//�����o�֐�
	void Limit(void);
	void Move(void);
	void Rotate(void);
	void Jump(void);
	void Gravity(void);
	void Dash(void);
	void Orbit(void);
	void Hit(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_CenterPos; //���S���W
	D3DXVECTOR3 m_vecStick; //�O��̉E�X�e�B�b�N����
	float m_fDashAngle; //�O��̉E�X�e�B�b�N����
	bool m_bRand;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;
	CArrow* m_pArrow;

	//���f�����
	CModel **m_ppModel; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����
	CMotion *m_pMotion;
	D3DXVECTOR3 m_oldposModel;

};

#endif
