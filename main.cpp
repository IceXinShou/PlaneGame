#include "player.h"

#define MAIN -1
#define SETTING -2

using namespace XsUtil;

// Class borderGUI

void waitForInput(int type, Setting setting);

HANDLE console; // batch setting handler

int main() {
    system("chcp 65001 | cls"); // UTF-8
    auto *snakeData = new Plane();
    Setting setting = Setting(snakeData, new GUI(snakeData));
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == INVALID_HANDLE_VALUE)
        return GetLastError();

    SetConsoleCursorInfo(console, new CONSOLE_CURSOR_INFO{1, false});

    // Show Selections

    waitForInput(MAIN, setting);
}

void waitForInput(int type, Setting setting) {
    setting.borderGUI();
    switch (type) {
        case MAIN: { // gui selections
            setting.mainGUI();
            switch (_getwch()) {
                case 13:  // Enter
                    setting.start();
                    break;
                case 111:  // O
                    waitForInput(SETTING, setting);
                    return;
                case 27: // Esc
                    exit(0);
                default:
                    waitForInput(type, setting);
            }
        }
        case SETTING: { // setting selections
            setting.configGUI();
            switch (_getwch()) {
                case 49: // 1
                    setting.changeGameSize();
                    break;
                case 50: // Space
                    setting.changeHeart();
                    break;
                case 51: // Page Up
                    setting.changeFPS();
                    break;
                case 27: // Esc
                    waitForInput(MAIN, setting);
                    return;
                default:
                    waitForInput(type, setting);
            }

            waitForInput(SETTING, setting);
            break;
        }
    }
}