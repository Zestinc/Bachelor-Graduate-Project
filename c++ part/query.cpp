////
////  query.cpp
////  test
////
////  Created by Zestinc on 15/1/4.
////  Copyright (c) 2015年 Zestinc. All rights reserved.
////
//
//#include "query.h"
//#include <stdio.h>
//#include <iostream>
//#include "test/cmysql/mysql.h"
//#include <string>
//using namespace std;
//
////初始化 & 连接MySQL
//MYSQL initsql()
//{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql, "localhost:8888", "root", "123456", "go", 0, 0, 0);
//    printf((!connection) ? "connect errors\n" : "Connected\n");
//    return mysql;
//}
//
////返回某一个查询得到的结果的拼接（即合成到一个字符串里
//）
//string getResult(MYSQL &mysql)
//{
//    string re, s, sql;
//    MYSQL_RES *result;
//    result = mysql_store_result(&mysql);
//    if(!result)
//    {
//        cerr<<"no result"<<endl;
//        exit(-1);
//    }
//    MYSQL_ROW row;
//    unsigned int num_fields;
//    unsigned int i;
//    num_fields = mysql_num_fields(result);
//    while ((row = mysql_fetch_row(result)))
//    {
//        unsigned long *lengths;
//        lengths = mysql_fetch_lengths(result);
//        for(i = 0; i < num_fields; i++)
//        {
//            printf("[%.*s]", (int) lengths[i], row[i] ? row[i] : "NULL");
//        }
//        printf("\n");
//    }
//
//    
//    return re;
//}
