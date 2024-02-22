//==========================================
//
//  障害物(block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CBlock : public CObject_Char
{
public:

	// メンバ関数
	CBlock();
	~CBlock();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CBlock* Create(const D3DXVECTOR3& pos);

private:

	// メンバ関数


	// メンバ変数

};

#endif
