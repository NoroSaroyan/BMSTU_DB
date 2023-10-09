#include <iostream>
#include "Student.h"

using namespace std;

Student students[50]{};
int border = 0;

void addStudent() {
    Student student{};
    cout
            << "Введите имя, фамилию, год рождения, год поступления, курс и группу студенту через пробел или через новой строки...\n";
    cin >> student.name
        >> student.surname
        >> student.birthYear
        >> student.entryYear
        >> student.year
        >> student.group;
    students[border] = student;
    border += 1;
}

int findLargestNameLength() {
    int max = -1;
    for (int i = 0; i < sizeof(students); ++i) {
        if (sizeof(students[i].name) > max) {
            max = sizeof(students[i].name);
        }
    }
    return max;
}

int findLargestSurnameLength() {
    int max = -1;
    for (int i = 0; i < sizeof(students); ++i) {
        if (sizeof(students[i].surname) > max) {
            max = sizeof(students[i].surname);
        }
    }
    return max;
}

void getAllStudents() {
    cout << "Имя   фамилия   год рождения   год поступления      курс      группа\n";
    for (auto &student: students) {
        cout << student.name << " " << student.surname << "   " << student.birthYear << "           "
             << student.entryYear << "                 "
             << student.year << "         " << student.group << "\n";
    }

}

void printCells() {
    int rows = 10;
    cout << "+\n";
    int nameLen = findLargestNameLength();
    int surnameLen = findLargestSurnameLength();
    int birthYearLen, entryYearLen = 4;
    int yearLen = 1;
    int groupLen = 3;


    for (int i = 0; i < rows * 2; ++i) {
        cout << "|\n";
    }
    cout << "+";
}

void showMenu() {
    cout << "Для выбора введите номер пункта \n\n";
    cout << "1.Ввод информации \n";
    cout << "2.Ввод информации из существующего текстового файла \n";
    cout << "3.Ввод информации из существующего бинарного файла \n";
    cout << "4.Вывод данных \n";
    cout << "5.Вывод данных в файл \n";
    cout << "6.Распечатка информации \n";
    cout << "7.Перевод базы данных в файл \n";
    cout << "8.Перевод содержимого текстового файла в бинарный файл \n";
    cout << "9.Добавление записи \n";
    cout << "10.Изменение записи \n";
    cout << "11.Удаление записи \n";
    cout << "12.Сортирова по любому из полей \n";
    cout << "13.Выход \n";
    cout << "\n";
}

void menuHandler(short choice) {

    switch (choice) {
        case 1:
            cout << "Ввод информации";
            break;
        case 2:
            cout << "Ввод информации из существующего текстового файла";

            break;
        case 3:
            cout << "Ввод информации из существующего бинарного файла";
            break;
        case 4:
            cout << "Вывод данных\n";
            getAllStudents();
            break;
        case 5:
            cout << "Вывод данных в файл";
            break;
        case 6:
            cout << "Распечатка иниформации ";
            break;
        case 7:
            cout << "Ввод информации из существующего текстового файла";
            break;
        case 8:
            cout << "Перевод содержимого текстового файла в бинарный файл";
            break;
        case 9:
            cout << "Добавление записи \n";
            addStudent();
            break;
        case 10:
            cout << "Изменение записи";
            break;
        case 11:
            cout << "Удаление записи";
            break;
        case 12:
            cout << "Сортирова по любому из полей";
            break;
        case 13:
            cout << "Выход";
            exit(0);
        default:
            cout << "Такого пункта нет в меню... \n";
            break;
    }
}

int main() {
//    while (true) {
//        showMenu();
//        short choice;
//        cout << "Введите номер пункта меню: ";
//        cin >> choice;
//        menuHandler(choice);
//    }
    printCells();
    return 0;
}

