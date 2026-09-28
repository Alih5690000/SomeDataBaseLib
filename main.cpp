#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    DataBase db;
    std::vector<Ellement> e={
        Ellement("a",5),
        Ellement("b",7),
        Ellement("m",{Ellement("inner_a",67)},true)
    };
    db.AddMapEx("m",e);
    db.WriteTo("lol.db");
    db=DataBase("lol.db");
    auto a=db.ReadMapEx("m");
    std::cout<<"Map's inner_a is "<<GetByName(GetByName(a, "m").GetMap(), "inner_a").GetInt()<<std::endl;
    return 0;
}