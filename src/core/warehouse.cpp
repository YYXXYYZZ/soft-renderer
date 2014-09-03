#include <core/warehouse.h>
#include <stdexcept>
#include <iostream>

Warehouse *Warehouse::instance()
{
    static Warehouse _instance;
    return &_instance;
}

void Warehouse::store(const std::string &key, const int &value)
{
    vector<int> * pVector = int_data[key];
    if (!pVector) {
        pVector = new vector<int>;
        int_data[key] = pVector;
    }
    pVector->push_back(value);
}

void Warehouse::store(const std::string &key, const float &value)
{
    vector<float> * pVector = float_data[key];
    if (!pVector) {
        pVector = new vector<float>;
        float_data[key] = pVector;
    }
    pVector->push_back(value);
}

const std::vector<int> *Warehouse::retrieveInt(const std::string &key) const
{
    std::vector<int> * pVector = NULL;
    try {
       pVector = int_data.at(key);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Warning: try to retrieve none exist values! key : " << key << std::endl;
    }
    return pVector;
}

const std::vector<float> *Warehouse::retrieveFloat(const std::string &key) const
{
    std::vector<float> * pVector = NULL;
    try {
       pVector = float_data.at(key);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Warning: try to retrieve none exist values! key : " << key << std::endl;
    }
    return pVector;
}

void Warehouse::disposalInt(const std::string &key)
{
    std::vector<int> * pVector = int_data[key];
    int_data.erase(key);
    if (!pVector) {
        return;
    }
    delete pVector;
}

void Warehouse::disposalFloat(const std::string &key)
{
    std::vector<float> * pVector = float_data[key];
    float_data.erase(key);
    if (!pVector) {
        return;
    }
    delete pVector;
}

void Warehouse::freeAllMemory()
{
    iter_int_map iter_int;
    for (iter_int = int_data.begin();iter_int!=int_data.end();iter_int++) {
        delete iter_int->second;
    }
    int_data.clear();

    iter_float_map iter_float;
    for (iter_float = float_data.begin();iter_float!=float_data.end();iter_float++) {
        delete iter_float->second;
    }
    float_data.clear();
}

Warehouse::Warehouse()
{

}

Warehouse::~Warehouse()
{
    freeAllMemory();
}
