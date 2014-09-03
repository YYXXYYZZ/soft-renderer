#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

/**
 * @brief The Warehouse class manages the memory in
 * the application.
 */
class Warehouse
{
public:
    static Warehouse *instance();

    void store(const std::string &key,const int &value);
    void store(const std::string &key,const float &value);

    // const make sure the date can't be modified outside
    const vector<int> *retrieveInt(const std::string &key) const;
    const vector<float> *retrieveFloat(const std::string &key) const;

    void disposalInt(const std::string &key);
    void disposalFloat(const std::string &key);

    void freeAllMemory();

private:
    Warehouse();
    ~Warehouse();

    typedef map<string,vector<int> *>::iterator iter_int_map;
    typedef map<string,vector<float> *>::iterator iter_float_map;

    map<string,vector<int> *> int_data;
    map<string,vector<float> *> float_data;

};

#endif // WAREHOUSE_H
