//==========================================
//
//  �`���[�g���A����Ԃł̕�(tutorial_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_BLOCK_H_
#define _TUTORIAL_BLOCK_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTutorialBlock : public CObject3D
{
public:

	// �����o�֐�
	CTutorialBlock();
	~CTutorialBlock();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�ϐ��錾
	static CTutorialBlock* Create(D3DXVECTOR3 pos);

private:

};

#endif
