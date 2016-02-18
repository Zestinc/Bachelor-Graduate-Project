////
////  disease2gene.cpp
////  test
////
////  Created by Zestinc on 15/3/19.
////  Copyright (c) 2015年 Zestinc. All rights reserved.
////
//
//#include <stdio.h>
//#include "cmysql/mysql.h"
//#include <string>
//#include <vector>
//#include <iostream>
//using namespace std;
//
////初始化 & 连接MySQL
//MYSQL initsql()
//{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "relationship", 0, 0, 0);
//    printf((!connection) ? "connect errors\n" : "Connected\n");
//    return mysql;
//}
//
//void quote_handle(string &s)
//{
//    //先处理「/」，再处理"
//    unsigned long pos = s.find('\\');
//    while(pos != string::npos)  //当find没有找到响应字符的时候，返回string::npos(-1).
//    {
//        s.insert(pos, "\\");
//        pos = s.find('\\', pos + 2);
//    }
//    
//    pos = s.find('"');
//    while(pos != string::npos)  //当find没有找到响应字符的时候，返回string::npos(-1).
//    {
//        s.insert(pos, "\\");
//        pos = s.find('"', pos + 2);
//    }
//}
//
//unsigned long max(unsigned long a, unsigned long b){
//    return a >= b ? a : b;
//}
//
//int main (int argc, const char * argv[])
//{
//    MYSQL mysql = initsql();
//    if(!freopen("disease2gene.txt", "r", stdin))
//        printf("Can't open the file!\n");
//    else
//        printf("open file Okey!\n");
//    
////        string content;
////        string hehe, symbol = "";
////        unsigned long a = 1;
////        while(getline(cin, content)){
////            unsigned long first_pos = content.find_first_of('\t');
////            symbol = content.substr(0, first_pos);
////            if(symbol.length() > a)
////            {
////                a = symbol.length();
////                hehe = symbol;
////            }
////        }
////        cout<<a<<endl<<hehe<<endl<<endl;
//    
//    
//    string symbol;  //disease
//    string content;//gene
//    while(getline(cin, content))
//    {
//        content = content.substr(0, content.length() - 1);
//        unsigned long first_pos = content.find_first_of('\t');
//        
//        symbol = content.substr(0, first_pos);
////        cout<<symbol;
//        quote_handle(symbol);
//        content = content.substr(first_pos + 1, string::npos);
//        quote_handle(content);
//        
//        string sql = "insert into disease2gene(disease, go_id)values(\"";
//        sql += symbol + "\",\"" + content + "\");";
//        
//        if(mysql_query(&mysql, sql.c_str()))
//        {
//            cerr<<"Error occured when execute sql: "<< sql << endl;
//            exit(-1);
//        }
//        
//    }
//    
//    mysql_close(&mysql);
//    return 0;
//}
//
