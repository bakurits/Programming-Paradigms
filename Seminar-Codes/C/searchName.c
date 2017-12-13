#include <search.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
    char* lastName;
    int age;
} student;

int compare(student* first, student* second) {
    return (strcmp(first->name, second->name) |
             strcmp(first->lastName, second->lastName));
}

void makeStudent(student* curStudent, char* name, char* lastName, int age) {
    curStudent->age = age;
    curStudent->name = name;
    curStudent->lastName = lastName;
}

int main() {
    size_t siz = 2;
    student students[siz];
    student curStudent;

    makeStudent(&students[0], "bakur", "tsut", 19);
    makeStudent(&students[1], "gvantsa", "tsut", 18);
    makeStudent(&curStudent, "eeWW", "tsut", -1);

    printf("%s %s %d\n", students[1].name, students[1].lastName, students[1].age); 
    printf("%s %s %d\n", curStudent.name, curStudent.lastName, curStudent.age); 

    student* findedStudent = (student*) lsearch(&curStudent, students, &siz, sizeof(student), 
    (int (*)(const void *, const void *)) compare);

    makeStudent(&curStudent, "bakur", "tsut", -1);

    if (findedStudent == NULL) {
        printf("%s\n", "Can't Find");
    } else {
        printf("%s %s %d\n", findedStudent->name, findedStudent->lastName, findedStudent->age); 
    }
}