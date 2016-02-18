////
////  symbol2go.cpp
////  test
////
////  Created by Zestinc on 15/2/1.
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
//int main (int argc, const char * argv[])
//{
//    MYSQL mysql = initsql();
//    if(!freopen("symbol2go.txt", "r", stdin))
//        printf("Can't open the file!\n");
//    else
//        printf("open file Okey!\n");
//    
//    string symbol;
//    string content;
//    while(getline(cin, content))
//    {
//        unsigned long first_pos = content.find_first_of('\t');
//        
//        symbol = content.substr(0, first_pos);
//        quote_handle(symbol);
//        
//        content = content.substr(first_pos + 1, string::npos);
//        vector<string> go_id;
//        while(content.length() >= 3)
//        {
//            first_pos = content.find_first_of(' ');
////            string temp =content.substr(0, first_pos);
////            cout<<temp<<endl;
//            go_id.push_back(content.substr(0, first_pos));
//            content.erase(0, first_pos + 1);
//        }
//
//        for(int i = 0 ; i < go_id.size() ; ++i)
//        {
//            string sql = "insert into symbol2go(symbol, go_id)values(\"";
//            sql += symbol + "\",\"" + go_id[i] + "\");";
//        
//            if(mysql_query(&mysql, sql.c_str()))
//            {
//                cerr<<"Error occured when execute sql: "<< sql << endl;
//                exit(-1);
//            }
//        }
//    }
//    
//    mysql_close(&mysql);
//    return 0;
//}
//
