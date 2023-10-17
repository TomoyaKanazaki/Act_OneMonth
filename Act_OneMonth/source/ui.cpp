//==========================================
//
//  UI�N���X(ui.cpp)
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
//  �R���X�g���N�^
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	m_bUpdate = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�E�B���h�E�n���h���̎擾
	m_hWnd = CManager::GetManager()->GetWindowHandle();

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

	//�J��������
	SetCamera();

	//���[�h�I��
	SelectMode();

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
		LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

		//���C�e�B���O���I�t
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//�`����e
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		//���C�e�B���O���I��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//==========================================
//  ���[�h�I������
//==========================================
void CUi::SelectMode(void)
{
	//�^�u�𐶐�
	if (ImGui::BeginTabBar(u8"���[�h�ύX", 0))
	{
		//�G�f�B�b�g���[�h
		if (ImGui::BeginTabItem(u8"Set"))
		{
			ImGui::Text(u8"SetObject");
			Create();
			ImGui::EndTabItem();
		}

		//�v���C���[�h
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
//  �I�u�W�F�N�g�𐶐����鏈��
//==========================================
void CUi::Create(void)
{
	//�ʒu���ړ�
	ImGui::DragFloat3(u8"�����ʒu", m_pos);

	//�G�𐶐�
	if (ImGui::Button(u8"����!!!"))
	{
		CEnemy::Create(m_pos, CEnemy::NORMAL);
	}
}

//==========================================
//  �I�u�W�F�N�g���ړ����鏈��
//==========================================
void CUi::Move(void)
{

}

//==========================================
//  �J�����̐ݒ�
//==========================================
void CUi::SetCamera(void)
{
	//�J�����̎擾
	CCamera* pCamera = CGameManager::GetCamera();

	//�f�o�b�O��Ԃ̐؂�ւ�
	if (ImGui::Button(u8"�J��������"))
	{
		pCamera->SwitchDebug();
	} ImGui::SameLine();

	//�\�����e
	if (pCamera->GetDebug())
	{
		ImGui::Text("ON");
	}
	else
	{
		ImGui::Text("OFF");
	}

	//���_�A�����_�̎擾
	D3DXVECTOR3 posR = pCamera->GetPosR();

	//���_�A�����_�̑���
	ImGui::Text(u8"�J�����̑���");
	ImGui::DragFloat3(u8"���_", posR);

	//���_�A�����_�̐ݒ�
	pCamera->SetPosR(posR);
}

//==========================================
//  �����o������
//==========================================
void CUi::Save(void)
{
	if (ImGui::Button("Save"))
	{
		CMap::Save();
	}
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CUi::Load(void)
{

}
