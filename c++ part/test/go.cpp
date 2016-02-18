////
////  go.cpp
////  test
////
////  Created by Zestinc on 15/1/2.
////  Copyright (c) 2015年 Zestinc. All rights reserved.
////
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
//struct t_relation
//{
//    string relation;
//    string id;
//    string name;
//};
//
//struct go
//{
//    string id;
//    string name;
//    string g_namespace;
////    string created_by;
////    string creation_date;
//    string comment;
//    bool is_obsolete;
//    vector<t_is_a> is_a;
//    vector<string> consider;
//    vector<string> replaced_by;
//    vector<t_relation> relationship;
//    vector<string> broad_synonym;
//    vector<string> narrow_synonym;
//    vector<string> related_synonym;
////    vector<string> xref_analog;
//    vector<string> exact_synonym;
//    vector<string> def;         //字段显示："def
//    vector<string> x_ref;
//    vector<string> alt_id;
////    vector<string> synonym;     //字段显示："synonym
//    vector<string> subset;
//    go() {is_obsolete = false;}
//};
//
///*
// //自定义异常
// class myException:public exception
// {
// public:
// const char* what(string str)const throw()//#1
// {
// string s = "ERROR! When inserting " + str + ".\n";
// return s.c_str();
// }
// };
// void check(int y, string sql, string head) throw(myException)//#2
// {
// if(y)
// throw myException();
// }
// */
//
//
////初始化 & 连接MySQL
//MYSQL initsql()
//{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "go", 0, 0, 0);
//    printf((!connection) ? "connect errors\n" : "Connected\n");
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
//void deal_head(go &item, string body, string head)
//{
//    if(head == "id")  //单表内容
//        item.id = body;
//    else if(head == "name" || head == "\"name"){
//        if(head[0] == '"')   {body = body.erase(body.length() - 1, 1);}
//        item.name = body;
//    }
//    else if(head == "namespace")
//        item.g_namespace = body;
//    else if(head == "comment" || head == "\"comment"){
//        if(head[0] == '"')  {body = body.erase(body.length() - 1, 1);}
//        item.comment = body;
//    }
//    else if(head == "consider")
//        item.consider.push_back(body);
//    else if(head == "xref_analog" || head == "\"xref_analog"){
//        if(head[0] == '"')  {body = body.erase(body.length() - 1, 1);}
//        item.x_ref.push_back(body);
//    }
//    else if(head == "is_a" || head == "\"is_a")
//    {
//        if(head[0] == '"')  {body.erase(body.length() - 1, 1);}
//        t_is_a tem;     //创建一个临时的is_a变量，分开存储ID和NAME，然后放进is_a数组里面
//        tem.id = body.substr(0, body.find_first_of('!') - 1);
//        tem.name = body.substr(body.find_first_of('!') + 2, string::npos);
//        item.is_a.push_back(tem);
//    }
//    else if(head == "alt_id")
//        item.alt_id.push_back(body);
//    else if(head == "\"def")
//    {
//        body = body.substr(1, string::npos);    //去除和"def匹配的"
//        quote_handle(body);                     //为剩下的"加转义字符
//        item.def.push_back(body);
//    }
//    else if(head == "subset")
//        item.subset.push_back(body);
//    else if(head == "is_obsolete")
//        item.is_obsolete = true;    //因为只要此项出现，就必然表示此项被舍弃
//    else if(head == "\"broad_synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.broad_synonym.push_back(body);
//    }
//    else if(head == "\"exact_synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.exact_synonym.push_back(body);
//    }
//    else if(head == "\"narrow_synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.narrow_synonym.push_back(body);
//    }
//    else if(head == "\"related_synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.related_synonym.push_back(body);
//    }
//    else if(head == "relationship" || head == "\"relationship")
//    {
//        if(head[0] == '"')  {body = body.erase(body.length() - 1, 1);}
//        t_relation tem;
//        unsigned long blank = body.find(' ');
//        unsigned long mark  = body.find('!');
//        tem.relation = body.substr(0, blank);
//        tem.id       = body.substr(blank + 1, mark - blank - 2);
//        tem.name     = body.substr(mark + 2, string::npos);
//        item.relationship.push_back(tem);
//    }
//    else if(head == "replaced_by")
//        item.replaced_by.push_back(body);
//    else
//    {
//        cout << "Error occur" <<endl;
//        cout << "head:" << head << endl;
//        cout << "body:" << body << endl;
//    }
//}
//
//void handle_go(go &item, MYSQL &mysql)
//{
//    string sql;
//    sql = "insert into go(go_id, name, namespace, comment, is_obsolete)values(";
//    sql = sql + '"' + item.id + '"' + ',' + '"' + item.name + '"' + ',' + '"' + item.g_namespace + "\",\"" + item.comment + "\"," + (item.is_obsolete ? "true" : "false") + ");";
//    if(mysql_query(&mysql, sql.c_str()))
//        throw sql.c_str();
////    {
////                cout<<sql<<endl;
////        throw sql.c_str();
////    }
//}
//
//void handle_xref(go &item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.x_ref.size(); ++i)
//    {
//        string sql;
//        sql = "insert into xref(go_id, xref) values(";
//        sql += '"' + item.id + "\"," + '"' + item.x_ref[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_subset(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.subset.size(); ++i)
//    {
//        string sql;
//        sql = "insert into subset(go_id, subset) values(";
//        sql += '"' + item.id + "\"," + '"' + item.subset[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_alt_id(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.alt_id.size(); ++i)
//    {
//        /* 根据id1<id2，无法搜索，舍弃
//         string sql, id1, id2;
//         int i1, i2;
//         id1 = item.id;
//         id2 = item.alt_id[i];
//         i1 = stoi(id1.substr(5, string::npos));
//         i2 = stoi(id2.substr(5, string::npos));
//         if(i1 > i2)
//         swap(id1, id2);
//         */
//        string sql;
//        sql = "insert into alt_id(go_id, alt_id) values(";
//        sql += '"' + item.id + "\",\"" + item.alt_id[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//    
//}
//
//void handle_def(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.def.size(); ++i)
//    {
//        string sql = "insert into def(go_id, def) values(";
//        sql += '"' + item.id + "\",\"" + item.def[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_is_a(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.is_a.size(); ++i)
//    {
//        string sql = "insert into is_a(go_id,is_a_id,is_a_name) values(";
//        sql += '"' + item.id + "\",\"" + item.is_a[i].id + "\",\"" + item.is_a[i].name + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_broad_synonym(go item,MYSQL &mysql)
//{
//    for(int i = 0; i < item.broad_synonym.size(); ++i)
//    {
//        string sql = "insert into broad_synonym(go_id, broad_synonym) values(";
//        sql += '"' + item.id + "\",\"" + item.broad_synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_exact_synonym(go item,MYSQL &mysql)
//{
//    for(int i = 0; i < item.exact_synonym.size(); ++i)
//    {
//        string sql = "insert into exact_synonym(go_id, exact_synonym) values(";
//        sql += '"' + item.id + "\",\"" + item.exact_synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_narrow_synonym(go item,MYSQL &mysql)
//{
//    for(int i = 0; i < item.narrow_synonym.size(); ++i)
//    {
//        string sql = "insert into narrow_synonym(go_id, narrow_synonym) values(";
//        sql += '"' + item.id + "\",\"" + item.narrow_synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_related_synonym(go item,MYSQL &mysql)
//{
//    for(int i = 0; i < item.related_synonym.size(); ++i)
//    {
//        string sql = "insert into related_synonym(go_id, related_synonym) values(";
//        sql += '"' + item.id + "\",\"" + item.related_synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_consider(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.consider.size(); ++i)
//    {
//        string sql = "insert into consider(go_id, consider) values(";
//        sql += '"' + item.id + "\",\"" + item.consider[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_relationship(go item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.relationship.size(); ++i)
//    {
//        string sql = "insert into relationship(go_id, re_id, name, relation) values(";
//        sql += '"' + item.id + "\",\"" + item.relationship[i].id + "\",\"" + item.relationship[i].name + "\",\"" + item.relationship[i].relation + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_replaced_by(go item, MYSQL &mysql)
//{
//    for (int i = 0; i < item.replaced_by.size(); ++i) {
//        string sql = "insert into replaced_by(go_id, replaced_by) values(";
//        sql += '"' + item.id + "\",\"" + item.replaced_by[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void Input_data(go &item, MYSQL &mysql)
//{
//    try {
//        handle_go(item, mysql);
//        handle_xref(item, mysql);
//        handle_subset(item, mysql);
//        handle_alt_id(item, mysql);
////        handle_synonym(item, mysql);
//        handle_def(item, mysql);
//        handle_is_a(item, mysql);
//        handle_broad_synonym(item, mysql);
//        handle_consider(item, mysql);
//        handle_exact_synonym(item, mysql);
//        handle_narrow_synonym(item, mysql);
//        handle_related_synonym(item, mysql);
//        handle_relationship(item, mysql);
//        handle_replaced_by(item, mysql);
//    } catch (const char *s) {
//        cerr << "error sql:" << s << endl;
//        exit(-1);
//    }
//}
//
//int main (int argc, const char * argv[])
//{
//    MYSQL mysql = initsql();
//    if(!freopen("go.txt", "r", stdin)) printf("Can't open the file!\n");
//    else                                printf("open file Okey!\n");
//    
//    string str;
//    while(getline(cin, str))
//    {
//        if(str != "[Term]")
//            continue;
//        else
//        {
//            go item;
//            //循环处理项目内的字段
//            while(getline(cin, str))
//            {
//                if(str.length() <= 1) break;
//                string head = gethead(str, str);
//                deal_head(item, str, head);
//            }
//            //将一些特殊的数据处理成数据库的格式
////            special_handle(item);
//            //将处理后的Term输入数据库中
//            Input_data(item, mysql);
//        }
//    }
//    
//    mysql_close(&mysql);
//    return 0;
//}
