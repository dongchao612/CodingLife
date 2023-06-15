#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define NAMENAMESIZE 32
#define MAXTELSIZE 12
#define MAXSSTUIZE 1024

typedef struct Student
{
    int id;
    char name[NAMENAMESIZE];
    int age;
    char tel[MAXTELSIZE];
} Stu;
Stu *g_info[MAXSSTUIZE] = {0};
int g_count; //表示人数

void welcome()
{
    system("clear");
    printf("------------------------------------\n\n");
    printf("\t欢迎使用学生管理系统\n\n");
    printf("------------------------------------\n\n");
    sleep(2);
}
void menu()
{
    system("clear");
    printf("------------------------------------\n\n");
    printf("\t1、添加信息 2、显示信息\n\n");
    printf("\t3、修改信息 4、删除信息\n\n");
    printf("\t5、查找信息 6、退出系统\n\n");
    printf("------------------------------------\n\n");
}
void add_info()
{
    system("clear");
    printf("请输入学号、姓名、年龄、电话\n");
    g_info[g_count] = malloc(sizeof(Stu *));
    if (g_info[g_count] == NULL)
    {
        fprintf(stderr, "申请失败: %s\n", strerror(errno));
        exit(0);
    }
    int flag = 1;
    while (flag)
    {
        scanf("%d%s%d%s", &g_info[g_count]->id, g_info[g_count]->name, &g_info[g_count]->age, g_info[g_count]->tel);

        // printf("%d\t%s\t%d\t%s\n", g_info[g_count]->id, g_info[g_count]->name, g_info[g_count]->age, g_info[g_count]->tel);

        //判断电话长度
        if (strlen(g_info[g_count]->tel) != MAXTELSIZE - 1)
        {
            printf("输入的电话信息有误，请重新输入\n");
            continue;
        }
        //判断姓名是否重复
        int i;
        for (i = 0; i < g_count; i++)
        {
            if (strcmp(g_info[i]->name, g_info[g_count]->name) == 0)
            {
                printf("姓名重复，请重新输入...\n");
                flag = 1;
                break;
            }
        }

        if (i == g_count)
        {
            flag = 0;
        }
    }
    g_count++;
    printf("添加信息成功\n");
    sleep(2);
}
void show_info()
{
    //排序

    int i, j;
    for (i = 0; i < g_count; i++)
    {
        for (j = 0; j < g_count - i - 1; j++)
        {
            if (g_info[j]->id > g_info[j + 1]->id)
            {
                Stu *temp = g_info[j];
                g_info[j] = g_info[j + 1];
                g_info[j + 1] = temp;

                free(temp);
            }
        }
    }
    system("clear");
    printf("%10s %10s %10s %15s\n", "学号", "姓名", "年龄", "电话\n");
    for (i = 0; i < g_count; i++)
    {
        printf("%5d %5s %5d %15s\n", g_info[i]->id, g_info[i]->name, g_info[i]->age, g_info[i]->tel);
    }
    sleep(2);
}
void modify_info()
{
    printf("请输入学号\n");

    int id;
flag:
    scanf("%d", &id);
    int i;
    for (i = 0; i < g_count; i++)
    {
        if (g_info[i]->id == id)
        {
            printf("当先信息如下\n%5d %5s %5d %15s\n", g_info[i]->id, g_info[i]->name, g_info[i]->age, g_info[i]->tel);
            printf("请输入新的信息\n");
            int flag;
            while (flag)
            {
                scanf("%d%s%d%s", &g_info[i]->id, g_info[i]->name, &g_info[i]->age, g_info[i]->tel);

                //判断电话长度
                if (strlen(g_info[i]->tel) != MAXTELSIZE - 1)
                {
                    printf("输入的电话信息有误，请重新输入\n");
                    continue;
                }
                //判断姓名是否重复
                int j;
                for (j = 0; j < g_count; j++)
                {
                    if (i == j)
                        continue;

                    if (strcmp(g_info[i]->name, g_info[j]->name) == 0)
                    {
                        printf("姓名重复，请重新输入...\n");
                        flag = 1;
                        break;
                    }
                }

                if (j == g_count)
                {
                    flag = 0;
                }
            }

            printf("修改成功\n");

            sleep(2);
            return;
        }
    }
    if (i == g_count)
    {
        printf("输入的学号不存在,请重新输入\n");
        goto flag;
    }
}
void delete_info()
{
    system("clear");
    printf("请输入学号\n");
    int id;
    scanf("%d", &id);
    for (size_t i = 0; i < g_count; i++)
    {
        if (g_info[i]->id == id)
        {
            free(g_info[i]);
            for (size_t j = 0; j < g_count - i - 1; j++)
            {
                g_info[i + j] = g_info[i + 1 + j];
            }
            g_count--;
            printf("删除成功\n");
            sleep(2);
            return;
        }
    }
    printf("学号不存在\n");
    sleep(2);
}
void find_info()
{
    system("clear");
    printf("很据学号查找[1]还是姓名查找[2]?\n");

    int choice, i;
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("请输入学号\n");
        int id;
        scanf("%d", &id);
        for (i = 0; i < g_count; i++)
        {
            if (g_info[i]->id == id)
            {
                printf("信息如下\n%5d %5s %5d %15s\n", g_info[i]->id, g_info[i]->name, g_info[i]->age, g_info[i]->tel);
                sleep(2);
                return;
            }
        }
        printf("学号不存在\n");
        sleep(2);
    }
    else
    {
        printf("请输入姓名\n");
        char name[NAMENAMESIZE];
        scanf("%s", name);
        for (i = 0; i < g_count; i++)
        {
            if (! strcmp(g_info[i]->name, name))
            {
                printf("信息如下\n%5d %5s %5d %15s\n", g_info[i]->id, g_info[i]->name, g_info[i]->age, g_info[i]->tel);
                sleep(2);
                return;
            }
        }
        printf("姓名有误\n");
        sleep(2);
    }
}
int main()
{

    welcome();
    int choice;
    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_info();
            break;
        case 2:
            show_info();
            break;
        case 3:
            modify_info();
            break;
        case 4:
            delete_info();
            break;
        case 5:
            find_info();
            break;
        case 6:
            exit(0);
        default:
            printf("输入有误\n");
        }
    }
}
