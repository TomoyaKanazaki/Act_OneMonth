//==========================================
//
//  チュートリアル状態での壁(tutorial_wall.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_WALL_H_
#define _TUTORIAL_WALL_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTutorialWall : public CObject3D
{
public:

	// メンバ関数
	CTutorialWall();
	~CTutorialWall();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ変数宣言
	static CTutorialWall* Create();

private:

};

#endif
