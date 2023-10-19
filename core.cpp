// mbnq.pl 2023


#include <iostream>
#include <Windows.h>

int main() {
    SetConsoleTitle(TEXT("Write from clipboard -- mbnq.pl"));
    std::cout << "Press CTRL+INSERT to paste clipboard contents..." << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_INSERT)) {
            if (OpenClipboard(NULL)) {
                HANDLE hClipboardData = GetClipboardData(CF_TEXT);
                char* clipText = static_cast<char*>(GlobalLock(hClipboardData));
                GlobalUnlock(hClipboardData);

                for (int i = 0; i < strlen(clipText); i++) {
                    INPUT input[2];
                    input[0].type = INPUT_KEYBOARD;
                    input[0].ki.wVk = 0;
                    input[0].ki.wScan = clipText[i];
                    input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    input[0].ki.time = 0;
                    input[0].ki.dwExtraInfo = 0;

                    input[1].type = INPUT_KEYBOARD;
                    input[1].ki.wVk = 0;
                    input[1].ki.wScan = clipText[i];
                    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
                    input[1].ki.time = 0;
                    input[1].ki.dwExtraInfo = 0;

                    SendInput(2, input, sizeof(INPUT));

                    // Delay between key presses
                    Sleep(10);
                }

                CloseClipboard();
            }
        }
        Sleep(10);
    }

    return 0;
}
