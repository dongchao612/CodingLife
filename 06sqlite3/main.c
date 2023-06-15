#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
/* Callback function */
int print(void *arg, int column, char **value, char **name)
{
    for (size_t i = 0; i < column; i++)
    {
        printf("%s = %s ", name[i], value[i]);
    }
    printf("\n");
    return 0;
}
int main()
{
    printf("sqlite3 version : %s\n", sqlite3_libversion());

    // 打开数据库
    sqlite3 *ppdb; // 数据库指针
    char sql[128]; // 保存sql语句的字符串
    int ret = sqlite3_open("student.db", &ppdb);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3 open:%s\n", sqlite3_errmsg(ppdb));
        exit(0);
    }

    // 创建数据库
    memset(sql, 0, sizeof(sql)); // 清空sql
    sprintf(sql, "create table if not exists student(id integer,name text,age integer);");
    ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL); // 执行sql语句
    if (ret != SQLITE_OK)
    {
        printf("create:%s\n", sqlite3_errmsg(ppdb));
        exit(0);
    }
#if 0
    //插入数据
    int id, age;
    char name[32] = {};
    printf("请输入学号，姓名，年龄\n");

    for (size_t i = 0; i < 5; i++)
    {
        scanf("%d%s%d", &id, name, &age);
        memset(sql, 0, sizeof(sql)); //清空sql
        sprintf(sql, "insert into student(id,name,age) values(%d,'%s',%d);", id, name, age);
        ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL); //执行sql语句
        if (ret != SQLITE_OK)
        {
            printf("insert:%s\n", sqlite3_errmsg(ppdb));
            exit(0);
        }
    }
#endif

#if 0
    // 修改
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "update  student set id = 5 where age = 25;");
    ret = sqlite3_exec(ppdb, sql, print, NULL, NULL);
    if (ret != SQLITE_OK)
    {
        printf("update:%s\n", sqlite3_errmsg(ppdb));
        exit(0);
    }
#endif
#if 1
    // 查询方法1
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from student;");
    printf("查询方法1结果如下\n");
    ret = sqlite3_exec(ppdb, sql, print, NULL, NULL); // 执行sql语句 回调函数
    if (ret != SQLITE_OK)
    {
        printf("select:%s\n", sqlite3_errmsg(ppdb));
        exit(0);
    }
#endif
#if 1
    // 查询方法2
    char **result; // 字符串数组
    int row = 0, column = 0;
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from student;");
    ret = sqlite3_get_table(ppdb, sql, &result, &row, &column, NULL);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n", sqlite3_errmsg(ppdb));
        exit(0);
    }

    // printf("一共查出来了 %d 行 %d 列数据\n", row, column); // 一共查出来了 5 行 3 列数据
#if 0
    for (size_t i = 0; i < (row + 1) * column; i++)
    {
        printf("%s ",result[i]);// id name age 1 aa 11 2 bb 22 3 cc 33 4 dd 44 5 ee 55 
    }
    printf("\n");
#endif
    // 查询方法2
    int i, j;
    int inindex = column; // 3
    printf("查询方法2结果如下\n");

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            printf("%s = %s ", result[j], result[inindex]);
            inindex++;
        }
        printf("\n");
    }
#endif
    exit(0);
}
