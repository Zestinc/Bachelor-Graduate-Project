////
////  envo.cpp
////  test
////
////  Created by Zestinc on 15/1/16.
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
//struct envo
//{
//    string envo_id;
//    string name;
//    string e_namespace;
//    string created_by;
//    string creation_date;
//    string comment;
//    string expand_assertion_to;
//    string property_value;
//    string replaced_by;
//    bool is_class_level;
//    bool is_metadata_tag;
//    bool is_obsolete;
//    bool is_symmetric;
//    bool is_transitive;
//    vector<t_is_a> disjoint_from;
//    vector<t_is_a> is_a;
//    vector<string> consider;
//    vector<t_relation> intersection_of;
//    vector<t_relation> relationship;
//    vector<string> def;         //字段显示："def
//    vector<string> x_ref;
//    vector<string> alt_id;
//    vector<string> synonym;     //字段显示："synonym
//    vector<string> subset;
//    envo() {is_obsolete = false;}
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
//    connection = mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "envo", 0, 0, 0);
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
//void deal_head(envo &item, string body, string head)
//{
//    if(head == "alt_id")
//        item.alt_id.push_back(body);
//    else if(head == "comment" || head == "\"comment"){
//        if(head[0] == '"')  {body = body.erase(body.length() - 1, 1);}
//        item.comment = body;
//    }
//    else if(head == "consider")
//        item.consider.push_back(body);
//    else if(head == "created_by")
//        item.created_by = body;
//    else if(head == "creation_date")
//    {
//        string tem;
//        tem = '"' + body.substr(0, 10) + " " + body.substr(11, 8) + '"';
//        item.creation_date = tem;
//    }
//    else if(head == "\"def")
//    {
//        body = body.substr(1, string::npos);    //去除和"def匹配的"
//        quote_handle(body);                         //为剩下的"加转义字符
//        item.def.push_back(body);
//    }
//    else if(head == "disjoint_from")
//    {
//        if(head[0] == '"')  {body.erase(body.length() - 1, 1);}
//        t_is_a tem;     //创建一个临时的is_a变量，分开存储ID和NAME，然后放进is_a数组里面
//        tem.id = body.substr(0, body.find_first_of('!') - 1);
//        tem.name = body.substr(body.find_first_of('!') + 2, string::npos);
//        item.disjoint_from.push_back(tem);
//    }
//    else if(head == "\"expand_assertion_to")
//    {
//        body = body.substr(1, string::npos);    //去除和"def匹配的"
//        quote_handle(body);                     //为剩下的"加转义字符
//        item.expand_assertion_to = body;
//    }
//    else if(head == "id")  //单表内容
//        item.envo_id = body;
//    else if(head == "intersection_of" || head == "\"intersection_of")
//    {
//        if(head[0] == '"')  {body = body.erase(body.length() - 1, 1);}
//        t_relation tem;
//        unsigned long blank = body.find(' ');
//        unsigned long mark  = body.find('!');
//        if(mark - blank <= 2)
//        {
//            tem.relation = "";
//            tem.id = body.substr(0, body.find_first_of('!') - 1);
//            tem.name = body.substr(body.find_first_of('!') + 2, string::npos);
//        }
//        else
//        {
//            tem.relation = body.substr(0, blank);
//            tem.id       = body.substr(blank + 1, mark - blank - 2);
//            tem.name     = body.substr(mark + 2, string::npos);
//        }
//        item.intersection_of.push_back(tem);
//    }
//    else if(head == "is_a" || head == "\"is_a")
//    {
//        if(head[0] == '"')  {body.erase(body.length() - 1, 1);}
//        t_is_a tem;     //创建一个临时的is_a变量，分开存储ID和NAME，然后放进is_a数组里面
//        tem.id = body.substr(0, body.find_first_of('!') - 1);
//        tem.name = body.substr(body.find_first_of('!') + 2, string::npos);
//        item.is_a.push_back(tem);
//    }
//    else if(head == "is_class_level")
//    {
//        item.is_class_level = true;
//    }
//    else if(head == "is_metadata_tag")
//    {
//        item.is_metadata_tag = true;
//    }
//    else if(head == "is_obsolete")
//        item.is_obsolete = true;    //因为只要此项出现，就必然表示此项被舍弃
//    else if(head == "is_symmetric")
//    {
//        item.is_symmetric = true;
//    }
//    else if(head == "is_transitive")
//    {
//        item.is_transitive = true;
//    }
//    else if(head == "name" || head == "\"name"){
//        if(head[0] == '"')
//        {
////            cout<<body<<" "<<body.length()<<endl;
//            body = body.erase(body.length() - 1, 1);
////            cout<<body<<" "<<body.length()<<endl;
//        }
//        item.name = body;
//    }
//    else if(head == "namespace")
//        item.e_namespace = body;
//    else if(head == "property_value")
//    {
//        item.property_value = body;
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
//    {
////        quote_handle(body);
//        item.replaced_by = body;
//    }
//    else if(head == "subset")
//        item.subset.push_back(body);
//    else if(head == "\"synonym")
//    {
//        body = body.substr(1, string::npos);
//        quote_handle(body);
//        item.synonym.push_back(body);
//    }
//    else if(head == "xref" || head == "\"xref"){
//        if(head[0] == '"')
//        {
//            body = body.erase(body.length() - 1, 1);
//        }
//        quote_handle(body);
//        item.x_ref.push_back(body);
//    }
//    else
//    {
//        cout << "Error occur" <<endl;
//        cout << "head:" << head << endl;
//        cout << "body:" << body << endl;
//    }
//}
//
//void handle_alt_id(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.alt_id.size(); ++i)
//    {
//        string sql;
//        sql = "insert into alt_id(envo_id, alt_id) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.alt_id[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//    
//}
//
//string judge(bool x)
//{
//    return x ? "true" : "false";
//}
//
//void handle_envo(envo &item, MYSQL &mysql)
//{
//    string sql;
//    sql = "insert into envo(envo_id, name, namespace, comment, is_obsolete, created_by, creation_date, expand_assertion_to, is_class_level, is_metadata_tag, is_symmetric, is_transitive, property_value, replaced_by)values(";
//    sql = sql + '"' + item.envo_id + '"' + ',' + '"' + item.name + '"' + ',' + '"' + item.e_namespace + "\",\"" + item.comment + "\"," + judge(item.is_obsolete) + ",\"" + item.created_by + "\"," + item.creation_date + ",\"" + item.expand_assertion_to + "\"," + judge(item.is_class_level) + "," + judge(item.is_metadata_tag) + "," + judge(item.is_symmetric) + "," + judge(item.is_transitive) + ",\"" + item.property_value + "\",\"" + item.replaced_by + "\");";
//    if(mysql_query(&mysql, sql.c_str()))
//        throw sql.c_str();
//}
//
//void handle_xref(envo &item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.x_ref.size(); ++i)
//    {
//        string sql;
//        sql = "insert into xref(envo_id, xref) values(";
//        sql += '"' + item.envo_id + "\"," + '"' + item.x_ref[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_subset(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.subset.size(); ++i)
//    {
//        string sql;
//        sql = "insert into subset(envo_id, subset) values(";
//        sql += '"' + item.envo_id + "\"," + '"' + item.subset[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_def(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.def.size(); ++i)
//    {
//        string sql = "insert into def(envo_id, def) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.def[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_synonym(envo item,MYSQL &mysql)
//{
//    for(int i = 0; i < item.synonym.size(); ++i)
//    {
//        string sql = "insert into synonym(envo_id, synonym) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.synonym[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_consider(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.consider.size(); ++i)
//    {
//        string sql = "insert into consider(envo_id, consider) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.consider[i] + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_relationship(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.relationship.size(); ++i)
//    {
//        string sql = "insert into relationship(envo_id, re_id, name, relation) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.relationship[i].id + "\",\"" + item.relationship[i].name + "\",\"" + item.relationship[i].relation + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
////void handle_replaced_by(go item, MYSQL &mysql)
////{
////    for (int i = 0; i < item.replaced_by.size(); ++i) {
////        string sql = "insert into replaced_by(envo_id, replaced_by) values(";
////        sql += '"' + item.id + "\",\"" + item.replaced_by[i] + "\");";
////        if(mysql_query(&mysql, sql.c_str()))
////            throw sql.c_str();
////    }
////}
//
//void handle_disjoint_from(envo &item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.disjoint_from.size(); ++i)
//    {
//        string sql = "insert into disjoint_from(envo_id,disj_id,disj_name) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.disjoint_from[i].id + "\",\"" + item.disjoint_from[i].name + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void handle_is_a(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.is_a.size(); ++i)
//    {
//        string sql = "insert into is_a(o_id,i_id,i_name) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.is_a[i].id + "\",\"" + item.is_a[i].name + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//
//void handle_intersection_of(envo item, MYSQL &mysql)
//{
//    for(int i = 0; i < item.intersection_of.size(); ++i)
//    {
//        string sql = "insert into relationship(envo_id, re_id, name, relation) values(";
//        sql += '"' + item.envo_id + "\",\"" + item.intersection_of[i].id + "\",\"" + item.intersection_of[i].name + "\",\"" + item.intersection_of[i].relation + "\");";
//        if(mysql_query(&mysql, sql.c_str()))
//            throw sql.c_str();
//    }
//}
//
//void Input_data(envo &item, MYSQL &mysql)
//{
//    try {
//        handle_alt_id(item, mysql);
//        handle_consider(item, mysql);
//        handle_def(item, mysql);
//        handle_disjoint_from(item, mysql);
//        handle_envo(item, mysql);
//        handle_intersection_of(item, mysql);
//        handle_is_a(item, mysql);
//        handle_relationship(item, mysql);
//        handle_subset(item, mysql);
//        handle_synonym(item, mysql);
//        handle_xref(item, mysql);
//    } catch (const char *s) {
//        cerr << "error sql:" << s << endl;
//        exit(-1);
//    }
//}
//
//int main (int argc, const char * argv[])
//{
//    MYSQL mysql = initsql();
//    if(!freopen("envo.txt", "r", stdin)) printf("Can't open the file!\n");
//    else                                printf("open file Okey!\n");
//    
//    string str;
//    while(getline(cin, str))
//    {
//        if(str != "[Term]")
//        {
//            cout<<str<<endl;
//            continue;
//        }
//        else
//        {
//            envo item;
//            //循环处理项目内的字段
//            while(getline(cin, str))
//            {
//                if(str.length() <= 1) break;
//                string head = gethead(str, str);
////                cout<<head<<endl;
//                deal_head(item, str, head);
//            }
//            //将一些特殊的数据处理成数据库的格式
//            if(item.creation_date.length() <= 1) item.creation_date = "NULL";
//            //将处理后的Term输入数据库中
//            Input_data(item, mysql);
//        }
//    }
//    
//    mysql_close(&mysql);
//    return 0;
//}
