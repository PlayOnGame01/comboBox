#include <windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hList, hButton, hEdit;

TCHAR str[100];
TCHAR str_radio_box1[100];
TCHAR str_radio_box2[100];
TCHAR str_radio_box3[100];

int rand_time = 0, min_time = 5, max_time = 30;
int number = 0, number_min = -5, number_max = 30;
int mass[100];
long long result = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

void RandNum() {
	number = number_min + rand() % (number_max - number_min + 1);
	if (number == 0) {
		number = number_min + rand() % (number_max - number_min + 1);
	}
	wsprintf(str, TEXT("%d"), number);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT info, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));
	switch (info)
	{
	case WM_INITDIALOG: {
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
	}
	break;
	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_BUTTON1) {
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			rand_time = min_time + rand() % (max_time - min_time + 1);
			for (int i = 0; i < rand_time; i++) {
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
				RandNum();
				mass[i] = number;
			}
		}
		if (LOWORD(wParam) == IDC_RADIO1) {
			for (int i = 0; i < rand_time - 1; i++) {
				result += mass[i];
			}
			wsprintf(str_radio_box1, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box1));
			result = 0;
		}
		if (LOWORD(wParam) == IDC_RADIO2) {
			result = mass[0];
			for (int i = 1; i < rand_time - 1; i++) {
				result *= mass[i];
			}
			wsprintf(str_radio_box2, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box2));
			result = 0;
		}
		if (LOWORD(wParam) == IDC_RADIO3) {
			for (int i = 0; i < rand_time - 1; i++) {
				result += mass[i];
			}
			result /= rand_time;
			double rez = 123.23;
			wsprintf(str_radio_box3, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box3));
			result = 0;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}