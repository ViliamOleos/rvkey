#include <iostream>
#include <windows.h>

using namespace std;

LRESULT CALLBACK TST_BTNhookproc(int ncode, WPARAM wParam, LPARAM lParam) {
    if (wParam == WM_KEYDOWN && lParam != NULL)
    {
        std::cout<<"keydown ";

        if (((LPKBDLLHOOKSTRUCT)lParam)->vkCode == 0x4A)
        {
            std::cout<<"j ";
            return 1;
        }
    }

    return CallNextHookEx(NULL, ncode, wParam, lParam);
}

int main()
{
    HHOOK TST_BTN = SetWindowsHookExW(WH_KEYBOARD_LL, TST_BTNhookproc,  NULL, 0);

    MessageBoxW(NULL, L"hooking", L"", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

    UnhookWindowsHookEx(TST_BTN);

    return 0;
}
