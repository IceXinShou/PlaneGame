#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

#define CENTER 0
#define CENTER_LEFT 1
#define ESC "\x1B"

using namespace std;


enum Type {
    BLANK,
    SLOW_STONE,
    STONE,
    FAST_STONE,
};

struct Paint {
    unsigned short x;
    unsigned short y;
    Type type;
};


namespace XsUtil {

    bool arrayBoolCheck(const bool* arr, int count);

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

    class Plane {
    public:
        unsigned short x = 0;
        unsigned short y = 0;
        unsigned short last_x = -1;
        unsigned short last_y = -1;
        Color color = CYAN;
        unsigned short gameSizeWidth = 70; // game size width
        unsigned short gameSizeHeight = 40; // game size high
        unsigned int hearts = 3; // plane's hearts
        unsigned int fps = 60; // game fps
        unsigned int planeWeigh = 9;
        unsigned int planeHeigh = 3;

        void init();

        void drawPlane();
    };

    class GUI {
        vector<string> mainWords = {"Project 05 : 013129 29 黃宥維", "<ENTER> Start To Play", "<O> Settings",
                                    "<ESC> Exit"};
        vector<string> settingWords = {"<1> Game Size", "<2> Plane's Hearts", "<3> Plane's FPS", "<ESC> Exit"};

    public:
        explicit GUI(Plane *data) { this->data = data; }; // constructor
        static void createMessage(const vector<string> &message, int position, Plane *data);;

        static int getMaxLength(vector<string> words);

        void main();

        void setting();

        static void printDefaultBorder(short width, short high);

        static void clearScreenWithoutBorder(short width, short height);

    private:
        Plane *data;
    };

    static void errorPrint(int errorCode); // game crash or report
    static void printRepeat(const char &c, int count); // repeat print out char
    static void printRepeat(const string &c, int count); // repeat print out string
    void print(const std::string &msg, Color background, Color font);;

    void print(const std::string &msg, Color font);;

    void gotoXY(short x, short y);


    class Setting {
        vector<string> gameOverWord = {"You Lose!"/*, "Press any key to continue"*/};
        vector<string> changeGameSizeWord = {"←  Width  →    |    ↑  High  ↓"};
        vector<string> changeHeartsWord = {"↑  Heart(s)  ↓"};
        vector<string> changeSpeedWord = {"↑  FPS  ↓"};

    public:
        explicit Setting(Plane *data) { this->data = data; };

        void start(); // no exit
        void changeGameSize(); // ! check whether string length suitable for new size
        void changeHeart();

        void changeSpeed();

        static void summonLaser(const unsigned short *width, const unsigned short *height, const short *status);

    private:
        Plane *data;
    };
}

#endif // MAIN_XSLIB_H