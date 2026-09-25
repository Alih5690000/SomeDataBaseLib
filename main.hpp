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
    void AddInt(const std::string& key, uint32_t num){
        std::vector<uint8_t> arr;
        arr.resize(4);
        memcpy(arr.data(), &num, sizeof(uint32_t));
        attrs[key]=arr;
    }
    void AddStr(const std::string& key, const std::string& str){
        std::vector<uint8_t> arr;
        arr.resize(str.size());
        memcpy(arr.data(), str.data(), str.size());
        attrs[key]=arr;
    }
    template <typename T>
    void AddVector(const std::string& key, const std::vector<T>& vec){
        std::vector<uint8_t> arr;
        arr.resize(vec.size()*sizeof(T));
        memcpy(arr.data(), vec.data(), vec.size()*sizeof(T));
        attrs[key]=arr;
    }
    template <typename T>
    std::vector<T> ReadVector(const std::string& key){
        std::vector<T> l(db.attrs[key].size()/sizeof(T));
        memcpy(l.data(), db.attrs[key].data(), db.attrs[key].size());
    }
    template <typename K, typename V>
    void AddMap(const std::string& key, std::map<K,V> map){
        std::vector<uint8_t> arr;
        arr.resize(map.size()*(sizeof(K)+sizeof(V)));
        size_t offset=0;
        for (const auto& [k,v]:map){
            memcpy(arr.data()+offset, &k, sizeof(K));
            offset+=sizeof(K);
            memcpy(arr.data()+offset, &v, sizeof(V));
            offset+=sizeof(V);
        }
        attrs[key]=arr;
    }
    template <typename K, typename V>
    std::map<K,V> ReadMap(const std::string& key){
        #warning "this shit is unfinshed
    }
};