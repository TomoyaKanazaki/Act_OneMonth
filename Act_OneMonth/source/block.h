//==========================================
//
//  ��Q��(block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CBlock : public CObject_Char
{
public:

	// �����o�֐�
	CBlock();
	~CBlock();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos);

private:

	// �����o�֐�


	// �����o�ϐ�

};

#endif
