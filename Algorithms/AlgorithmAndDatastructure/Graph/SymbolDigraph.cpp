//
// Created by windyear_office on 18-1-31.
//

#include <fstream>
#include "SymbolDigraph.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

SymbolDigraph::SymbolDigraph(string filename, char* sp) {
    ifstream input(filename);
    if(input){
        string s;
        vector<string> ss;
        //以sp为分隔符读取字符串内容到s中
        while(getline(input, s)) {
            //map的插入方法，要熟悉
            boost::algorithm::split(ss, s, boost::algorithm::is_any_of(sp));
            for(auto v: ss) {
                if (!index_table.count(v)) {
                    index_table.insert(pair<string, int>(v, index_table.size()));
                }
            }
        }
    }
    input.close();
    //第二次遍历构造图
    g = new Digraph(index_table.size());
    //重新分配大小
    index.resize(index_table.size());
    //遍历map
    map<string, int>::iterator it;
    for(it = index_table.begin(); it != index_table.end(); it++){
        index[it->second] = it->first;
    }

    input.open(filename);
    if(input){
        string s;
        vector<string> ss;
        while(getline(input, s)) {
            //map的插入方法，要熟悉
            boost::algorithm::split(ss, s, boost::algorithm::is_any_of(sp));
            int v = index_table[ss[0]];
            for(int i = 1; i < ss.size(); i++) {
               g->AddEdge(v, index_table[ss[i]]);
            }
        }
    }
    input.close();
    cout << "The size of the Digraph is: " << index_table.size() << endl;
}

SymbolDigraph::~SymbolDigraph() {
    delete g;
}

bool SymbolDigraph::Contains(string s) {
    return index_table.count(s);
}

Digraph SymbolDigraph::G() {
    return *g;
}

int SymbolDigraph::Index(string s) {
    return index_table[s];
}

string SymbolDigraph::Name(int index_) {
    return index[index_];
}


