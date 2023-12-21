#include "op_headers.h"

Student *students = new Student[10000];
int border = sizeof(students) / sizeof(students[0]);

void writeStudentsToTextFile() {
    char filename[256];
    cout << "Введите название текстового файла: ";
    cin >> filename;

    ofstream out(filename);

    if (!out.is_open()) {
        cerr << "Ошибка с файлом: " << filename << endl;
        return;
    }

    for (int i = 0; i < border; ++i) {
        out << students[i].name << ' ' << students[i].surname << ' '
            << students[i].entryYear << ' ' << students[i].birthYear << ' '
            << students[i].year << ' ' << students[i].group << ' '
            << students[i].id << endl;
    }
    out.close();
}

void writeStudentsToBinaryFile() {
    char filename[200];
    cin >> filename;
    ofstream out(filename, ios::binary);
    if (out.is_open()) {
        for (int i = 0; i < border; ++i) {
            out.write((char *) &students[i], sizeof(Student));
        }
    } else {
        cout << "ошибка";
    }
    out.close();
}

void readStudentsFromTextFile() {
    char filename[256];
    cout << "Введите имя текстового файла: ";
    cin >> filename;

    ifstream in(filename);

    if (!in.is_open()) {
        cerr << "Ошибка: " << filename << endl;
        return;
    }

    while (in >> students[border].name >> students[border].surname
              >> students[border].entryYear >> students[border].birthYear
              >> students[border].year >> students[border].group
              >> students[border].id) {
        border++;
        checkSize();
    }
    in.close();
}

void readStudentsFromBinaryFile() {
    char fileName[256];
    cout << "Введите название двочного файла: ";
    cin >> fileName;

    ifstream in(fileName, ios::binary);
    if (in.is_open()) {
        Student temp{};
        cout << "data from file:\n";
        while (in.read((char *) &temp, sizeof(Student))) {
            students[border] = temp;
            border++;
            checkSize();
        }
    }
    in.close();
}

void convertTxtToBin() {
    char txtFileName[200];
    char binFileName[200];
    cout << "Введите название текстового файла(без .txt): ";
    cin >> txtFileName;
    cout << "Введите название бинарного файла(.bin в конце):";
    cin >> binFileName;
    ifstream in(txtFileName);
    ofstream out(binFileName, ios::binary);
    Student temp{};
    while (in >> temp.name >> temp.surname >> temp.entryYear >> temp.birthYear >> temp.year >> temp.group >> temp.id) {
        out.write((char *) &temp, sizeof(Student));
    }
    in.close();
    out.close();
}

bool compareStudents(const Student &a, const Student &b, int choice, bool reversed) {
    switch (choice) {
        case 1:
            return (reversed ? std::strcmp(b.name, a.name) : std::strcmp(a.name, b.name)) < 0;
        case 2:
            return (reversed ? std::strcmp(b.surname, a.surname) : std::strcmp(a.surname, b.surname)) < 0;
        case 3:
            return (reversed ? b.entryYear < a.entryYear : a.entryYear < b.entryYear);
        case 4:
            return (reversed ? b.birthYear < a.birthYear : a.birthYear < b.birthYear);
        case 5:
            return (reversed ? b.year < a.year : a.year < b.year);
        case 6:
            return (reversed ? std::strcmp(b.group, a.group) : std::strcmp(a.group, b.group)) < 0;
        case 7:
            return (reversed ? std::strcmp(b.id, a.id) : std::strcmp(a.id, b.id)) < 0;
        default:
            std::cout << "Неправильный выбор";
            return false;
    }
}

void swapStudents(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp;
}

void sortStudents(Student *students, int length, int choice, bool reversed) {
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (compareStudents(students[j], students[j + 1], choice, reversed)) {
                swapStudents(students[j], students[j + 1]);
            }
        }
    }
}

void printSortMenu() {
    int choice;
    int ascending;
    bool reversed = false;
    cout
            << "1-имя \n 2-фамилия\n 3-год поступления \n 4- год рождения \n 5- курс\n 6- группа \n 7- номер студенческого билета \n если хотите отменить операцию, введите 0 "
            << endl;
    cout << "Выберите поле, по которому хотите сортировать список: ";
    cin >> choice;
    if (choice > 7 || choice <= 0) {
        if (choice == 0) {
            return;
        }
        cout << "Вы выбрали несуществующий пункт, попробуйте еще раз: ";
        cin >> choice;
        cout << endl;
    }
    cout << "Введите 1, для сортировки в порядке возрастания и -1 для убывания: ";
    cin >> ascending;
    if (ascending == 0) {
        return;
    } else if (ascending == 1) {
        reversed = true;
    } else if (ascending == -1) {
        reversed = false;
    } else {
        cout << "Вы выбрали несуществующий пункт, попробуйте еще раз: ";
        cin >> ascending;
    }
    sortStudents(students, border, choice, reversed);
}

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

void sortStudentsByAge(int low, int high, bool reversed) {
    if (low < high) {
        int pivotIndex = partition(low, high, reversed);
        sortStudentsByAge(low, pivotIndex - 1, reversed);
        sortStudentsByAge(pivotIndex + 1, high, reversed);
    }
}

void addStudent() {
    Student student{};
    while (true) {
        cout << "введите имя" << endl;
        cin >> setw(40) >> student.name;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат имени. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cout << "Введите фамилию" << endl;
        cin >> setw(40) >> student.surname;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат фамилии. Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (true) {
        cout << "Введите Год рождения"<< endl;
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
        cout << "Введите год поступления" << endl;
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
        cout << "Введите курс(1-6)" << endl;
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
        cout << "Введите группу" << endl;
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
        cout << "Введите номер студенческого билета" << endl;
        cin >> setw(20) >> student.id;
        if (cin.fail()) {
            cerr << "Ошибка: неверный формат номера студенческого билета. Попробуйте еще раз.\n";
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
    cout << "Введите номер студенческого билета студента, данные которого вы хотите обновить: ";
    cin >> id;

    for (int i = 0; i < border; ++i) {
        if (strcmp(students[i].id, id) == 0) {
            cout << "Список названии полей(убедитесь, что правильно написали названия полей)\n";
            cout << "name, surname, entryYear, birthYear, year, group, id\n";
            cout << "Введите поля, которые вы хотите обновить (через запятую): ";
            char fields[100];
            cin >> fields;

            char *field = strtok(fields, ",");
            while (field != nullptr) {
                if (strcmp(field, "name") == 0) {
                    cout << "Введите новое имя: ";
                    cin >> setw(40) >> students[i].name;
                } else if (strcmp(field, "surname") == 0) {
                    cout << "Введите новую фамилию: ";
                    cin >> setw(40) >> students[i].surname;
                } else if (strcmp(field, "entryYear") == 0) {
                    while (true) {
                        cout << "Введите новый год поступления: ";
                        cin >> students[i].entryYear;
                        if (cin.fail() || students[i].entryYear < 2000 || students[i].entryYear > 2023) {
                            cerr << "Ошибка: неверный формат года поступления. Год должен быть в диапазоне от 2000 до 2023. Попробуйте еще раз.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                } else if (strcmp(field, "birthYear") == 0) {
                    while (true) {
                        cout << "Введите новый год рождения: ";
                        cin >> students[i].birthYear;
                        if (cin.fail() || students[i].birthYear < 1975 || students[i].birthYear > 2007) {
                            cerr << "Ошибка: неверный формат года рождения. Год должен быть в диапазоне от 1975 до 2007. Попробуйте еще раз.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                } else if (strcmp(field, "year") == 0) {
                    while (true) {
                        cout << "Введите новый год обучения: ";
                        cin >> students[i].year;
                        if (cin.fail() || students[i].year < 1 || students[i].year > 6) {
                            cerr << "Ошибка: неверный формат курса. Курс должен быть в диапазоне от 1 до 6. Попробуйте еще раз.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                } else if (strcmp(field, "group") == 0) {
                    while (true) {
                        cout << "Введите новую группу: ";
                        cin >> setw(12) >> students[i].group;
                        if (cin.fail()) {
                            cerr << "Ошибка: неверный формат группы. Попробуйте еще раз.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                } else if (strcmp(field, "id") == 0) {
                    while (true) {
                        cout << "Введите новый ID: ";
                        cin >> setw(20) >> students[i].id;
                        if (cin.fail()) {
                            cerr << "Ошибка: неверный формат номера студенческого билета. Попробуйте еще раз.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                }

                field = strtok(nullptr, ",");
            }
            return;
        }
    }
    cout << "Студент с указанным ID не найден." << endl;
}

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

void checkSize() {
    if (border == sizeof(&students)) {
        changeSize();
    }
}

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

void getAllStudents() {
    int maxLengths[7] = {sizeof("Name") - 1, sizeof("Surname") - 1, sizeof("Entry Year") - 1, sizeof("Birth Year") - 1,
                         sizeof("Year") - 1, sizeof("Group") - 1, sizeof("Id") - 1};

    for (int i = 0; i < border; i++) {
        if (strlen(students[i].name) > maxLengths[0]) maxLengths[0] = strlen(students[i].name);
        if (strlen(students[i].surname) > maxLengths[1]) maxLengths[1] = strlen(students[i].surname);
        if (sizeof(students[i].entryYear) > maxLengths[2])maxLengths[2] = sizeof(students[i].entryYear);
        if (sizeof(students[i].birthYear) > maxLengths[3])maxLengths[3] = sizeof(students[i].birthYear);
        if (sizeof(students[i].year) > maxLengths[4]) maxLengths[4] = sizeof(students[i].year);
        if (strlen(students[i].group) > maxLengths[5]) maxLengths[5] = strlen(students[i].group);
        if (strlen(students[i].id) > maxLengths[6]) maxLengths[6] = strlen(students[i].id);
    }

    cout << "| " << left << setw(maxLengths[0]) << "Name" << " | ";
    cout << left << setw(maxLengths[1]) << "Surname" << " | ";
    cout << left << setw(maxLengths[2]) << "Entry Year" << " | ";
    cout << left << setw(maxLengths[3]) << "Birth Year" << " | ";
    cout << left << setw(maxLengths[4]) << "Year" << " | ";
    cout << left << setw(maxLengths[5]) << "Group" << " |";
    cout << left << setw(maxLengths[6]) << "Id" << " |\n";

    for (int maxLength: maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";

    for (int i = 0; i < border; i++) {
        cout << "| " << left << setw(maxLengths[0]) << students[i].name << " | ";
        cout << left << setw(maxLengths[1]) << students[i].surname << " | ";
        cout << left << setw(maxLengths[2]) << students[i].entryYear << " | ";
        cout << left << setw(maxLengths[3]) << students[i].birthYear << " | ";
        cout << left << setw(maxLengths[4]) << students[i].year << " | ";
        cout << left << setw(maxLengths[5]) << students[i].group << " |";
        cout << left << setw(maxLengths[6]) << students[i].id << " |\n";
    }

    for (int maxLength: maxLengths) {
        cout << "+";
        for (int j = 0; j < maxLength + 2; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << "\n";
}

void request() {
    sortStudentsByAge(0, border - 1, true);
    cout << "Фамилия: " << students[0].surname << ", Год рождения: " << students[0].birthYear << endl;
    cout << "Фамилия: " << students[1].surname << ", Год рождения: " << students[1].birthYear << endl;
}

void showMenu() {
    cout << "Введите номер пункта меню:\n\n";
    cout << "1. Ввести информацию из существующего текстового файла\n";
    cout << "2. Ввести информацию из существующего двоичного файла\n";
    cout << "3. Отобразить данные\n";
    cout << "4. Вывести данные в бинарный файл\n";
    cout << "5. Выгрузить в текстовый файл\n";
    cout << "6. Преобразовать содержимое текстового файла в двоичный файл\n";
    cout << "7. Добавить запись\n";
    cout << "8. Изменить запись\n";
    cout << "9. Удалить запись\n";
    cout << "10. Сортировать по любому полю\n";
    cout << "11. Выход\n";
    cout << "12. Запрос\n";
    cout << "\n";
}

void menuHandler(short choice) {
    switch (choice) {
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
            cout << "Выгрузить данные в бинарный файл\n";
            writeStudentsToBinaryFile();
            break;
        case 5:
            cout << "Выгрузить в текстовый файл\n";
            writeStudentsToTextFile();
        case 6:
            cout << "Преобразовать содержимое текстового файла в двоичный файл\n";
            convertTxtToBin();
            break;
        case 7:
            cout << "Добавить нового студента\n";
            addStudent();
            break;
        case 8:
            cout << "Изменить запись\n";
            updateStudent();
            break;
        case 9:
            cout << "Удалить запись\n";
            deleteStudent();
            break;
        case 10:
            cout << "Сортировать по любому полю\n";
            printSortMenu();
            break;
        case 11:
            cout << "Выход\n";
            exit(0);
        case 12:
            cout << "Запрос\n";
            request();
        default:
            cout << "Неверный номер пункта меню.\n";
            break;
    }
}

int main() {
    setlocale(LC_ALL, "");
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