/*********************************************************
Пример использования:

DArray<int>* a = new DArray<int>();
for (int i = 0; i<10; i++)
    a->add(i, i*i);

for (int i = 0; i < 10; i++)
    cout << a->get(i) << "\n";
*********************************************************/

#pragma once

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <tuple>
#include "BArray.h"
#include "OList.h"


template <class T, size_t BLKCNT=10, size_t BLKSIZE=10>
class IArray
{
private:

    static constexpr auto _opt_column = BLKSIZE * 0.6;

    std::size_t _size;
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

    std::tuple<std::size_t, std::size_t> get_cell(std::size_t idx) const
    {
        if(idx > (BLKSIZE * BLKCNT))
        {
            throw std::range_error("Out of index in IArray");
        }
        if(idx > (_size + 1))
        {
            std::cout << "IArray size: " << _size << std::endl;
            throw std::range_error("Out of index in IArray");
        }

        std::size_t r = 0;
        std::size_t c = 0;
        for(std::size_t i=0; i<BLKCNT; i++)
        {
            c = _data.get(i).size();
            if((r + c) >= idx)
            {
                c = _data.get(i).size() - (idx - r);
                break;
            }
            r = r + c;
        }
        return std::make_tuple(r, c);
    }

public:
    IArray() : _size(0)
    {
    }

    ~IArray()
    {
    }

    T &get(std::size_t index) const
    {
        std::size_t r;
        std::size_t c;
        std::tie(r, c) = get_cell(index);
        return _data.get(r).get(c);
    }


    void set(std::size_t index, const T &val)
    {
        std::size_t r;
        std::size_t c;
        std::tie(r, c) = get_cell(index);
        _data.get(r).set(c, val);
    }


    void add(const T &val)
    {
        if(_size == 0)
        {
            _data.add(BArray<T, BLKSIZE>());
            _data.get(0).add(val);
        }
        else
        {
            std::size_t r;
            std::size_t c;
            std::tie(r, c) = get_cell(_size - 1);
            if(c < _opt_column)
            {
                _data.get(r).add(val);
            }
            else
            {
                _data.add(BArray<T, BLKSIZE>());
                _data.get(r + 1).add(val);
            }
        }
        _size++;
    }


    void insert(std::size_t index, const T &val)
    {


        _size++;
    }


    void remove(std::size_t index)
    {


        _size--;
    }


    std::size_t size()
    {
        return _size;
    }

};

