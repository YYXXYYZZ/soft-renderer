#ifndef GPUMEMORY_H
#define GPUMEMORY_H

#include <map>
#include <cstring>
#include <typeindex>
#include <iostream>
#include <exception>

using std::string;
using std::map;
using std::type_index;

namespace GPUMemory {

struct MemoryInfo{
    void * address;
    int size;
    string type;
};
typedef map<string,MemoryInfo> DataMap;

extern DataMap Global_Data;

template<class T>
bool alloc(const string& name, const int & size,T *&pointer){
    try{
        Global_Data.at(name);
        std::cerr << "Warning: alloc exist element! " << name << std::endl;
        return false;
    }
    catch(const std::out_of_range & ){
        MemoryInfo info;
        T *data = new T[size]();
        info.address = static_cast<void *>(data);
        info.size = size;
        info.type = typeid(T).name();
        Global_Data[name] = info;
        pointer = data;
    }
    return true;
}

template<class T>
bool alloc(const string& name, const int & size){
    try{
        Global_Data.at(name);
        std::cerr << "Warning: alloc exist element! " << name << std::endl;
        return false;
    }
    catch(const std::out_of_range & ){
        MemoryInfo info;
        T *data = new T[size]();
        info.address = static_cast<void *>(data);
        info.size = size;
        info.type = typeid(T).name();
        Global_Data[name] = info;
    }
    return true;
}


template<class T>
void dealloc(const string& name)
{
    try{
        MemoryInfo info = Global_Data.at(name);
        if (info.type != typeid(T).name()) {
            std::cerr << "Warning: dealloc a different type elemet! " << name << std::endl;
            return;
        }
        T * data = static_cast<T *>(info.address);
        delete []data;
        Global_Data.erase(name);
    }
    catch(const std::out_of_range & ){
        std::cerr << "Warning: dealloc none-exist element! " << name << std::endl;
    }
}

template<class T>
bool memoryCopy(const string &name, const int &size, T *in_data)
{
    try{
        MemoryInfo mem_info = Global_Data.at(name);
        if (size > mem_info.size) {
            std::cerr << "Warning: memory copy to a smaller space! " << name << std::endl;
            return false;
        }
        if(mem_info.type != typeid(T).name()){
            std::cerr << "Warning: memory copy to a different type! " << name << std::endl;
            return false;
        }
        memcpy(mem_info.address,in_data,size * sizeof(T));
        return true;
    }
    catch(const std::out_of_range & ){
        std::cerr << "Warning: memory copy to none-exist element! " << name << std::endl;
    }
    return false;
}

template<class T>
bool retrieve(const std::string &name,int &size,T *&out_data)
{
    try{
        MemoryInfo mem_info = Global_Data.at(name);
        if(mem_info.type != typeid(T).name()){
            std::cerr << "Warning: retrieve to a different type! " << name << std::endl;
            out_data = NULL;
            return false;
        }
        out_data = static_cast<T *>(mem_info.address);
        size = mem_info.size;
        return true;
    }
    catch(const std::out_of_range & ){
        std::cerr << "Warning: retrieve none-exist element! " << name << std::endl;
    }
    size = 0;
    out_data = NULL;
    return false;
}

} //namespace
#endif // GPUMEMORY_H
