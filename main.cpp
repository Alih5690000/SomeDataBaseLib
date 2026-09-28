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
    Map a=db.ReadMapEx("m");
    std::cout<<"Map's inner_a is "<<a.Get("m").GetMap().Get("inner_a").GetStr()<<std::endl;
    return 0;
}