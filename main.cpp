#include <iostream>
#include <windows.h>

using namespace std;

LRESULT CALLBACK TST_BTNhookproc(int ncode, WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_KEYDOWN && lParam != NULL) { // keydown could be problematic, ill change it later
        std::cout<<((LPKBDLLHOOKSTRUCT)lParam)->vkCode<<' '; // T = 84

        if(((LPKBDLLHOOKSTRUCT)lParam)->vkCode==84) { // if key = T
            return true; // huh wdym never heard of a T being pressed
        }
    }

    return CallNextHookEx(NULL, ncode, wParam, lParam); // pass the torch
}

int main()
{
    HHOOK TST_BTN = SetWindowsHookExW(WH_KEYBOARD_LL, TST_BTNhookproc,  NULL, 0);

    MessageBoxW(NULL, L"hooking", L"", MB_ICONEXCLAMATION | MB_SYSTEMMODAL); // Dialogue Box duh

    UnhookWindowsHookEx(TST_BTN); // baye

    return 0;
}
