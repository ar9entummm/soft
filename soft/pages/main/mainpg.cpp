#include "mainpg.h"
#include <ncurses.h>
#include <vector>
#include <iostream>
#include "../../main.h"

using namespace std;

void mainPg() {
    vector<Option> options = {
        Option(0, "Discord", [](int index){callback(1);}),
        Option(1, "VK", [](int index){callback(2);}),
        Option(2, "Telegram", [](int index){callback(3);})
    };

    int choice;
    int highlights = 0;

    writeOptions(options, highlights);

    while (true) {
        choice = getch();
        switch (choice) {
            case KEY_UP:
                mvaddstr(highlights, options[highlights].get_name().length() + 5, "  ");

            highlights = (highlights == 0) ? options.size() - 1 : highlights - 1;

            break;

            case KEY_DOWN:
                mvaddstr(highlights, options[highlights].get_name().length() + 5, "  ");

            highlights = (highlights == options.size() - 1) ? 0 : highlights + 1;

            break;

            case 10:
                options[highlights].ex_callback(10);
            break;
        }

        writeOptions(options, highlights);
        refresh();
    }

    mvaddstr(options.size() + 1, 0, "Управление: стрелки вверх/вниз, Enter для выбора");
}

void callback(int index) {
    printw("option: %i", index);
}
