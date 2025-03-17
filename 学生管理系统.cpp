#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
typedef struct _student {
    char id[10];
    char name[10];
    int age;
    char gender[4];
    char birthday[20];
    char address[50];
    struct _student* next;
} Student;
Student* readStudentTable() {
    Student* headNode = (Student*)malloc(sizeof(Student));
    if (headNode == NULL) return NULL;
    headNode->next = NULL;
    Student* p = headNode;

    FILE* fp = fopen("D:\\Zlw_computer\\VS\\学生信息管理系统\\StudentTable.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return NULL;
    }

    while (!feof(fp)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (fscanf(fp, "%s%s%d%s%s%s", newStudent->id, newStudent->name,
            &newStudent->age, newStudent->gender, newStudent->birthday, newStudent->address) == 6) {
            newStudent->next = NULL;
            p->next = newStudent;
            p = newStudent;
        }
        else {
            free(newStudent);
            break;
        }
    }

    fclose(fp);
    return headNode;
}

void printList(Student* list) {
	if(list == NULL){
		cout<<"woshidashabi"<<endl;
		return;
	}
    Student* p = list->next; // 从第一个有效节点开始打印
    printf("-----------------buhao----------------\n");
    printf("学号\t姓名\t年龄\t性别\t生日\t籍贯\n");
    while (p != NULL) {
        printf("%s\t%s\t%d\t%s\t%s\t%s\n", p->id, p->name,
            p->age, p->gender, p->birthday, p->address);
        p = p->next;
    }
    printf("-----------------hao----------------\n\n");
}

int main() {
    Student* list = readStudentTable();
    printList(list);
    return 0;
}

