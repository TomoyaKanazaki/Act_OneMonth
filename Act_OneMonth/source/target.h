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
//  前方宣言
//==========================================
class CCourse;

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
	static CTarget* Create(const int nNum);

private:

	// メンバ関数
	void Move(); // 移動処理
	void SetMove(); // 移動先の設定
	void Limit(); // 移動制限

	// メンバ変数
	D3DXVECTOR3* m_pPosMove; // 移動先のポイント
	D3DXVECTOR3 m_move; // 移動量
	int m_nNumCount; // 移動可能回数
	int m_nNextIdx; // 次に座標を保存する先

};

#endif
