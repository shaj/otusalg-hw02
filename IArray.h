/*********************************************************
Пример использования:

DArray<int>* a = new DArray<int>();
for (int i = 0; i<10; i++)
    a->add(i, i*i);

for (int i = 0; i < 10; i++)
    cout << a->get(i) << "\n";
*********************************************************/

#pragma once

#include <cstddef>
#include <stdexcept>
#include "BArray.h"
#include "OList.h"


template <class T, size_t BLKCNT=100, size_t BLKSIZE=100>
class IArray
{
private:
    BArray<BArray<T, BLKSIZE>, BLKCNT> _data;

//    void relocate(int newsize, int index)
//    {
//        T* tmp = new T[newsize];

//        if (_arr != nullptr)
//        {
//            for (int i = 0; i < _size; i++)
//            {
//                if (i<index) tmp[i] = _arr[i];
//                else tmp[i + 1] = _arr[i];
//            }
//            delete [] _arr;
//        }
//        _arr = tmp;
//        _size = newsize;
//    }

public:
    IArray()
    {
    }

    ~IArray()
    {
    }

    T get(int index)
    {
        if(index > (BLKSIZE * BLKCNT))
        {
            throw std::range_error("Out of index in IArray");
        }

        T retval;
        int cnt = 0;
        int bs;
        for(int i=0; i<BLKCNT; i++)
        {
            bs = _data.get(i).size();
            if((cnt + bs) > index)
            {
                retval = _data.get(i).get(index - cnt);
                cnt += bs;
                break;
            }
            cnt += bs;
        }

        if(cnt < index)
        {
            throw std::range_error("Out of index in IArray");
        }
        return retval;
    }

    void insert(int index, T element)
    {
        if(index > (BLKSIZE * BLKCNT))
        {
            throw std::range_error("Out of index in IArray");
        }

        int cnt = 0;
        int bs;
        for(int i=0; i<BLKCNT; i++)
        {
            bs = _data.get(i).size();
            if((cnt + bs) > index)
            {
                // Нашли блок, в который нужно писать
                cnt += bs;
                break;
            }
            cnt += bs;
        }

    }

    void set(int index, T element)
    {
        _arr[index] = element;
    }

    int size()
    {
        return _size;
    }

};

