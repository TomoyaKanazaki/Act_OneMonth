//==========================================
//
//  マネージャクラス(manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//==========================================
//  マクロ定義
//==========================================
#define MAX_PLAYER (4) //プレイヤーの最大数

//==========================================
//  前方宣言
//==========================================
class CRenderer;
class CKeyboard;
class CMouse;
class CJoyPad;
class CDebugProc;
class CSound;
class CTexture;
class CSceneManager;

//==========================================
//  マネージャクラス定義
//==========================================
class CManager
{
public:

	//定数
#define SCREEN_WIDTH (1280) //スクリーンの幅
#define SCREEN_HEIGHT (720) //スクリーンの高さ
#define CENTER_WIDTH (SCREEN_WIDTH / 2) //スクリーン中心座標のY座標
#define CENTER_HEIGHT (SCREEN_HEIGHT / 2) //スクリーン中心座標のX座標
#define FLOAT_SCREEN_WIDTH (1280.0f) //スクリーンの幅(float版)
#define FLOAT_SCREEN_HEIGHT (720.0f) //スクリーンの高さ(float版)
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "REBLADE"

	CManager(); //コンストラクタ
	~CManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }
	static CMouse *GetMouse(void) { return m_pMouse; }
	static CJoyPad *GetJoyPad(void) { return m_pJoyPad; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CSound *GetSound(void) { return m_pSound; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CSceneManager *GetSceneManager(void) { return m_pSceneManager; }
	static int GetFPS(void) { return m_nFPS; }
	static void SetFPS(int nFPS) { m_nFPS = nFPS; }

private:

	//静的メンバ変数
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad;
	static CDebugProc *m_pDebugProc;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CSceneManager *m_pSceneManager;
	static int m_nFPS;

	//メンバ変数
	HINSTANCE m_Instance; HWND m_Wnd; BOOL m_Window;

};

#endif
