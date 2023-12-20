//
// Created by Norik Saroyan on 21.12.23.
//

#ifndef BMSTU_DB_OP_HEADERS_H
#define BMSTU_DB_OP_HEADERS_H

#include "Student.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std;

void checkSize();

void changeSize();

void addStudent();

void getAllStudents();

void request();

void showMenu();

void deleteStudent();

void menuHandler(short choice);

void updateStudent();

void convertTxtToBin();

void writeStudentsToTextFile();

void writeStudentsToBinaryFile();

void readStudentsFromTextFile();

void readStudentsFromBinaryFile();

void printSortMenu();

void sortStudentsByAge(int low, int high, bool reversed);

int partition(int low, int high, bool reversed);

bool compareStudents(const Student &a, const Student &b, int choice, bool reversed);

void swapStudents(Student &a, Student &b);

void sortStudents(Student *students, int length, int choice, bool reversed);

#endif //BMSTU_DB_OP_HEADERS_H
