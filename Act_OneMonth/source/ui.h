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

	//メンバ変数
	HWND m_hWnd; //ウィンドウハンドル
	bool m_bUpdate; //更新フラグ

};

#endif
