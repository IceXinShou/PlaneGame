#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

#define CENTER 0
#define CENTER_LEFT 1
#define ESC "\x1B"
#define K_UP 0b00000001
#define K_DOWN 0b00000010
#define K_LEFT 0b00000100
#define K_RIGHT 0b00001000
#define K_LSHIFT 0b00010000
#define K_CTRL 0b00100000
#define K_ESC 0b01000000
#define K_TAB 0b10000000

namespace XsUtil {
    void getKeyStatus(byte *keyStatus, const bool *run, bool *refresh, int delay);

    enum DropType {
        BLANK,
        SLOW_STONE,
        STONE,
        FAST_STONE,
    };

    struct Paint {
        unsigned short x;
        unsigned short y;
        DropType type;
    };

    enum Color : int {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGRAY,
        DARKGRAY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE,
    };

    bool arrayBoolCheck(const bool *arr, int count);

    class Plane {
    public:
        Color color = CYAN;
        unsigned short x = 0;
        unsigned short y = 0;
        unsigned short last_x = -1;
        unsigned short last_y = -1;
        unsigned short gameSizeWidth = 70; // game size width
        unsigned short gameSizeHeight = 40; // game size high
        unsigned int hearts = 3; // plane's hearts
        unsigned int fps = 60; // game fps
        unsigned int planeWeigh = 9;
        unsigned int planeHeight = 3;

        void init();

        void drawPlane();
    };

    class GUI {
        std::vector<std::string> mainWords = {"Project 05 : 013129 29 黃宥維", "<ENTER> Start To Play", "<O> Settings",
                                              "<ESC> Exit"};
        std::vector<std::string> settingWords = {"<1> Game Size", "<2> Plane's Hearts", "<3> Plane's FPS",
                                                 "<ESC> Exit"};

    public:
        explicit GUI(Plane *data) { this->data = data; };

        void createMessage(const std::vector<std::string> &message, int position);

        int getMaxLength(std::vector<std::string> words);

        void main();

        void setting();

        void printDefaultBorder();

        void clearScreenWithoutBorder();

    private:
        Plane *data;
    };

    static void errorPrint(int errorCode); // game crash or report
    static void printRepeat(const std::string &c, int count); // repeat print out string

    void print(const std::string &msg, Color font);;

    void gotoXY(short x, short y);


    class Setting {
        std::vector<std::string> gameOverWord = {"You Lose!"/*, "Press any key to continue"*/};
        std::vector<std::string> changeGameSizeWord = {"←  Width  →    |    ↑  High  ↓"};
        std::vector<std::string> changeHeartsWord = {"↑  Heart(s)  ↓"};
        std::vector<std::string> changeFPSWord = {"↑  FPS  ↓"};

    public:
        explicit Setting(Plane *data, GUI *gui) {
            this->data = data;
            this->gui = gui;
        };
        void borderGUI();
        void mainGUI();
        void start();
        void configGUI();
        void changeGameSize(); // ! check whether string length suitable for new size
        void changeHeart();

        void changeFPS();

        static void summonStone(const unsigned short *width, const unsigned short *height, const short *status);

    private:
        Plane *data;
        GUI *gui;
    };
}

#endif // MAIN_XSLIB_H