#include "pch.h"
#include "CWindowContainer.h"
#include "CInput.h"

CWindowContainer::CWindowContainer()
{
	static bool raw_input_initialized = false;
	if (false == raw_input_initialized)
	{
		RAWINPUTDEVICE rawInputDevice;
		rawInputDevice.usUsagePage = 0x01;	// mouse
		rawInputDevice.usUsage = 0x02;
		rawInputDevice.dwFlags = 0;
		rawInputDevice.hwndTarget = NULL;

		if (FALSE == RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)))
		{
			MessageBox(nullptr, L"Failed to register raw input devices.", L"¿¡·¯", MB_OK);
			exit(-1);
		}

		raw_input_initialized = true;
	}
}

int CWindowContainer::WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
		// keyboard message
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(_wParam);

		const bool wasPressed = _lParam & KF_REPEAT;

		if (wasPressed)
			CInput::GetInst()->OnKeyPressed(keycode);
		else
			CInput::GetInst()->OnKeyHold(keycode);

		return 0;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(_wParam);

		const bool wasReleased = _lParam & KF_UP;

		if (wasReleased)
			CInput::GetInst()->OnKeyInvalided(keycode);
		else
			CInput::GetInst()->OnKeyReleased(keycode);

		return 0;
	}

	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(_wParam);

		CInput::GetInst()->OnChar(ch);

		return 0;
	}
	// mouse message
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);
		CInput::GetInst()->OnMouseMove(x, y);

		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasPressed = _lParam & KF_REPEAT;

		if (!wasPressed)
			CInput::GetInst()->OnLeftPressed(x, y);
		else
			CInput::GetInst()->OnLeftPressed(x, y);


		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasReleased = _lParam & KF_UP;

		if (wasReleased)
			CInput::GetInst()->OnLeftReleased(x, y);
		else
			CInput::GetInst()->OnLeftReleased(x, y);


		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasPressed = _lParam & KF_REPEAT;

		if (!wasPressed)
			CInput::GetInst()->OnRightPressed(x, y);
		else
			CInput::GetInst()->OnRightPressed(x, y);


		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasReleased = _lParam & KF_UP;

		if (wasReleased)
			CInput::GetInst()->OnRightReleased(x, y);
		else
			CInput::GetInst()->OnRightReleased(x, y);

		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasPressed = _lParam & KF_REPEAT;

		if (!wasPressed)
			CInput::GetInst()->OnMiddlePressed(x, y);
		else
			CInput::GetInst()->OnMiddlePressed(x, y);


		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		const bool wasReleased = _lParam & KF_UP;

		if (wasReleased)
			CInput::GetInst()->OnMiddleReleased(x, y);
		else
			CInput::GetInst()->OnMiddleReleased(x, y);

		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(_lParam);
		int y = HIWORD(_lParam);

		if (GET_WHEEL_DELTA_WPARAM(_wParam) > 0)
			CInput::GetInst()->OnWheelUp(x, y);

		else if (GET_WHEEL_DELTA_WPARAM(_wParam) < 0)
			CInput::GetInst()->OnWheelDown(x, y);

		return 0;
	}
	case WM_INPUT:
	{
		UINT dataSize = 0;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));	// Need to populate data size first
		if (0 < dataSize)
		{
			std::unique_ptr<BYTE[]> rawData = std::make_unique<BYTE[]>(dataSize);

			if (dataSize == GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER)))
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());

				if (RIM_TYPEMOUSE == raw->header.dwType)
					CInput::GetInst()->OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			}
		}

		return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	}
	default:
		return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	}
}
