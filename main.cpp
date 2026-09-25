#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    /*DataBase db;
    std::map<int,int> m;
    m[3]=4;
    db.AddMap("m",m);
    db.WriteTo("lol.db");
    return 0;*/
    DataBase db("lol.db");
    auto m=db.ReadMap<int,int>("m");
    std::cout<<"3 is "<<m[3]<<std::endl;
    return 0;
}