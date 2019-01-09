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

template <class T, std::size_t BLOCK>
class BArray
{
private:
    std::size_t _size;
    std::size_t _max_idx;
    bool _empty;
    T* _arr;

    void relocate(std::size_t newsize, std::size_t index)
    {
        T* tmp = new T[newsize];

        if (_arr != nullptr)
        {
            for (std::size_t i = 0; i < _size; i++)
            {
                if (i<index) tmp[i] = _arr[i];
                else tmp[i + 1] = _arr[i];
            }
            delete [] _arr;
        }
        _arr = tmp;
        _size = newsize;
    }

    void add(std::size_t index, const T &element)
    {
        if (_arr == nullptr || _size <= index)
            relocate(((index/BLOCK) + 1) * BLOCK, index);
        _arr[index] = element;

        if(index > _max_idx) _max_idx = index;
        _empty = false;
    }


public:
    BArray()
    {
        _arr = nullptr;
        _size = 0;
        _max_idx = 0;
        _empty = true;
    }

    ~BArray()
    {
        if (_arr != nullptr)
            delete [] _arr;
    }

    T &get(std::size_t index) const
    {
        return _arr[index];
    }

    void add(const T &val)
    {
        if(_empty) add(0, val);
        else add(_max_idx+1, val);

    }

    void insert(std::size_t index, const T &val)
    {
        if(index > _max_idx)
            add(index, val);
        else
        {
            add(_max_idx + 1, val);   // Выделяем место для нового элемента
            for(std::size_t i=_max_idx; i>index ; i--)
            {
                _arr[i] = _arr[i-1];
            }
            _arr[index] = val;
        }
    }

    void remove(std::size_t index)
    {
//        throw std::runtime_error("BArray::remove() not implemented yet");
        if(index > _max_idx)
            throw std::range_error("Out of index in BArray remove");
        if(index == _max_idx)
        {
            _max_idx--;
        }
        else
        {
            for(std::size_t i=index; i<_max_idx; i++)
                _arr[i] = _arr[i+1];
            _max_idx--;
        }
    }

    void set(std::size_t index, const T &element)
    {
        _arr[index] = element;
        if(index > _max_idx) _max_idx = index;
    }

    std::size_t size() const
    {
        if(_empty) return 0;
        else return _max_idx + 1;
    }

};

