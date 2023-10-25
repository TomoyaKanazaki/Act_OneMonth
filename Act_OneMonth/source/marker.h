//==========================================
//
//  ヒットマーカー(marker.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MARKER_H_
#define _MARKER_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CMarker : public CObject3D
{
public:

	//メンバ関数
	CMarker(int nPriority = 6); //コンストラクタ
	~CMarker(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CMarker* Create(const D3DXVECTOR3 pos);

private:

	//静的メンバ変数
	static const D3DXVECTOR3 mc_size;

};

#endif
