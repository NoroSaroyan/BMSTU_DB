#include "Student.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

Student *students = new Student[1000];
int border = sizeof(students) / sizeof(students[0]);

void save();

void checkSize();

void changeSize();

int partition(Student *students, int low, int high, bool reversed);

void sortStudentsByAge(Student *students, int low, int high, bool reversed);

void addStudent();

void getAllStudents();

void request();

void showMenu();

void deleteStudent();

void menuHandler(short choice);

void updateStudent();

void textToBinary() {
    char textFileName[256];
    char binaryFileName[256];

    std::cout << "Введите имя текстового файла: ";
    std::cin >> textFileName;

    std::cout << "Введите имя двоичного файла: ";
    std::cin >> binaryFileName;

    std::ifstream inputFile(textFileName);
    std::ofstream outputFile(binaryFileName, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия текстового файла: " << textFileName << std::endl;
        return;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Ошибка открытия бинарного файла: " << binaryFileName << std::endl;
        inputFile.close();
        return;
    }

    while (inputFile >> students[border].name >> students[border].surname
                     >> students[border].entryYear >> students[border].birthYear
                     >> students[border].year >> students[border].group
                     >> students[border].id) {
        border++; // Переход к следующему слоту в массиве
        if (border >= 1000) {
            break; // Избегаем переполнения буфера
        }
    }

    // Записываем весь массив в бинарный файл
    outputFile.write(reinterpret_cast<char *>(students), border * sizeof(Student));

    inputFile.close();
    outputFile.close();
}

void writeStudentsToTextFile() {
    char filename[256];
    std::cout << "Введите название текстового файла: ";
    std::cin >> filename;

    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Ошибка с файлом: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < border; ++i) {
        // Write student information to the text file
        outputFile << students[i].name << ' ' << students[i].surname << ' '
                   << students[i].entryYear << ' ' << students[i].birthYear << ' '
                   << students[i].year << ' ' << students[i].group << ' '
                   << students[i].id << std::endl;
    }

    outputFile.close();
}

void writeStudentsToBinaryFile() {
    char filename[256];
    std::cout << "Введите название двочного файла: ";
    std::cin >> filename;

    std::ofstream outputFile(filename, std::ios::binary);

    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: " << filename << std::endl;
        return;
    }

    outputFile.write(reinterpret_cast<char *>(students), border * sizeof(Student));

    outputFile.close();
}

void readStudentsFromTextFile() {
    char filename[256];
    std::cout << "Введите имя текстового файла: ";
    std::cin >> filename;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: " << filename << std::endl;
        return;
    }

    while (inputFile >> students[border].name >> students[border].surname
                     >> students[border].entryYear >> students[border].birthYear
                     >> students[border].year >> students[border].group
                     >> students[border].id) {
        border++; // Move to the next slot in the array
        checkSize();
    }
    inputFile.close();
}

void readStudentsFromBinaryFile() {
    char filename[256];
    std::cout << "Введите название двочного файла: ";
    std::cin >> filename;

    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: " << filename << std::endl;
        return;
    }

    // Read the entire array from the binary file
    inputFile.read(reinterpret_cast<char *>(students), border * sizeof(Student));

    // Calculate the new size based on the number of bytes read
    border = inputFile.gcount() / sizeof(Student);

    inputFile.close();
}


bool compareStudents(const Student &a, const Student &b, int field, bool ascending) {
    switch (field) {
        case 1:
            return (ascending) ? (std::strcmp(a.name, b.name) < 0) : (std::strcmp(a.name, b.name) > 0);
        case 2:
            return (ascending) ? (std::strcmp(a.surname, b.surname) < 0) : (std::strcmp(a.surname, b.surname) > 0);
        case 3:
            return (ascending) ? (a.entryYear < b.entryYear) : (a.entryYear > b.entryYear);
        case 4:
            return (ascending) ? (a.birthYear < b.birthYear) : (a.birthYear > b.birthYear);
        case 5:
            return (ascending) ? (a.year < b.year) : (a.year > b.year);
        case 6:
            return (ascending) ? (std::strcmp(a.group, b.group) < 0) : (std::strcmp(a.group, b.group) > 0);
        case 7:
            return (ascending) ? (std::strcmp(a.id, b.id) < 0) : (std::strcmp(a.id, b.id) > 0);
    }

    return false;  // Default case (field not recognized)
}

// Quicksort algorithm
void quicksort(int left, int right, int field, bool ascending) {
    int i = left, j = right;
    Student pivot = students[(left + right) / 2];

    while (i <= j) {
        while (compareStudents(students[i], pivot, field, ascending)) {
            i++;
        }

        while (compareStudents(pivot, students[j], field, ascending)) {
            j--;
        }

        if (i <= j) {
            // Swap elements at i and j
            std::swap(students[i], students[j]);
            i++;
            j--;
        }
    }

    // Recursive calls
    if (left < j) {
        quicksort(left, j, field, ascending);
    }
    if (i < right) {
        quicksort(i, right, field, ascending);
    }
}


//работает
int partition(int low, int high, bool reversed) {
    int pivot = students[high].birthYear;
    int i = low;

    for (int j = low; j < high; ++j) {
        if ((reversed && students[j].birthYear > pivot) || (!reversed && students[j].birthYear < pivot)) {
            swap(students[i], students[j]);
            ++i;
        }
    }
    swap(students[i], students[high]);
    return i;
}

//работает
void sortStudentsByAge(int low, int high, bool reversed) {
    if (low < high) {
        int pivotIndex = partition(low, high, reversed);
        sortStudentsByAge(low, pivotIndex - 1, reversed);
        sortStudentsByAge(pivotIndex + 1, high, reversed);
    }
}

void addStudent() {
    Student student{};
    std::cout
            << "Введите имя, фамилию, год рождения, год поступления, курс и группу студента (разделенные пробелами):\n";

    while (true) {
        std::cin >> setw(30) >> student.name;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат имени. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> setw(30) >> student.surname;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат фамилии. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> student.birthYear;
        if (cin.fail() || student.birthYear < 1975 || student.birthYear > 2007) {
            cerr
                    << "Ошибка: неверный формат года рождения. Год должен быть в диапазоне от 1975 до 2007. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> student.entryYear;
        if (cin.fail() || student.entryYear < 2000 || student.entryYear > 2023) {
            cerr
                    << "Ошибка: неверный формат года поступления. Год должен быть в диапазоне от 1900 до 2023. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> student.year;
        if (cin.fail() || student.year < 1 || student.year > 6) {
            cerr << "Ошибка: неверный формат курса. Курс должен быть в диапазоне от 1 до 6. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> setw(12) >> student.group;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат группы. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cin >> setw(20) >> student.id;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат номера зачетника. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    checkSize();
    students[border] = student;
    border += 1;
}

void updateStudent() {
    char id[20];
    std::cout << "Введите ID студента, которого вы хотите обновить: ";
    std::cin >> id;

    for (int i = 0; i < border; ++i) {
        if (strcmp(students[i].id, id) == 0) {
            std::cout << "Список названии полей(убедитесь, что правильно написали названия полей)\n";
            std::cout << "name, surname, entryYear, birthYear, year, group, id\n";
            std::cout << "Введите поля, которые вы хотите обновить (через запятую): ";
            char fields[100];
            std::cin >> fields;

            char *field = strtok(fields, ",");
            while (field != nullptr) {
                if (strcmp(field, "name") == 0) {
                    std::cout << "Введите новое имя: ";
                    std::cin >> students[i].name;
                } else if (strcmp(field, "surname") == 0) {
                    std::cout << "Введите новую фамилию: ";
                    std::cin >> students[i].surname;
                } else if (strcmp(field, "entryYear") == 0) {
                    std::cout << "Введите новый год поступления: ";
                    std::cin >> students[i].entryYear;
                } else if (strcmp(field, "birthYear") == 0) {
                    std::cout << "Введите новый год рождения: ";
                    std::cin >> students[i].birthYear;
                } else if (strcmp(field, "year") == 0) {
                    std::cout << "Введите новый год обучения: ";
                    std::cin >> students[i].year;
                } else if (strcmp(field, "group") == 0) {
                    std::cout << "Введите новую группу: ";
                    std::cin.ignore(); // Ignore the newline character
                    std::cin.getline(students[i].group, 12);
                } else if (strcmp(field, "id") == 0) {
                    std::cout << "Введите новый ID: ";
                    std::cin.ignore(); // Ignore the newline character
                    std::cin.getline(students[i].id, 20);
                }

                field = strtok(nullptr, ",");
            }
            return;
        }
    }

    std::cout << "Студент с указанным ID не найден." << std::endl;
}

//работает
void deleteStudent() {
    char stId[20];
    cout << "Введите номер студ.билета";
    cin >> stId;
    short idx = -100;
    if (border == 1) {
        delete[] students;
        border = 0;
        students = new Student[1000];
    } else {
        for (int i = 0; i < border - 1; ++i) {
            if (strcmp(students[i].id, stId) == 0) {
                idx = short(i);
            }
        }
        if (idx >= 0) {
            auto *_students = new Student[border - 1];
            for (int i = 0, j = 0; i < border; ++i) {
                if (i != int(idx)) {
                    _students[j] = students[i];
                    j++;
                }
            }
            delete[] students;
            students = _students;
            border--;
        } else {
            cout << "студент с таким номером студенческого билета не найден\n";

        }
    }

}

//работает
void checkSize() {
    if (border == sizeof(&students)) {
        changeSize();
    }
}

//работает
void changeSize() {
    int length = (border + 1) * 2;
    auto *newStudents = new Student[length];
    for (int i = 0; i <= border; ++i) {
        newStudents[i] = students[i];
    }
    *students = *new Student[length];
    for (int i = 0; i < border; ++i) {
        students[i] = newStudents[i];
    }
    delete[] newStudents;
}

//работает
void getAllStudents() {
    // Find max length for each column
    int maxLengths[7] = {sizeof("Name") - 1, sizeof("Surname") - 1, sizeof("Entry Year") - 1, sizeof("Birth Year") - 1,
                         sizeof("Year") - 1, sizeof("Group") - 1, sizeof("Id") - 1};
    for (int i = 0; i < border; i++) {
        if (sizeof(students[i].name) > maxLengths[0]) maxLengths[0] = sizeof(students[i].name);
        if (sizeof(students[i].surname) > maxLengths[1]) maxLengths[1] = sizeof(students[i].surname);
        if (sizeof(students[i].entryYear) > maxLengths[2]) maxLengths[2] = sizeof(students[i].entryYear);
        if (sizeof(students[i].birthYear) > maxLengths[3]) maxLengths[3] = sizeof(students[i].birthYear);
        if (sizeof(students[i].year) > maxLengths[4]) maxLengths[4] = sizeof(students[i].year);
        if (sizeof(students[i].group) > maxLengths[5]) maxLengths[5] = sizeof(students[i].group);
        if (sizeof(students[i].id) > maxLengths[6]) maxLengths[6] = sizeof(students[i].id);
    }

    // Print header row
    cout << "| " << left << setw(maxLengths[0]) << "Name" << " | ";
    cout << left << setw(maxLengths[1]) << "Surname" << " | ";
    cout << left << setw(maxLengths[2]) << "Entry Year" << " | ";
    cout << left << setw(maxLengths[3]) << "Birth Year" << " | ";
    cout << left << setw(maxLengths[4]) << "Year" << " | ";
    cout << left << setw(maxLengths[5]) << "Group" << " |";
    cout << left << setw(maxLengths[6]) << "Id" << " |\n";

    // Print separator row
    for (int maxLength: maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";

    // Print data rows
    for (int i = 0; i < border; i++) {
        cout << "| " << left << setw(maxLengths[0]) << students[i].name << " | ";
        cout << left << setw(maxLengths[1]) << students[i].surname << " | ";
        cout << left << setw(maxLengths[2]) << students[i].entryYear << " | ";
        cout << left << setw(maxLengths[3]) << students[i].birthYear << " | ";
        cout << left << setw(maxLengths[4]) << students[i].year << " | ";
        cout << left << setw(maxLengths[5]) << students[i].group << " |";
        cout << left << setw(maxLengths[6]) << students[i].id << " |\n";
    }

    // Print footer row
    for (int maxLength: maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";
}


//Запрос: Получить фамилии и группы двух самых молодых студентов по возрасту
// работает
void request() {
    sortStudentsByAge(0, border - 1, true);
    cout << "Фамилия: " << students[0].surname << ", Год рождения: " << students[0].birthYear << endl;
    cout << "Фамилия: " << students[1].surname << ", Год рождения: " << students[1].birthYear << endl;
}

//работает
void showMenu() {
    cout << "Введите номер пункта меню:\n\n";
    cout << "0. Ввести информацию\n";
    cout << "1. Ввести информацию из существующего текстового файла\n";
    cout << "2. Ввести информацию из существующего двоичного файла\n";
    cout << "3. Отобразить данные\n";
    cout << "4. Вывести данные в файл\n";
    cout << "5. Распечатать информацию\n";
    cout << "6. Преобразовать базу данных в файл\n";
    cout << "7. Преобразовать содержимое текстового файла в двоичный файл\n";
    cout << "8. Добавить запись\n";
    cout << "9. Изменить запись\n";
    cout << "10. Удалить запись\n";
    cout << "11. Сортировать по любому полю\n";
    cout << "12. Выход\n";
    cout << "13. Запрос\n";
    cout << "\n";
}

//работает
void menuHandler(short choice) {
    switch (choice) {
        case 0:
            cout << "Ввести информацию\n";
            break;
        case 1:
            cout << "Ввести информацию из существующего текстового файла\n";
            readStudentsFromTextFile();
            break;
        case 2:
            cout << "Ввести информацию из существующего двоичного файла\n";
            readStudentsFromBinaryFile();
            break;
        case 3:
            cout << "Отобразить данные\n";
            getAllStudents();
            break;
        case 4:
            cout << "Вывести данные в бинарный файл\n";
            writeStudentsToBinaryFile();
            break;
        case 5:
            cout << "Распечатать информацию\n";
            break;
        case 6:
            cout << "Преобразовать базу данных в текстовый файл\n";
            writeStudentsToTextFile();
            break;
        case 7:
            cout << "Преобразовать содержимое текстового файла в двоичный файл\n";
            textToBinary();
            break;
        case 8:
            cout << "Добавить запись\n";
            addStudent();
            break;
        case 9:
            cout << "Изменить запись\n";
            updateStudent();
            break;
        case 10:
            cout << "Удалить запись\n";
            deleteStudent();
            break;
        case 11:
            cout << "Сортировать по любому полю\n";
//            добавить сортировку по любому полю

            break;
        case 12:
            cout << "Выход\n";
            exit(0);
        case 13:
            cout << "Запрос\n";
            request();
        default:
            cout << "Неверный номер пункта меню.\n";
            break;
    }
}

int main() {
    while (true) {

        showMenu();
        short choice;
        cout << "Введите номер пункта меню: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Пожалуйста, введите правильный номер пункта меню: ";
        }
        menuHandler(choice);
    }
}
