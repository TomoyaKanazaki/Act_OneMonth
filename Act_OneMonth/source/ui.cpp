//==========================================
//
//  UIクラス(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	m_bUpdate = false;
}

//==========================================
//  デストラクタ
//==========================================
CUi::~CUi()
{

}

//==========================================
//  初期化処理
//==========================================
void CUi::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ウィンドウハンドルの取得
	m_hWnd = CManager::GetWindowHandle();

	//ImGui環境の設定
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//使用するフォント
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//フォントサイズ
	const float FontSize = 15.0f;

	//文字の設定
	ImGuiIO& io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGuiスタイルの設定
	ImGui::StyleColorsLight();

	//プラットフォーム/レンダラーとバックエンドの設定
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX9_Init(pDevice);
}

//==========================================
//  終了処理
//==========================================
void CUi::Uninit(void)
{
	//ImGuiを終了
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  更新処理
//==========================================
void CUi::Update(void)
{
	//ImGuiの実行
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ウィンドウの生成
	ImGui::Begin(u8"MapEditor");

	//ウィンドウの終了
	ImGui::End();

	//更新の終了
	ImGui::EndFrame();

	//更新フラグの更新
	if (!m_bUpdate)
	{
		m_bUpdate = true;
	}
}

//==========================================
//  描画処理
//==========================================
void CUi::Draw(void)
{
	if (m_bUpdate)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//ライティングをオフ
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//描画内容
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		//ライティングをオン
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
