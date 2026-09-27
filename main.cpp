#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    DataBase db;
    std::vector<Ellement> e={
        Ellement(5),
        Ellement(7)
    };
    db.AddVectorEx("v",e);
    db.WriteTo("lol.db");
    db=DataBase("lol.db");
    auto a=db.ReadVectorEx("v");
    std::cout<<"Vec's first is "<<a[0].GetInt()<<std::endl;
    return 0;
}