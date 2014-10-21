#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
#pragma omp parallel for
    for (int var = 0; var < 10; ++var) {
        std::cerr << var<< " id " << omp_get_thread_num()<< endl;
    }
    cout << "Hello World!" << endl;
    return 0;
}

