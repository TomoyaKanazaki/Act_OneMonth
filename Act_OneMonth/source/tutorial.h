//==========================================
//
//  チュートリアル(tutorial.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTutorial : public CObject3D
{
public:

	//メンバ関数
	CTutorial(int nPriority = 7);
	~CTutorial();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void NextProgress(void);

	//静的メンバ関数
	static CTutorial* Create(void);

private:

	//定数定義
	static const float mc_fHeight;
	static const D3DXVECTOR3 mc_size;
};

#endif
