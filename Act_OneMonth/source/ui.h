//==========================================
//
//  UI�N���X(ui.h)
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
//  �N���X��`
//==========================================
class CUi
{
public:

	//�����o�֐�
	CUi();
	~CUi();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	//�񋓌^��`
	enum EMode
	{
		SET_OBJECT = 0, //�ݒu���[�h
		MOVE_OBJECT, //�ړ����[�h
		MAX
	};

	//�����o�֐�
	void SelectMode(void);
	void Create(void);
	void Move(void);
	void SetCamera(void);

	//�����o�ϐ�
	HWND m_hWnd; //�E�B���h�E�n���h��
	bool m_bUpdate; //�X�V�t���O
	D3DXVECTOR3 m_pos; //�����ʒu

};

#endif
