//==========================================
//
//  UIクラス(ui.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UI_H_
#define _UI_H_

//ImGui Template
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

//==========================================
//  クラス定義
//==========================================
class CUi
{
public:

	//メンバ関数
	CUi();
	~CUi();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	//列挙型定義
	enum EMode
	{
		SET_OBJECT = 0, //設置モード
		MOVE_OBJECT, //移動モード
		MAX
	};

	//メンバ関数
	void SelectMode(void);
	void Create(void);
	void Move(void);
	void SetCamera(void);

	//メンバ変数
	HWND m_hWnd; //ウィンドウハンドル
	bool m_bUpdate; //更新フラグ
	D3DXVECTOR3 m_pos; //生成位置

};

#endif
