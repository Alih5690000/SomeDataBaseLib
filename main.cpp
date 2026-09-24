#include <iostream>
#define DEBUG
#include "main.hpp"

int main(){
    /*DataBase db;
    std::vector<uint8_t> arr;
    arr.resize(4);
    uint32_t num=67;
    memcpy(arr.data(), &num, sizeof(uint32_t));
    db.attrs["a"]=arr;
    db.WriteTo("lol.db");
    return 0;*/
    DataBase db("lol.db");
    for (const auto& [k,v]:db.attrs){
        std::cout<<"Key is "<<k<<std::endl;
    }
    uint32_t num;
    memcpy(&num, db.attrs["a"].data(), 4);
    std::cout<<"Num is "<<num<<std::endl;
}