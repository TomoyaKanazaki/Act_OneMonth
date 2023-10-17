//==========================================
//
//  UIクラス(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "gamemanager.h"
#include "renderer.h"
#include "enemy.h"
#include "camera.h"
#include "map.h"

//==========================================
//  コンストラクタ
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	m_bUpdate = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//ウィンドウハンドルの取得
	m_hWnd = CManager::GetManager()->GetWindowHandle();

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

	//カメラ操作
	SetCamera();

	//モード選択
	SelectMode();

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
		LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

		//ライティングをオフ
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//描画内容
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		//ライティングをオン
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//==========================================
//  モード選択処理
//==========================================
void CUi::SelectMode(void)
{
	//タブを生成
	if (ImGui::BeginTabBar(u8"モード変更", 0))
	{
		//エディットモード
		if (ImGui::BeginTabItem(u8"Set"))
		{
			ImGui::Text(u8"SetObject");
			Create();
			ImGui::EndTabItem();
		}

		//プレイモード
		if (ImGui::BeginTabItem(u8"Move"))
		{
			ImGui::Text(u8"MoveObject");
			Move();
			ImGui::EndTabItem();
		}

		ImGui::Separator();
		ImGui::TreePop();
	}
}

//==========================================
//  オブジェクトを生成する処理
//==========================================
void CUi::Create(void)
{
	//位置を移動
	ImGui::DragFloat3(u8"生成位置", m_pos);

	//敵を生成
	if (ImGui::Button(u8"生成!!!"))
	{
		CEnemy::Create(m_pos, CEnemy::NORMAL);
	}
}

//==========================================
//  オブジェクトを移動する処理
//==========================================
void CUi::Move(void)
{

}

//==========================================
//  カメラの設定
//==========================================
void CUi::SetCamera(void)
{
	//カメラの取得
	CCamera* pCamera = CGameManager::GetCamera();

	//デバッグ状態の切り替え
	if (ImGui::Button(u8"カメラ操作"))
	{
		pCamera->SwitchDebug();
	} ImGui::SameLine();

	//表示内容
	if (pCamera->GetDebug())
	{
		ImGui::Text("ON");
	}
	else
	{
		ImGui::Text("OFF");
	}

	//視点、注視点の取得
	D3DXVECTOR3 posR = pCamera->GetPosR();

	//視点、注視点の操作
	ImGui::Text(u8"カメラの操作");
	ImGui::DragFloat3(u8"視点", posR);

	//視点、注視点の設定
	pCamera->SetPosR(posR);
}

//==========================================
//  書き出し処理
//==========================================
void CUi::Save(void)
{
	if (ImGui::Button("Save"))
	{
		CMap::Save();
	}
}

//==========================================
//  読み込み処理
//==========================================
void CUi::Load(void)
{

}
