//
// Created by Norik Saroyan on 06.10.23.
//

#ifndef BMSTU_DB_STUDENT_H
#define BMSTU_DB_STUDENT_H

struct Student {
    char name[30]{};
    char surname[30]{};
    short entryYear{};
    short birthYear{};
    unsigned short year{};
    char group[12]{};
    char id[20]{};
};


#endif //BMSTU_DB_STUDENT_H
