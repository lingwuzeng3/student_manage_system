#include"studentManageSystem.h"

int main()
{
    int numOfStudent = 0;
    //建立一个学生链表，将文件中所有学生录入链表
    Student* list = readStudentTable(&numOfStudent);
    int num;
    welcome();
    while ((scanf("%d",&num)) != EOF) {
        
        switch (num) {
        case 1:
            system("cls");
            //学生信息浏览功能
            printList(list);
            printf("总共有 %d 名学生在系统中！\n", numOfStudent);
            break;
        case 2:
            system("cls");
            //学生信息录入功能
            addStudent(list);
            numOfStudent++;
            break;
        case 3:
            system("cls");
            //学生信息修改功能
            changeStudent(list);
            break;
        case 4:
            system("cls");
            //学生信息删除功能
            deleteStudent(list);
            break;
        case 5:
            system("cls");
            //学生信息查询功能
            findStudent(list);
            break;
        case 6:
            system("cls");
            //学生信息排序功能
            sortStudent(list,numOfStudent);
            printList(list);
            break;
        case 7:
            system("cls");
            //学生信息统计功能
            countStudent(list);
            break;
        case 8:
            outputStudentTable(list);
            exit(0);
        default:
            break;
        }
        welcome();
    }
}

//录入学生，建立链表
Student* readStudentTable(int* numOfStudent) {
    Student* headNode = (Student*)malloc(sizeof(Student));
    if (headNode == NULL) return NULL;
    headNode->next = NULL;
    Student* p = headNode;

    FILE* fp = fopen("StudentTableInput.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return NULL;
    }

    while (!feof(fp)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        (*numOfStudent)++;
        if (fscanf(fp, "%s %s %d %s %s %s %s", newStudent->id, newStudent->name,
            &newStudent->age, newStudent->gender, newStudent->birthday, newStudent->address,newStudent->identity) == 7) {
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

//把所有学生输出到文件中
void outputStudentTable(Student* list){
    Student* p = list->next;
    FILE* fp = fopen("StudentTableInput.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return ;
    }
    while (p != NULL) {

        if (fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name,
            p->age, p->gender, p->birthday, p->address,p->identity) < 0) {
            printf("输出失败！\n");
            return;
        }
        p = p->next;
    }

    fclose(fp);
    printf("输出成功！\n");
}

//增加新学生
Student* addStudent(Student* list) {
    Student* newNode = (Student*)malloc(sizeof(Student));
    printf("input the new student message please:\n(如：001 张三 20 男 2000-01-01 江西 群众)\n");
    if(scanf("%s%s%d%s%s%s%s", newNode->id, newNode->name, &newNode->age,
            newNode->gender, newNode->birthday, newNode->address,newNode->identity) != 7 ){
        printf("录入学生失败！\n");
    }
    else {
        printf("成功录入学生!\n");
    }
    newNode->next = list->next;
    list->next = newNode;
    return list;
}

//修改学生信息
Student* changeStudent(Student* list) {
    //获取修改学生Id
    printf("please input change student's id:\n");
    char uid[10];
    if (scanf("%s", uid) != 1) {
        return NULL;
    }
    //从链表中找到修改学生
    Student* p = list->next;
    while (p != NULL) {
        bool flag = true;
        for (int i = 0; i < 10; i++) {
            //比较有效Id
            if (uid[i] < 0) {
                break;
            }
            if (uid[i] != p->id[i]) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            break;
        }
        p = p->next;
    }
    //选择修改内容
    printf("please input the number you want to change\n"
        "1.id   2.name   3.age   4.gender   5.birthdat   6.address 7.identity\n");
    int num;
    if (scanf("%d", &num) != 1) {
        return NULL;
    }
    if (num > 7 || num < 0) {
        printf("输入错误！");
        return list;
    }
    switch (num) {
    case 1:
        printf("please input new id: ");
        if (scanf("%s", p->id) != 1) {
            return NULL;
        }
        break;
    case 2:
        printf("please input new name: ");
        if (scanf("%s", p->name) != 1) {
            return NULL;
        }
        break;
    case 3:
        printf("please input new age: ");
        if (scanf("%d", &p->age) != 1) {
            return NULL;
        }
        break;
    case 4:
        printf("please input new geader: ");
        if (scanf("%s", p->gender) != 1) {
            return NULL;
        }
        break;
    case 5:
        printf("please input new birthday: ");
        if (scanf("%s", p->birthday) != 1) {
            return NULL;
        }
        break;
    case 6:
        printf("please input new address: ");
        if (scanf("%s", p->address) != 1) {
            return NULL;
        }
    case 7:
        printf("please input new identity: ");
        if (scanf("%s", p->identity) != 1) {
            return NULL;
        }
        break;
    default:
        break;
    }
    printf("修改成功！\n");
    return list;
}

//删除学生信息
Student* deleteStudent(Student* list) {
    //p为需删除节点，frontNode为其前驱节点
    Student* frontNode = list;
    Student* p = list->next;
    printf("please delete student's id:\n");
    char uid[10];
    if (scanf("%s", uid) != 1) {
        return NULL;
    }
    //从链表中找到修改学生
    while (p != NULL) {
        bool flag = true;
        for (int i = 0; i < 10; i++) {
            //比较有效Id
            if (uid[i] < 0) {
                break;
            }
            if (uid[i] != p->id[i]) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            break;
        }
        frontNode = p;
        p = p->next;
    }
    frontNode->next = p->next;
    free(p);
    printf("删除成功！\n");
    return list;
}

//查询学生信息
void findStudent(Student* list) {
    //获取查询学生Id
    printf("please input the student's id:\n");
    char uid[10];
    if (scanf("%s", uid) != 1) {
        return ;
    }
    //从链表中找到需查询学生
    Student* p = list->next;
    while (p != NULL) {
        bool flag = true;
        for (int i = 0; i < 10; i++) {
            //比较有效Id
            if (uid[i] < 0) {
                break;
            }
            if (uid[i] != p->id[i]) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            break;
        }
        p = p->next;
    }
    printf("the message are following:\n"
        "%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name, p->age, p->gender, p->birthday, p->address,p->identity);

}

// 按学号排序学生
void sortStudent(Student* list,int numOfStudent) {
    
    for (int i = 1; i < numOfStudent; i++) {
        Student* p = list->next;
        Student* q = p->next;
        while (q != NULL) {
            if (strcmp(p->id,q->id) > 0) {
                swap(p, q);
            }
            p = p->next;
            q = p->next;
        }
    }
}

//交换两个链表的信息
void swap(Student* p, Student* q) {
    char temp[50];
    int t;
    //交换Id
    strcpy(temp, q->id);
    strcpy(q->id,p->id);
    strcpy(p->id,temp);
    //交换name
    strcpy(temp, q->name);
    strcpy(q->name,p->name);
    strcpy(p->name,temp); 
    //交换age
    t = q->age;
    q->age = p->age;
    p->age = t;
    //交换gender
    strcpy(temp, q->gender);
    strcpy(q->gender,p->gender);
    strcpy(p->gender,temp);
    //交换birthday
    strcpy(temp, q->birthday);
    strcpy(q->birthday,p->birthday);
    strcpy(p->birthday,temp);
    //交换address
    strcpy(temp, q->address);
    strcpy(q->address,p->address);
    strcpy(p->address,temp);
    //交换identity
    strcpy(temp, q->identity);
    strcpy(q->identity,p->identity);
    strcpy(p->identity,temp);

}

//统计学生信息
void countStudent(Student* list) {
    Student* p = list->next;
    printf("please input message you wannna count:\n1.age   2.gender   3.address   4.identity\n");
    int num,cnt=0;
    if (scanf("%d", &num) != 1 || (num > 4 || num < 0)) {
        printf("统计失败！\n");
        return; 
    }
    switch (num){
        case 1:
            printf("please input the count age: ");
            int agei;
            scanf("%d", &agei);
            if (agei < 0) {
                printf("输入错误年龄！");
                return;
            }
            while (p) {
                if (p->age == agei) {
                    cnt++;
                    printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name, p->age, p->gender, p->birthday, p->address,p->identity);
                }
                p = p->next;
            }
            break;
        case 2:
            printf("please input the count gender: 男/女\n");
            char genderi[4];
            scanf("%s", genderi);
            while (p) {
                if (strcmp(p->gender,genderi) == 0) {
                    cnt++;
                    printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name, p->age, p->gender, p->birthday, p->address, p->identity);
                }
                p = p->next;
            }
            break;
        case 3:
            printf("please input the count address: (如江西/北京/上海)\n");
            char addressi[50];
            scanf("%s", addressi);
            while (p) {
                if (strcmp(p->address,addressi) == 0) {
                    cnt++;
                    printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name, p->age, p->gender, p->birthday, p->address, p->identity);
                }
                p = p->next;
            }
            break; 
        case 4:
            printf("please input the count identity:(如党员/团员/群众)\n");
            char identityi[50];
            scanf("%s", identityi);
            while (p) {
                if (strcmp(p->identity,identityi) == 0) {
                    cnt++;
                    printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name, p->age, p->gender, p->birthday, p->address, p->identity);
                }
                p = p->next;
            }
            break;
    }
    printf("共有%d名学生！\n", cnt);
}

//打印输出学生表
void printList(Student* list) {
    Student* p = list->next; // 从第一个有效节点开始打印
    printf("\n----------------------------------------------------\n");
    printf("学号\t姓名\t年龄\t性别\t生日\t\t籍贯\t政治面貌\n");
    while (p != NULL) {
        printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\n", p->id, p->name,
            p->age, p->gender, p->birthday, p->address,p->identity);
        p = p->next;
    }
    printf("----------------------------------------------------\n\n");
}

//欢迎界面
void welcome() {
    printf("welcome to Student Manage System:\n");
	//printf("---------------------------------\n");
	printf("1.输出所有学生信息\n");
	printf("2.录入学生信息\n");
	printf("3.修改学生信息\n");
	printf("4.删除学生信息\n");
	printf("5.查询学生信息\n");
	printf("6.排序学生信息\n");
	printf("7.统计学生信息\n");
	printf("8.输出学生表\n");
	//printf("---------------------------------\n");
    printf("please input your choice: \n");
	
}

