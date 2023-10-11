//==========================================
//
//  UI�N���X(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	m_bUpdate = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CUi::~CUi()
{

}

//==========================================
//  ����������
//==========================================
void CUi::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�E�B���h�E�n���h���̎擾
	m_hWnd = CManager::GetWindowHandle();

	//ImGui���̐ݒ�
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//�g�p����t�H���g
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//�t�H���g�T�C�Y
	const float FontSize = 15.0f;

	//�����̐ݒ�
	ImGuiIO& io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�X�^�C���̐ݒ�
	ImGui::StyleColorsLight();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX9_Init(pDevice);
}

//==========================================
//  �I������
//==========================================
void CUi::Uninit(void)
{
	//ImGui���I��
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  �X�V����
//==========================================
void CUi::Update(void)
{
	//ImGui�̎��s
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//�E�B���h�E�̐���
	ImGui::Begin(u8"MapEditor");

	//�E�B���h�E�̏I��
	ImGui::End();

	//�X�V�̏I��
	ImGui::EndFrame();

	//�X�V�t���O�̍X�V
	if (!m_bUpdate)
	{
		m_bUpdate = true;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CUi::Draw(void)
{
	if (m_bUpdate)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���C�e�B���O���I�t
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//�`����e
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		//���C�e�B���O���I��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
