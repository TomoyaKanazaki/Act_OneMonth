//==========================================
//
//  �`���[�g���A��(tutorial.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTutorial : public CObject3D
{
public:

	//�����o�֐�
	CTutorial(int nPriority = 7);
	~CTutorial();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void NextProgress(void);

	//�ÓI�����o�֐�
	static CTutorial* Create(void);

private:

	//�萔��`
	static const float mc_fHeight;
	static const D3DXVECTOR3 mc_size;
};

#endif
