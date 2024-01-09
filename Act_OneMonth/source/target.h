//==========================================
//
//  ターゲットクラス(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTarget : public CObject3D
{
public:

	//メンバ関数
	CTarget(int nPriority = 6); //コンストラクタ
	~CTarget(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTarget* Create(const D3DXVECTOR3 pos);

private:

	// メンバ変数
	D3DXVECTOR3* m_pPosMove; // 移動先のポイント
	int m_nNumCount; // 移動可能回数

};

#endif
