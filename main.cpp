#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    DataBase db;
    std::vector<Ellement> e={
        Ellement("a",5),
        Ellement("b",7)
    };
    db.AddMapEx("m",e);
    db.WriteTo("lol.db");
    db=DataBase("lol.db");
    auto a=db.ReadMapEx("m");
    std::cout<<"Map's a is "<<GetByName(a,"a").GetInt()<<std::endl;
    return 0;
}