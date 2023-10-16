//==========================================
//
//  �}�b�v�Ǘ��N���X(map.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAP_H_
#define _MAP_H_
#include "object.h"

//==========================================
//  �N���X��`
//==========================================
class CMap
{
public:

	//�����o�֐�
	CMap();
	~CMap();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static void Save(void);

private:

	//�}�b�v�`�b�v���
	struct Tips
	{
		D3DXVECTOR3 pos; //���W
		D3DXVECTOR3 rot; //�p�x
		CObject::TYPE type; //�I�u�W�F�N�g�̎��
	};

	//�ÓI�����o�ϐ�
	static Tips m_Tips[2048];

};

#endif
