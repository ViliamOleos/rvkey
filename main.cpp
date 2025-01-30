#include <windows.h>
#include <iostream>
#include <cstdio>

LRESULT CALLBACK TST_BTNhookproc(int ncode, WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_KEYDOWN && lParam != NULL) { // keydown could be problematic, ill change it later
        std::cout<<((LPKBDLLHOOKSTRUCT)lParam)->vkCode<<' '; // T = 84

        return ((LPKBDLLHOOKSTRUCT)lParam)->vkCode==84; // if key = T then never heard of a T being pressed end
    }

    return CallNextHookEx(NULL, ncode, wParam, lParam); // pass the torch
}

int main()
{
    HHOOK TST_BTN = SetWindowsHookExW(WH_KEYBOARD_LL, TST_BTNhookproc,  NULL, 0);
    MSG mesag;


    while (GetMessage(&mesag, NULL, 0, 0)) {
        TranslateMessage(&mesag);
        DispatchMessage(&mesag);
    }

    UnhookWindowsHookEx(TST_BTN); // baye

    return 0;
}
