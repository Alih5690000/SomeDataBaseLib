#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#ifdef DEBUG
#define LOG(x) std::cout<<x<<std::endl
#else
#define LOG
#endif

class DataBase{
    public:
    std::map<std::string,std::vector<std::uint8_t>> attrs;
    DataBase(const std::string& path){
        std::ifstream file(path,std::ios::binary);
        while (file.peek() != std::ifstream::traits_type::eof()){
            uint32_t lengthOfName;
            file.read((char*)&lengthOfName,sizeof(uint32_t));
            LOG("Length of name is "+std::to_string(lengthOfName));
            std::string name;
            name.resize(lengthOfName);
            file.read(name.data(),lengthOfName);
            LOG("Name is "+name);
            uint32_t lengthOfData;
            file.read((char*)&lengthOfData,sizeof(uint32_t));
            LOG("Length of data is "+std::to_string(lengthOfData));
            std::vector<uint8_t> data;
            data.resize(lengthOfData);
            file.read((char*)data.data(),lengthOfData);
            attrs[name]=data;
        }
    }

    DataBase()=default;
    void WriteTo(const std::string& path){
        std::ofstream file(path,std::ios::binary | std::ios::in);
        for (auto [k,v]:attrs){
            uint32_t size=k.size();
            LOG("[WRITE]Length of name is "+std::to_string(size));
            file.write((char*)&size,sizeof(uint32_t));
            file.write(k.data(),size);
            LOG("[WRITE]Name is "+k);
            uint32_t size2=v.size();
            LOG("[WRITE]Length of data is "+std::to_string(size2));
            file.write((char*)&size2,sizeof(uint32_t));
            char* data=(char*)v.data();
            file.write(data,size2);
        }
    }
};