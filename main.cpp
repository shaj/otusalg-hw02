
#include <iostream>

#include "DArray.h"
#include "BArray.h"
#include "IArray.h"

#define TEST_SIZE 200000


#include <chrono>

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F&& func, Args&&... args)
    {
        auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT>
                            (std::chrono::steady_clock::now() - start);
        return duration.count();
    }
};


int main()
{
    long long int retval = 0;

    for(int j=0; j<10; j++)
    {
        DArray<int> *a = new DArray<int>();
        std::cout << "Fill DArray: " << measure<>::execution([&]()
            {
                for (int i=0; i<TEST_SIZE; i++)
                    a->add(i, i*i);
            }
        ) << "ms\n";
        std::cout << "Read DArray: " << measure<>::execution([&]()
            {
                for (int i=0; i<TEST_SIZE; i++)
                    retval += a->get(i);
            }
        ) << "ms\n";
        std::cout << std::endl;
        delete a;
    }
    std::cout << "retval = " << retval << std::endl;



    for(int j=0; j<10; j++)
    {
        BArray<int, 100> *a = new BArray<int, 100>();
        std::cout << "Fill BArray: " << measure<>::execution([&]()
            {
                for (int i=0; i<TEST_SIZE; i++)
                    a->add(i, i*i);
            }
        ) << "ms\n";
        std::cout << "Read BArray: " << measure<>::execution([&]()
            {
                for (int i=0; i<TEST_SIZE; i++)
                    retval += a->get(i);
            }
        ) << "ms\n";
        std::cout << std::endl;
        delete a;
    }
    std::cout << "retval = " << retval << std::endl;

    return 0;
}

