#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    /*DataBase db;
    std::vector<uint32_t> v={1,2,3,4,5};
    std::vector<uint8_t> arr;
    db.AddInt("a",67);
    db.AddVector("v",v);
    db.WriteTo("lol.db");
    return 0;*/
    DataBase db("lol.db");
    for (const auto& [k,v]:db.attrs){
        std::cout<<"Key is "<<k<<std::endl;
    }
    uint32_t num;
    memcpy(&num, db.attrs["a"].data(), 4);
    std::cout<<"Num is "<<num<<std::endl;
    uint8_t* d=db.attrs["v"].data();
    std::vector<uint32_t> l(db.attrs["v"].size()/sizeof(uint32_t));
    memcpy(l.data(), db.attrs["v"].data(), db.attrs["v"].size());
    for (auto i:l){
        std::cout<<"VEC IS "<<i<<std::endl;
    }
}