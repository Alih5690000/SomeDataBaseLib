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

/**
 * @brief Just a database. Look at methods brief if you want to know more.
 */
class DataBase{
    public:
    /**
     * @brief Just fields of database.
     * @note Storing types with pointer as field or with vtable is NOT RECOMENDED
     */
    std::map<std::string,std::vector<std::uint8_t>> attrs;
    /**
     * @brief Constructor with path to database.
     * @param path Path to database.
     */
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

    /**
     * @brief Default constructor with no parameters.
     */
    DataBase()=default;
    /**
     * @brief Dumps whole database to file.
     * @param path Path to database.
     */
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
    /**
     * @brief Adds integer to DataBase::atrs eventually turning it into vector of uint8_t
     * @param key Key.
     * @param num Integer to be stored.
     */
    void AddInt(const std::string& key, uint32_t num){
        std::vector<uint8_t> arr;
        arr.resize(4);
        memcpy(arr.data(), &num, sizeof(uint32_t));
        attrs[key]=std::move(arr);
    }
    /**
     * @brief Adds string to DataBase::atrs eventually turning it into vector of uint8_t
     * @param key Key.
     * @param str String to be stored.
     */
    void AddStr(const std::string& key, const std::string& str){
        std::vector<uint8_t> arr;
        arr.resize(str.size());
        memcpy(arr.data(), str.data(), str.size());
        attrs[key]=std::move(arr);
    }
    /**
     * @brief Adds vector to DataBase::atrs eventually turning it into vector of uint8_t
     * @param key Key.
     * @param vec Vector to be stored.
     * @param T Template parameter which is type of a vector.
     */
    template <typename T>
    void AddVector(const std::string& key, const std::vector<T>& vec){
        std::vector<uint8_t> arr;
        arr.resize(vec.size()*sizeof(T));
        memcpy(arr.data(), vec.data(), vec.size()*sizeof(T));
        attrs[key]=std::move(arr);
    }
    /**
     * @brief Reads bytes and converts it to std::vector.
     * @param key Key.
     * @param T Type of std::vector
     * @return Vector with T type
     */
    template <typename T>
    std::vector<T> ReadVector(const std::string& key){
        std::vector<T> l(attrs[key].size()/sizeof(T));
        memcpy(l.data(), attrs[key].data(), attrs[key].size());
    }
    /**
     * @brief Adds map to DataBase::atrs eventually turning it into vector of uint8_t
     * @param key Key.
     * @param map Map to be stored.
     * @param K Type of key
     * @param V Type of value
     */
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
        attrs[key]=std::move(arr);
    }
    /**
     * @brief Reads bytes and converts it to std::vector.
     * @param key Key.
     * @param K Type of key
     * @param V Type of value
     */
    template <typename K, typename V>
    std::map<K,V> ReadMap(const std::string& key){
        const std::vector<uint8_t>& arr=attrs[key];
        std::map<K,V> res;
        int i=0;
        while(i<arr.size()){
            K k;
            memcpy(&k, arr.data()+i, sizeof(K));
            i+=sizeof(K);
            V v;
            memcpy(&v, arr.data()+i, sizeof(V));
            i+=sizeof(V);
            res[k]=v;
        }
        return res;
    }
};