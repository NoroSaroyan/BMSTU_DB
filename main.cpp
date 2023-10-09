#include "Student.h"
#include "iostream"
#include <iomanip>
#include "array"

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

void getAllStudents() {
    // Find max length for each column
    int maxLengths[6] = {sizeof("Name") - 1, sizeof("Surname") - 1, sizeof("Entry Year") - 1, sizeof("Birth Year") - 1,
                         sizeof("Year") - 1, sizeof("Group") - 1};
    for (int i = 0; i < size(students); i++) {
        if (sizeof(students[i].name) > maxLengths[0]) maxLengths[0] = sizeof(students[i].name);
        if (sizeof(students[i].surname) > maxLengths[1]) maxLengths[1] = sizeof(students[i].surname);
        if (sizeof(students[i].entryYear) > maxLengths[2]) maxLengths[2] = sizeof(students[i].entryYear);
        if (sizeof(students[i].birthYear) > maxLengths[3]) maxLengths[3] = sizeof(students[i].birthYear);
        if (sizeof(students[i].year) > maxLengths[4]) maxLengths[4] = sizeof(students[i].year);
        if (sizeof(students[i].group) > maxLengths[5]) maxLengths[5] = sizeof(students[i].group);
    }

    // Print header row
    cout << "| " << left << setw(maxLengths[0]) << "Name" << " | ";
    cout << left << setw(maxLengths[1]) << "Surname" << " | ";
    cout << left << setw(maxLengths[2]) << "Entry Year" << " | ";
    cout << left << setw(maxLengths[3]) << "Birth Year" << " | ";
    cout << left << setw(maxLengths[4]) << "Year" << " | ";
    cout << left << setw(maxLengths[5]) << "Group" << " |\n";

    // Print separator row
    for (int maxLength : maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";

    // Print data rows
    for (int i = 0; i < size(students); i++) {
        cout << "| " << left << setw(maxLengths[0]) << students[i].name << " | ";
        cout << left << setw(maxLengths[1]) << students[i].surname << " | ";
        cout << left << setw(maxLengths[2]) << students[i].entryYear << " | ";
        cout << left << setw(maxLengths[3]) << students[i].birthYear << " | ";
        cout << left << setw(maxLengths[4]) << students[i].year << " | ";
        cout << left << setw(maxLengths[5]) << students[i].group << " |\n";
    }

    // Print footer row
    for (int maxLength : maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";
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
    while (true) {
        showMenu();
        short choice;
        cout << "Введите номер пункта меню: ";
        cin >> choice;
        menuHandler(choice);
    }
    return 0;
}

