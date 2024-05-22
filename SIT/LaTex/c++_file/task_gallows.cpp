#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void output_v_(vector<char>& v_out) {
    for (auto it = v_out.begin(); it != v_out.end(); it++) {
        cout << *it;
    }
}

void check(vector<char>& v_out, vector <string> ::iterator word_it, string str, int& counter) {
    if (str.length() == 1) {//проверка буквы
        int flag = 0;//флаг угадал/не угадал букву 
        //если эта буква есть в слове и еще не была угадана, то раскрываем эту букву и
        //её расположение
        if (count((*word_it).begin(), (*word_it).end(), str[0]) > 0 &&
            count(v_out.begin(), v_out.end(), str[0]) == 0) {
            int index_c = 0;
            flag++;
            //находим позицию/позиции буквы и расскрываем её/их
            for (auto it = (*word_it).begin(); it != (*word_it).end(); it++) {
                if (*it == str[0]) {
                    v_out[index_c] = str[0];
                    counter++;
                }
                index_c++;
            }
        }
        if (counter == (*word_it).length()) {
            cout << endl << "Вы угадали все буквы" << endl;
            cout << "загаданное слово:" << endl;
            cout << *word_it << endl << endl;
        }
        else {
            if (flag == 0) {
                cout << "новая буква не угадана за этот ход" << endl;
            }
            else {
                cout << "за ход вы угадали новую букву" << endl;
            }
            //вывод уже отгаданых букв
            output_v_(v_out);
            cout << endl << endl;
        }

    }
    else {//проверка на угаданное слово целиком
        if (str == *word_it) {
            cout << endl << "Вы угадали слово" << endl;
            counter = (*word_it).length();
        }
    }
}


void task_gallows() {
    setlocale(LC_ALL, "RUS"); 
    cout << "ТОЛЬКО АНГЛИЙСКИЕ СЛОВА" << endl;
    vector <string> words_mas({
        "destiny","aragami","word",
        "admin", "apex","stack",
        "sword", "bow","coffee"
        });
    

    //рандомный выбор слова
    int rand_value;
    srand(time(0));
    rand_value = rand() % words_mas.size();
    auto word_it = words_mas.begin();
    advance(word_it, rand_value);//сдвиг итератора на нужное слово

    vector <char> v_out;
    cout << "слоты для букв(" << (*word_it).length() << "):" << endl;
    for (int i = 0; i < (*word_it).length(); i++) {
        v_out.push_back('_');
        cout << '_';
    }
    cout << endl;

    int steps = 1, steps_max = (*word_it).length() *2, counter = 0;
    //пока не угаданы все буквы в слове и пока не кончились ходы
    while (counter != (*word_it).length() && steps <= steps_max) {
        cout << "ход " << steps << " из " << steps_max << endl;
        cout << "введите слово/букву:" << endl;
        string str;
        cin >> str;//считываем слово/букву
        while (str.length() != (*word_it).length() && str.length() > 1) {
            cout << "неверный ввод: в слове отличное от вашего ввода кол-во букв" << endl;
            cout << "введите слово/букву:" << endl;
            cin >> str;
        }
        steps++;//засчитываем ход
        check(v_out, word_it, str, counter);//проверка
    }
    if (counter != (*word_it).length()) {
        cout << "Вы проиграли" << endl;
        cout << "загаданное слово:" << endl;
        cout << *word_it << endl;
    }
}

int main() {
    task_gallows();
}