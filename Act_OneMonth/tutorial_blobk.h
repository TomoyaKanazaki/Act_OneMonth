//==========================================
//
//  チュートリアル状態での壁(tutorial_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_BLOCK_H_
#define _TUTORIAL_BLOCK_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTutorialBlock : public CObject3D
{
public:

	// メンバ関数
	CTutorialBlock();
	~CTutorialBlock();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ変数宣言
	static CTutorialBlock* Create(D3DXVECTOR3 pos);

private:

};

#endif
