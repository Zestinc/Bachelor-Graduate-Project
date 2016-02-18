//
//  Doid2Doid.cpp
//  test
//
//  Created by Zestinc on 15/3/23.
//  Copyright (c) 2015年 Zestinc. All rights reserved.
//

#include <stdio.h>
#include "cmysql/mysql.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
struct Match{
    string doid;    //doid对应的doid
    int num;        //doid对应的病症的次数
    Match(string a = "", int b = 0){
        doid = a;
        num = b;
    }
    
};

bool cmp (const Match &a, const Match &b){
    return a.num > b.num;
}

vector<Match> match;
vector<string> symptom;
vector<string> disease;
vector<string> RelateDisease;
vector<string> doid2;
vector<int> doid2num;
map<string, vector<Match>> ans;

//初始化 & 连接MySQL
MYSQL initsql()
{
    MYSQL *connection, mysql;
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "relationship", 0, 0, 0);
    printf((!connection) ? "connect errors\n" : "Connected\n");
    return mysql;
}

MYSQL_RES* query(MYSQL *con, string sql){
    if(mysql_query(con, sql.c_str())){
        cout<<"Error happen when execute sql"<<" "<<sql<<endl;
    }
    MYSQL_RES *res = NULL;
    res = mysql_store_result(con);
    return res;
}

string int2str(int &i) {
    string s;
    stringstream ss(s);
    ss << i;
    
    return ss.str();
}

string quote_handle(string s)
{
    //先处理「/」，再处理"
    unsigned long pos = s.find('\\');
    while(pos != string::npos)  //当find没有找到响应字符的时候，返回string::npos(-1).
    {
        s.insert(pos, "\\");
        pos = s.find('\\', pos + 2);
    }

    pos = s.find('"');
    while(pos != string::npos)  //当find没有找到响应字符的时候，返回string::npos(-1).
    {
        s.insert(pos, "\\");
        pos = s.find('"', pos + 2);
    }
    return s;
}

void f(Match m, MYSQL *con, string original){
    string sql = "insert into doid2doid(disease, relate_disease, counter) values(\"";
    sql = sql + original + "\", " + m.doid + "\", \"" + int2str(m.num) + "\")";
    query(con, sql);
}

int main(){
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    freopen("diseases2symptom.txt", "r", stdin);
    //获得disease2symptom的键值对 （symptom数组 and disease数组）
    MYSQL mysql = initsql();
    string sql = "select distinct(disease) from disease2symptom";
    res = query(&mysql, sql);
    while (row = mysql_fetch_row(res), row) {
        //        for (int i = 0 ; i < mysql_num_rows(res); i++) {
        disease.push_back(row[0]);
        //        }
    }
    cout<<disease.size()<<endl;
    
    //对于每一个disease，找对应的symptom
    for (int i = 0; i < disease.size(); i++) {
        sql = "select symptom from disease2symptom where disease = \"" + quote_handle(disease[i]) + "\"";
        res = query(&mysql, sql);
        //清空各种变量
        match.clear();
        symptom.clear();
        RelateDisease.clear();
        //获得所有相关的symptom
        while (row = mysql_fetch_row(res), row) {
            symptom.push_back(row[0]);
        }
        //再找对应的disease
        for (int j = 0;  j < symptom.size(); j++) {
            sql = "select disease from disease2symptom where symptom = \"" + quote_handle(symptom[j]) + "\"";
            MYSQL_RES *res2 = NULL;
            MYSQL_ROW row2 = NULL;
            res2 = query(&mysql, sql);
            //将symptom对应的disease存到数组里面
            while (row2 = mysql_fetch_row(res2), row2) {
                RelateDisease.push_back(row2[0]);
            }
        }
        //对数组进行排序，统计每个disease出现的次数
        RelateDisease.push_back("zzzzzzzzzzzzz");
        sort(RelateDisease.begin(), RelateDisease.end());
        int number = 1;
        for(int j = 1; j < RelateDisease.size() ; j++){
            if(RelateDisease[j] != RelateDisease[j-1]){
                //将自身的disease排除掉
                if(RelateDisease[j-1] != disease[i]){
                    match.push_back(Match(RelateDisease[j-1], number));
                }
                number = 1;
            }
            else
                number++;
        }
        //根据disease出现大的次数，对disease 和 disease病症出现次数 排序，从大到小
        sort(match.begin(), match.end(), cmp);
        cout<<"i:"<<i<<endl<<"match.size():"<<match.size()<<endl;
        //生成对应的vector存进map中
        for(int j = 0; j < match.size(); j++){
            ans[disease[i]] = match;
        }
    }
    //录入到数据库之中
    for(int i = 0; i < disease.size(); ++i){
        vector<Match> temp = ans[disease[i]];
        for(int j = 0 ; j < temp.size(); ++j){
            sql = "insert into doid2doid(disease, relate_disease, counter) values(\"" + disease[i] + "\",\"" + temp[j].doid + "\"," + int2str(temp[j].num) + ")";
            query(&mysql, sql);
        }
    }
    mysql_close(&mysql);
    return 0;
}