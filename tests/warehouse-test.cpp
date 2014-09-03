#include <iostream>
#include <unistd.h>

#include "core/warehouse.h"

using namespace std;

int main()
{
    for (int var = 0; var < 65535; ++var) {
        Warehouse::instance()->store("exist",var);
    }

    const std::vector<int> * pVector = Warehouse::instance()->retrieveInt("exist");
    cout << "is size? "<< pVector->size() <<endl;

    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    Warehouse::instance()->store("float",15.0f);
    //    std::vector<float> * pVector3 = Warehouse::instance()->retrieveFloat("float");
    //    for (int var = 0; var < pVector3->size(); ++var) {
    //        cout << pVector3->at(var) << endl;
    //    }

    //    cout << "disposal" <<endl;
    //    Warehouse::instance()->disposalInt("exist");
    //    pVector = Warehouse::instance()->retrieveInt("exist");
    //    for (int var = 0; var < pVector->size(); ++var) {
    //        cout << pVector->at(var) << endl;
    //    }
    //    cout << "clear" <<endl;

    //    cout << "disposal-float" <<endl;
    //    Warehouse::instance()->disposalFloat("float");
    //    pVector3 = Warehouse::instance()->retrieveFloat("float");
    //    for (int var = 0; var < pVector3->size(); ++var) {
    //        cout << pVector3->at(var) << endl;
    //    }
    //    cout << "clear" <<endl;
    Warehouse::instance()->freeAllMemory();

    return 0;
}

