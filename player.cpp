#include "player.h"

using namespace XsUtil;

extern HANDLE console; // batch setting handler
namespace XsUtil {

    void GUI::main() {
        XsUtil::GUI::createMessage(mainWords, CENTER_LEFT, data);
    }

    void GUI::setting() {
        XsUtil::GUI::createMessage(settingWords, CENTER_LEFT, data);
    }

    int GUI::getMaxLength(vector<string> words) {
        return int((*std::max_element(words.begin(), words.end(),
                                      [](const auto &a, const auto &b) { return a.size() < b.size(); })).length());
    }

    void GUI::createMessage(const vector<string> &message, int position, Plane *data) {
        switch (position) {
            case CENTER: {
                clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);

                SetConsoleCursorPosition(console, {0, 1});

                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Plane's Heart(s): %d\n"
                       "║ - Plane's FPS: %d\n",
                       data->gameSizeWidth, data->gameSizeHeight, data->hearts, data->fps);
                short firstLine = (data->gameSizeHeight - 5) / 2.0f + 0.5f;
                for (const auto &i: message) {
                    SetConsoleCursorPosition(console,
                                             {short((data->gameSizeWidth - 2 - i.length()) / 2.0f), firstLine++});
                    printf("%s", i.c_str());
                }
                break;
            }
            case CENTER_LEFT: {
                short space = (data->gameSizeWidth - getMaxLength(message)) >> 1;
//                printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);
                clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
                SetConsoleCursorPosition(console, {0, 1});
                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Plane's Heart(s): %d\n"
                       "║ - Plane's FPS: %d\n",
                       data->gameSizeWidth, data->gameSizeHeight, data->hearts, data->fps);
                short firstLine = (data->gameSizeHeight - 6) / 2.0f + 0.5f;

                for (const string &i: message) {
                    SetConsoleCursorPosition(console, {space, firstLine++});
                    printf("%s", i.c_str());
                }

                break;
            }
        }
    }

    void GUI::printDefaultBorder(short width, short high) {
        system("cls");
        SetConsoleCursorPosition(console, {0, 0});
        printf("╔");
        printRepeat("═", width - 2);
        printf("╗\n");
        for (short i = 0; i < high - 2; ++i) {
            short posY = i + 1;
            SetConsoleCursorPosition(console, {0, posY});
            printf("║");
            SetConsoleCursorPosition(console, {short(width - 1), posY});
            printf("║");
        }
        printf("\n╚");
        printRepeat("═", width - 2);
        printf("╝");
    }

    void GUI::clearScreenWithoutBorder(short width, short height) {
        for (short i = 1; i < height - 1; ++i) {
            SetConsoleCursorPosition(console, {1, i});
            printf(ESC"[%dX", width - 2);
        }
    }

    void print(const std::string &msg, Color background, Color font) {
        SetConsoleTextAttribute(console, background * 16 + font);
        printf("%s", msg.c_str());
        SetConsoleTextAttribute(console, LIGHTGRAY);
    }

    void print(const std::string &msg, Color font) {
        SetConsoleTextAttribute(console, font);
        printf("%s", msg.c_str());
        SetConsoleTextAttribute(console, LIGHTGRAY);
    }

    void gotoXY(short x, short y) {
        SetConsoleCursorPosition(console, {x, y});
    }

    void printRepeat(const string &c, int count) {
        if (count < 0) errorPrint(-1);
        while (count--)
            cout << c;
    }

    void printRepeat(const char &c, int count) {
        if (count < 0) errorPrint(-1);
        while (count--)
            printf("%c", c);
    }

    void errorPrint(int errorCode) {
        printf("\n\n-\n");
        if (errorCode < 0) {
            printf("Game had crash and shutdown by error: ");
            switch (errorCode) {
                case -1:
                    printf("Repeat number could not be negative!");
                    break;
            }
        } else {
            printf("Game met an error: ");
            switch (errorCode) {
                case 1:
                    printf("Something here!");
                    break;
            }
        }
        printf("\n-\n\n");
        if (errorCode < 0) exit(0);
    }

    bool arrayBoolCheck(const bool *arr, int count) {
        for (int i = 0; i < count; ++i) {
            if (*(arr + count))
                return true;
        }
        return false;
    }


    void Setting::changeGameSize() {
        while (true) {
            XsUtil::GUI::printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);
            XsUtil::GUI::createMessage(changeGameSizeWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->gameSizeHeight < 255)
                            data->gameSizeHeight += 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->gameSizeHeight > 1)
                            data->gameSizeHeight -= 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->gameSizeHeight < 246)
                            data->gameSizeHeight += 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->gameSizeHeight > 10)
                            data->gameSizeHeight -= 10;
                        break;
                        // ---------------------------------
                    case 75:
                        // code for arrow left
                        if (data->gameSizeWidth > 1)
                            data->gameSizeWidth -= 1;
                        break;
                    case 77:
                        // code for arrow right
                        if (data->gameSizeWidth < 255)
                            data->gameSizeWidth += 1;
                        break;
                    case 116:
                        // code for ctrl arrow right
                        if (data->gameSizeWidth < 246)
                            data->gameSizeWidth += 10;
                        break;
                    case 115:
                        // code for ctrl arrow left
                        if (data->gameSizeWidth > 10)
                            data->gameSizeWidth -= 10;
                        break;
                    default:
                        break;
                }
            else break;
        }
    }

    void Setting::changeHeart() {
        while (true) {
            XsUtil::GUI::createMessage(changeHeartsWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->hearts > 1)
                            data->hearts -= 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->hearts < 4294967295)
                            data->hearts += 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->hearts > 10)
                            data->hearts -= 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->hearts < 4294967286)
                            data->hearts += 10;
                        break;
                    default:
                        break;
                }
            else break;
        }
    }


    void Setting::changeSpeed() {
        while (true) {
            XsUtil::GUI::createMessage(changeSpeedWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->fps > 1)
                            data->fps -= 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->fps < 4294967295)
                            data->fps += 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->fps > 10)
                            data->fps -= 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->fps < 4294967286)
                            data->fps += 10;
                        break;
                    default:
                        break;
                }
            else break;
        }
    }


    mutex m;
    std::random_device dev;
    std::mt19937 rng(dev());
    queue<Paint *> paintsQueue;
    uniform_int_distribution<mt19937::result_type> rand(1, 1000); // distribution in range [1, 1000]
    void Setting::summonLaser(const unsigned short *width, const unsigned short *height, const short *status) {

        // generate a random laser
        int randNum = rand(rng);
        int waitTime = (randNum % 35) + 20; // ms
        unsigned short x = (randNum * randNum % (*width - 6)) + 3;
        unsigned short y = 1;

        // change laser
        while (*status == 1) {
            ++y;

            m.lock();

            // erase old paint
            paintsQueue.push(new Paint{x, (unsigned short) (y - 1), BLANK});

            // if hit the border
            if ((*height - 1) == y) {
                m.unlock();
                break;
            }
            if (waitTime <= 20)
                paintsQueue.push(new Paint{x, (unsigned short) (y), FAST_STONE});
            else if (waitTime >= 40)
                paintsQueue.push(new Paint{x, (unsigned short) (y), SLOW_STONE});
            else
                paintsQueue.push(new Paint{x, (unsigned short) (y), STONE});

            m.unlock();

            this_thread::sleep_for(chrono::milliseconds(waitTime));
        }
    }

    void Setting::start() {
        SetConsoleCursorInfo(console, new CONSOLE_CURSOR_INFO{1, false});
        XsUtil::GUI::clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
        data->init();

        // render setting
        bool gameMap[data->gameSizeHeight][data->gameSizeWidth]; // rock

        for (int i = 0; i < data->gameSizeHeight; ++i) {
            for (int j = 0; j < data->gameSizeWidth; ++j) {
                gameMap[i][j] = false;
            }
        }

        float fps = data->fps;
        struct timeval last{}, now = {0, 0}, secTimer = {0, 0};
        long renderTime = 0;
        long maxRenTime = 0;
        long delayTime = 0;
        mingw_gettimeofday(&now, nullptr);

        short game_status = 1;
        int counter = 0;
        float difficult = (data->gameSizeWidth / 2.0 - data->gameSizeWidth / 10.0);
        difficult -= int(difficult) % 30;
        float timer = 40 - difficult;

        vector<thread> laserThread;
        while (true) {

            // timer to generate laser
            if (++counter >= timer) {
                counter = 0;
                if (timer > 30)
                    timer -= 0.03 * (30 - difficult);
                else if (timer > 20)
                    timer -= 0.03 * (10 - int(difficult) % 10);
                else if (timer > 10)
                    timer -= 0.03;
                else if (difficult >= 25)
                    timer -= 0.02;
                thread(summonLaser, &data->gameSizeWidth, &data->gameSizeHeight, &game_status).detach();
            }
            // print

            m.lock();
            while (!paintsQueue.empty()) {
                Paint *p = paintsQueue.front();
                paintsQueue.pop();

                if (p->type == BLANK)
                    gameMap[p->y][p->x] = false;
                else
                    gameMap[p->y][p->x] = true;

                gotoXY(p->x, p->y);
                switch (p->type) {
                    case BLANK:
                        printf("  ");
                        break;

                    case SLOW_STONE:
                        print("▆▆", GREEN);
                        break;

                    case STONE:
                        print("▆▆", YELLOW);
                        break;

                    case FAST_STONE:
                        print("▆▆", RED);
                        break;
                }
            }
            m.unlock();

            // check plane alive
            /*
            bool *l1 = gameMap[data->x + 2] + data->y;
            bool *l2 = gameMap[data->x] + data->y + 1;
            bool *l3 = gameMap[data->x] + data->y + 2;
            if (arrayBoolCheck(l1, 5) || arrayBoolCheck(l2, 9) || arrayBoolCheck(l3, 9)) {
                XsUtil::GUI::createMessage(gameOverWord, CENTER, data);
                return;
            }
            */


            // print plane
            data->drawPlane();
            data->last_x = data->x;
            data->last_y = data->y;

            // move plane
            if (!((0x8000 & GetAsyncKeyState(VK_LEFT)) && (0x8000 & GetAsyncKeyState(VK_RIGHT)))) {

                // left press
                if (0x8000 & GetAsyncKeyState(VK_LEFT)) {
                    if (data->x > 1)
                        data->x--;

                } else if (0x8000 & GetAsyncKeyState(VK_RIGHT)) {
                    // right press
                    if (data->x < data->gameSizeWidth - data->planeWeigh - 1)
                        data->x++;
                }
            }
            if (!((0x8000 & GetAsyncKeyState(VK_UP)) && (0x8000 & GetAsyncKeyState(VK_DOWN)))) {

                // up press
                if (0x8000 & GetAsyncKeyState(VK_UP)) {
                    if (data->y > 2.5)
                        data->y--;
                } else if (0x8000 & GetAsyncKeyState(VK_DOWN)) {
                    // down press
                    if (data->y < data->gameSizeHeight - data->planeHeigh - 1.5)
                        data->y++;
                }
            }

            // print info data
            gotoXY(1, 1);
            printf(ESC
                   "[0m"
                   ESC
                   "[%dX FPS: %.2f\tRender Used: %.2fms / Max: %.2fms ",
                   data->gameSizeWidth - 2,
                   (renderTime + delayTime) == 0 ? 1000000 : 1000000.f / (renderTime + delayTime),
                   (float) renderTime / 1000.f,
                   (float) maxRenTime / 1000.f
            );

            // timer
            last = now;
            mingw_gettimeofday(&now, nullptr);
            renderTime = (now.tv_sec - last.tv_sec) * 1000000L +
                         (now.tv_usec - last.tv_usec);
            if ((now.tv_sec - secTimer.tv_sec) * 1000000L +
                (now.tv_usec - secTimer.tv_usec) >
                1000000L) {
                secTimer = now;
                maxRenTime = renderTime;
            }
            if (renderTime > maxRenTime) maxRenTime = renderTime;

            // update delay
            delayTime = 1000000 / fps - renderTime;
            if (delayTime > 0) {
                struct timespec ts = {0, delayTime * 1000};
                nanosleep(&ts, &ts);
            } else
                delayTime = 0;
            mingw_gettimeofday(&now, nullptr);

        }
    }


    void Plane::init() {
        x = gameSizeWidth / 2.0 - 5.5;
        y = gameSizeHeight / 2.0 + 4.5;
    }

    void Plane::drawPlane()  {

        // erase old
        if (last_x != -1 || last_y != -1) {
            XsUtil::gotoXY(last_x + 2, last_y);
            print("     ", color);
            gotoXY(last_x, last_y + 1);
            print("         ", color);
            gotoXY(last_x, last_y + 2);
            print("         ", color);
        }

        // print new
        gotoXY(x + 2, y);
        print("__|__", color);
        gotoXY(x, y + 1);
        print("---(_)---", color);
        gotoXY(x, y + 2);
        print("O 0   O O", color);
    }
}
