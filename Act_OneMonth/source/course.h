//==========================================
//
//  移動を繋ぐ線(course.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _COURSE_H_
#define _COURSE_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CCourse : public CObject3D
{
public:

	//メンバ関数
	CCourse(int nPriority = 6); //コンストラクタ
	~CCourse(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CCourse* Create(D3DXVECTOR3 start, D3DXVECTOR3 end);

private:

	// メンバ関数
	void SetInfo(D3DXVECTOR3 start, D3DXVECTOR3 end); // ポリゴンの情報を設定
	void Hit(); // 敵との当たり判定

	// メンバ変数
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;

};

#endif
