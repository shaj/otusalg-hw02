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

    static constexpr auto _opt_column = BLKSIZE * 0.5;

    std::size_t _size;
    BArray<BArray<T, BLKSIZE>*, BLKCNT> _data;


    std::tuple<std::size_t, std::size_t> get_cell(std::size_t idx) const
    {
        if(idx > (_size))   // max index + 1
        { // Можем добавлять только по 1 элементу
            // std::cout << "IArray size: " << _size << std::endl;
            throw std::range_error("Out of index in IArray");
        }

        std::size_t r = 0;
        std::size_t c = 0;
        std::size_t sum = 0;
        for(std::size_t i=0; i<_data.size(); i++)
        {
            sum += _data.get(i)->size();
            if((sum - 1) >= idx)
            {
                c = idx - ((sum - 1) - (_data.get(i)->size() - 1));
                break;
            }
            r++;
        }
        return std::make_tuple(r, c);
    }



public:
    IArray() : _size(0)
    {
    }

    ~IArray()
    {
        for(std::size_t i=0; i<_data.size(); i++)
        {
            delete _data.get(i);
        }
    }

    T &get(std::size_t index) const
    {
        std::size_t r;
        std::size_t c;
        std::tie(r, c) = get_cell(index);
        return _data.get(r)->get(c);
    }


    void set(std::size_t index, const T &val)
    {
        std::size_t r;
        std::size_t c;
        std::tie(r, c) = get_cell(index);
        _data.get(r)->set(c, val);
    }


    void add(const T &val)
    {
        if(_size == 0)
        {
            _data.add(new BArray<T, BLKSIZE>);
            _data.get(0)->add(val);
        }
        else
        {
            std::size_t r;
            std::size_t c;
            std::tie(r, c) = get_cell(_size-1);
            if(c < _opt_column)
            {
                _data.get(r)->add(val);
            }
            else
            {
                _data.add(new BArray<T, BLKSIZE>);
                _data.get(r + 1)->add(val);
            }
        }
        _size++;
    }


    void debug_print()
    {
        std::size_t rows = _data.size();
        std::cout << "_data rows: " << rows << "\n";
        for(std::size_t i=0; i<rows; i++)
        {
            std::size_t columns = _data.get(i)->size();
            if(columns < BLKSIZE) columns = BLKSIZE;
            for(std::size_t j=0; j<columns; j++)
            {
                if(j < _data.get(i)->size())
                    std::cout << _data.get(i)->get(j) << "  ";
                else
                    std::cout << "X  ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    void insert(std::size_t index, const T &val)
    {
        throw std::runtime_error("IArray::insert() not implemented yet");
        _size++;
    }


    void remove(std::size_t index)
    {
        throw std::runtime_error("IArray::remove() not implemented yet");
        _size--;
    }


    std::size_t size()
    {
        return _size;
    }

};

