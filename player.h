#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

#define CENTER 0
#define CENTER_LEFT 1
#define ESC "\x1B"
#define SHOOTED 1
#define AMMO_STOP -1

using namespace std;

enum Color : int {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

static void errorPrint(int errorCode); // game crash or report
static void printRepeat(const char &c, int count); // repeat print out char
static void printRepeat(const string &c, int count); // repeat print out string
void print(const std::string &msg, Color background, Color font);;

void print(const std::string &msg, Color font);;

void gotoXY(short x, short y);


enum Type {
    BLANK,
    LASER,
};

struct Paint {
    unsigned short x;
    unsigned short y;
    Type type;
};

struct Laser {
    bool changed = false;
    unsigned short x{};
    short last_x{};
    unsigned short y{};
    short last_y{};
    unsigned short status{};
};

void summonLazer(unsigned short *player_x, unsigned short *weigh, unsigned short *height, short *stop);


class Plane {
public:
    bool leftBarrier = false;
    bool rightBarrier = false;
    unsigned short planex[255 * 255]{};
    unsigned short planey[255 * 255]{};
    unsigned short foodx[255 * 255]{};
    unsigned short foody[255 * 255]{};
    unsigned short coordinate_x = 0;
    unsigned short coordinate_y = 0;
    unsigned int foodCount = 2;
    unsigned int length = 3;
    unsigned int lengthNow = 0;
    unsigned int offset = 0;
    Color color = RED;
    unsigned short gameSizeWidth = 70; // game size width
    unsigned short gameSizeHeight = 40; // game size high
    unsigned int hearts = 3; // snake's hearts
    unsigned int fps = 60; // snake's fps
    unsigned int planeWeigh = 11;
    unsigned int planeHeigh = 3;

    void init();

    void drawPlane(short x, short y) const;
};


namespace XsUtil {
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

}


namespace XsSetting {

    class Setting {
        vector<string> gameOverWord = {"You Lose!"/*, "Press any key to continue"*/};
        vector<string> changeGameSizeWord = {"←  Width  →    |    ↑  High  ↓"};
        vector<string> changeHeartsWord = {"↑  Heart(s)  ↓"};
        vector<string> changeSpeedWord = {"↑  FPS  ↓"};

    public:
        explicit Setting(Plane *data) { this->data = data; };

        static void *keyEvent(void *wch);

        [[noreturn]] void start(); // no exit
        void changeGameSize(); // ! check whether string length suitable for new size
        void changeHeart();

        void changeSpeed();

        void movePlane(char key);

        void drawPlane();

    private:
        Plane *data;
    };

}

#endif // MAIN_XSLIB_H