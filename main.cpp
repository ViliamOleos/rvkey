#include <windows.h>
#include <iostream>
#include <cstdio>

DWORD replacer = {}; // initializing this var so it doesn't carry rubbish
INPUT keytrain[256] = {}; // woohoo the coding train! https://www.youtube.com/@TheCodingTrain

LRESULT CALLBACK TST_BTNhookproc(int ncode, WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_KEYDOWN && lParam != NULL) { // keydown could be problematic, ill change it later
        std::cout<<((LPKBDLLHOOKSTRUCT)lParam)->vkCode<<' '; // print pressed keys

        if(!replacer){
            replacer = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        }

        switch(((LPKBDLLHOOKSTRUCT)lParam)->vkCode) { // switch statement because this one fits nicely
            case 27: // case escape key pressed then
                PostQuitMessage(0); // quit program
            case 81: // the q key
                keytrain[0].type = INPUT_KEYBOARD;
                keytrain[0].ki.wVk = replacer;

                SendInput(ARRAYSIZE(keytrain), keytrain, sizeof(INPUT)); // it should simulate the key "replacer"
                return 1;
        }

        //return ((LPKBDLLHOOKSTRUCT)lParam)->vkCode==84; // if key = T then never heard of a T being pressed end
    }

    return CallNextHookEx(NULL, ncode, wParam, lParam); // pass the torch
}

int main()
{
    HHOOK TST_BTN = SetWindowsHookExW(WH_KEYBOARD_LL, TST_BTNhookproc,  NULL, 0); // h o o k e n g
    // imagine DWORD replacer here if that makes it easier
    MSG mesag; // carrier of the button master

    while (GetMessage(&mesag, NULL, 0, 0)) { // macrosoft hate this trick!
        TranslateMessage(&mesag);
        DispatchMessage(&mesag);
    }

    UnhookWindowsHookEx(TST_BTN); // baye

    return 0;
}
