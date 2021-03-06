
#include <iostream>

#include "DArray.h"
#include "BArray.h"
#include "IArray.h"
#include "PQueue.h"

#define TEST_SIZE 100


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
                    a->add(i*i);
            }
        ) << "ms\n";
        std::cout << "Read BArray: " << measure<>::execution([&]()
            {
                for (std::size_t i=0; i<TEST_SIZE; i++)
                    retval += a->get(i);
            }
        ) << "ms\n";
        std::cout << std::endl;
        delete a;
    }
    std::cout << "retval = " << retval << std::endl;


    {
        BArray<int, 5> a;
        for(int i=0; i<22; i++)
        {
            std::cout << "a.size() " << a.size() << "\n";
            a.insert(0, i);
        }
        std::cout << "BArray size: " << a.size() << std::endl;
        for(std::size_t i=0; i<a.size(); i++)
        {
            std::cout << a.get(i) << "  ";
        }
        std::cout << std::endl;
    }

    {
        IArray<int, 10, 10> a;
        for(int i=0; i<125; i++)
        {
            a.add(i);
        }

        a.debug_print();

        for(int i=0; i<13; i++)
            a.insert(23, i);

        a.remove(38);

        for(int i=0; i<12; i++)
            a.remove(44);

        a.debug_print();

        for(std::size_t i=0; i<a.size(); i++)
        {
            std::cout << a.get(i) << "  ";
        }
        std::cout << std::endl;

    }



    PQueue<int> pq;
    pq.enqueue(20, 20);
    pq.enqueue(3, 3);
    pq.enqueue(2, 2);
    pq.enqueue(1, 1);
    pq.enqueue(10, 10);
    pq.enqueue(20, 20);
    pq.enqueue(30, 30);
    pq.enqueue(5, 5);


    pq.enqueue(20, 25);
    pq.enqueue(20, 24);
    pq.enqueue(20, 23);
    pq.enqueue(20, 22);


    pq.debugPrint();

    while(pq.size() > 0)
    {
        std::cout << "Dequeue: " << pq.dequeue() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

