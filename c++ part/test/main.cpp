////
////  main.cpp
////  test
////
////  Created by Zestinc on 14/12/29.
////  Copyright (c) 2014年 Zestinc. All rights reserved.
////
//
//
//#include <stdio.h>
//#include "cmysql/mysql.h"
//#include <string>
//#include <vector>
//#include <iostream>
//using namespace std;
//struct t_is_a
//{
//    string id;
//    string name;
//};
//
//struct doid
//{
//    string id;
//    string name;
//    //string d_namespace;
//    string created_by;
//    string creation_date;
//    string comment;
//    bool is_obsolete;
//    vector<t_is_a> is_a;
//    vector<string> def;         //字段显示："def
//    vector<string> x_ref;
//    vector<string> alt_id;
//    vector<string> synonym;     //字段显示："synonym
//    vector<string> subset;
//    doid() {is_obsolete = false;}
//};
//
///*
////自定义异常
//class myException:public exception
//{
//public:
//    const char* what(string str)const throw()//#1
//    {
//        string s = "ERROR! When inserting " + str + ".\n";
//        return s.c_str();
//    }
//};
//void check(int y, string sql, string head) throw(myException)//#2
//{
//    if(y)
//        throw myException();
//}
//*/
//
//
////初始化 & 连接MySQL
//MYSQL initsql()
//{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql, "localhost:8888", "root", "123456", "test", 0, 0, 0);
//    if(!connection)
//    {
//        printf("Connect error!\n");
//        exit(-1);
//    }
//    else
//        printf("Connected\n");
//    return mysql;
//}
//
//
////获取当前字段的名称
//string gethead(string str, string &body)
//{
//    int first = 0;
//    for(int i = 0; i < str.length(); ++i)
//    {
//        if(str[i] == ':')
//        {
//            first = i;
//            break;
//        }
//    }
//    body = str.substr(first + 2, string::npos);
//    return str.erase(first, string::npos);
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
////根据字段名称(head)将剩下部分(body)数据传入结构体
//void deal_head(doid &item, string body, string head)
//{
//    if(head == "id")  //单表内容
//        item.id = body;
//    else if(head == "name")
//        item.name = body;
//    else if(head == "created_by")
//        item.created_by = body;
//    else if(head == "creation_date")
//    {
//        string tem;
//        tem = '"' + body.substr(0, 10) + " " + body.substr(11, 8) + '"';
//        item.creation_date = tem;
//    }
//    else if(head == "comment")
//        item.comment = body;
//    else if(head == "xref")
//        item.x_ref.push_back(body);
//    else if(head == "is_a")
//    {
//        t_is_a tem;     //创建一个临时的is_a变量，分开存储ID和NAME，然后放进is_a数组里面
//        tem.id = body.substr(0, body.find_first_of('!'));
//        tem.name = body.substr(body.find_first_of('!') + 1, string::npos);
//        item.is_a.push_back(tem);
//    }
//    else if(head == "alt_id")
//        item.alt_id.push_back(body);
//    else if(head == "\"def")
//    {
//        body = body.substr(1, string::npos);    //去除和"def匹配的"
//        //cout<<body<<endl;
//        quote_handle(body);                     //为剩下的"加转义字符
//        item.def.push_back(body);
//    }
//    else if(head == "\"synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.synonym.push_back(body);
//    }
//    else if(head == "subset")
//        item.subset.push_back(body);
//    else if(head == "is_obsolete")
//        item.is_obsolete = true;    //因为只要此项出现，就必然表示此项被舍弃
//    else
//        cout << "Error occur" <<endl;
//}
//
//void handle_doid(doid &item, MYSQL &mysql)
//{
//    string sql;
//    sql = "insert into doid(id, name, created_by, creation_date, comment, is_obsolete)values(";
//    sql = sql + '"' + item.id + '"' + ',' + '"' + item.name + '"' + ',' + '"' + item.created_by + '"' + ',' + item.creation_date                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      + ',' + '"' + item.comment + '"' + ',' + (item.is_obsolete ? "true" : "false") + ");";
//    if(mysql_query(&mysql, sql.c_str()))
//        throw sql.c_str();
//}
//
//void handle_xref(doid &item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.x_ref.size(); ++i)
//    {
//        string sql;
//        sql = "insert into xref(doid_id, xref) values(";
//        sql += '"' + item.id + "\"," + '"' + item.x_ref[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_subset(doid item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.subset.size(); ++i)
//    {
//        string sql;
//        sql = "insert into subset(doid_id, subset) values(";
//        sql += '"' + item.id + "\"," + '"' + item.subset[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//           throw sql.c_str();
//    }
//}
//
//void handle_alt_id(doid item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.alt_id.size(); ++i)
//    {
//        /* 根据id1<id2，无法搜索，舍弃
//        string sql, id1, id2;
//        int i1, i2;
//        id1 = item.id;
//        id2 = item.alt_id[i];
//        i1 = stoi(id1.substr(5, string::npos));
//        i2 = stoi(id2.substr(5, string::npos));
//        if(i1 > i2)
//            swap(id1, id2);
//         */
//        string sql;
//        sql = "insert into alt_id(id1, id2) values(";
//        sql += '"' + item.id + "\",\"" + item.alt_id[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//    
//}
//
//void handle_synonym(doid item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.synonym.size(); ++i)
//    {
//        string sql = "insert into synonym(doid_id, synonym) values(";
//        sql += '"' + item.id + "\",\"" + item.synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_def(doid item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.def.size(); ++i)
//    {
//        string sql = "insert into def(doid_id, def) values(";
//        sql += '"' + item.id + "\",\"" + item.def[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_is_a(doid item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.is_a.size(); ++i)
//    {
//        string sql = "insert into is_a(original_id,is_a_id,is_a_name) values(";
//        sql += '"' + item.id + "\",\"" + item.is_a[i].id + "\",\"" + item.is_a[i].name + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//        {
//            throw sql.c_str();
//        }
//    }
//}
//
//void Input_data(doid &item, MYSQL &mysql)
//{
//    string sql;
//    try {
//        handle_doid(item, mysql);
//        handle_xref(item, mysql);
//        handle_subset(item, mysql);
//        handle_alt_id(item, mysql);
//        handle_synonym(item, mysql);
//        handle_def(item, mysql);
//        handle_is_a(item, mysql);
//    } catch (const char *s) {
//        cerr << "error sql:" << s << endl;
//        exit(-1);
//    }
//}
//
//void special_handle(doid &item)
//{
//    if(item.creation_date.length() <= 1) item.creation_date = "NULL";
//}
//
//int main (int argc, const char * argv[])
//{
//    MYSQL mysql = initsql();
//    if(!freopen("doid.txt", "r", stdin)) printf("Can't open the file!\n");
//    else                                printf("open file Okey!\n");
//   
//    string str;
//    while(getline(cin, str))
//    {
//        if(str != "[Term]")
//            continue;
//        else
//        {
//            doid item;
//            //循环处理项目内的字段
//            while(getline(cin, str))
//            {
//                if(str.length() <= 1) break;
//                string head = gethead(str, str);
//                deal_head(item, str, head);
//            }
//            //将一些特殊的数据处理成数据库的格式
//            special_handle(item);
//            //将处理后的Term输入数据库中
//            Input_data(item, mysql);
//        }
//    }
//    
//    mysql_close(&mysql);
//    return 0;
//}
