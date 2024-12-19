#include <ncurses.h>
#include <iostream>
#include <locale.h>
#include <string>
#include <vector>
#include "main.h"
#include <fstream>
#include "pages/main/mainpg.h"

using namespace std;

const string config = "config.ini";

void writeConfig() {
    ofstream file(config);
    if (file.is_open()) {
        file << "[Settings]\n";
        file << "token=";
        file.close();
    } else {
        cerr << "Не удалось открыть файл конфига";
    }
}

void writeTokenToFile(const string& token) {
    ifstream infile(config);
    string line;
    string content;
    bool tokenFound = false;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.find("token=") != string::npos) {
                content += "token=" + token + "\n";
                tokenFound = true;
            } else {
                content += line + "\n";
            }
        }
        infile.close();

        if (!tokenFound) {
            content += "token=" + token + "\n";
        }

        ofstream outfile(config);
        if (outfile.is_open()) {
            outfile << content;
            outfile.close();
            cout << "Токен успешно записан в файл." << endl;
        } else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}


Option::Option(int idx, string nm, function<void(int index)> cb) : index(idx), name(nm), callback(cb) {}

void Option::ex_callback(int index){
    if (callback){
        callback(index);
    }
}

string Option::get_name() const{
    return name;
}

int Option::get_index() const{
    return index;
}

void init() {
    setlocale(LC_ALL, "");
    initscr();
    erase();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (!has_colors()) {
        endwin();
        printf("Терминал не поддерживает цвета.\n");
        return;
    }

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

void writeOptions(const vector<Option>& options, int highlights) {
    for (int i = 0; i < options.size(); i++) {
        string index_str = "[" + to_string(i + 1) + "] ";
        string name_str = options[i].get_name();

        if (highlights == i) {
            name_str += " <";
        }

        attron(COLOR_PAIR(5));
        mvaddstr(i, 0, index_str.c_str());
        attroff(COLOR_PAIR(5));

        mvaddstr(i, index_str.length(), name_str.c_str());
    }
}

void getInput(char* input, int length) {
    echo();
    curs_set(1);
    move(1, 0);
    getnstr(input, length-1);
    noecho();
    curs_set(0);
}

int main() {
    init();

    bool token = false;
    if (token) {
        mainPg();
    }
    else {
        char input[100];

        while (true) {
            clear();
            mvprintw(0, 0, "Введите токен вашего аккаунта дискорд:");
            refresh();
            getInput(input, 100);
            if (strlen(input) > 0) {
                clear();
                mvprintw(0,0, "token: %s", input);
                refresh();
                break;
            }
        }
    }
    while (true)
    endwin();
    return 0;
}
