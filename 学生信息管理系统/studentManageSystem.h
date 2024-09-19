#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS  1
#pragma warning(disable:6031)
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;
//学生结构体声明
typedef struct _student {
    char id[10] = {0};
    char name[10];
    int age;
    char gender[4];
    char birthday[20];
    char address[50];
    char identity[10];
    struct _student* next;
} Student;

Student* readStudentTable(int* numOfStudent);
void outputStudentTable(Student* list);
void printList(Student* list);
Student* addStudent(Student* list);
Student* deleteStudent(Student* list);
Student* changeStudent(Student* list);
void findStudent(Student* list);
void sortStudent(Student* list,int numOfStudent);
void countStudent(Student* list);
void welcome();
void swap(Student* p, Student* q);