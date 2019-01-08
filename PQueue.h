/*********************************************************
Пример использования:

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

    while(pq.size() > 0)
    {
        std::cout << "Dequeue: " << pq.dequeue() << std::endl;
    }

*********************************************************/

#pragma once

#include <iostream>

#include "OList.h"

template<class T>
class PQueueItem
{
private:
    int _priority;
    OList<T> _list;

public:
    PQueueItem() : _priority(0)
    {
    }

    PQueueItem(int p) : _priority(p)
    {
	}

    int getPriority()
    {
        return _priority;
	}

    OList<T> &getList()
    {
        return _list;
	}
};


template<class T>
class PQueue
{
private:
    OList<PQueueItem<T>> _list;
    int _size;

public:
    PQueue() : _size(0)
	{
    }

    ~PQueue()
	{
    }




    void enqueue(int priority, T item)
    {
        auto pl = _list.head();
        if(pl == nullptr)
        { // Пустая очередь
            pl = _list.add(PQueueItem<T>(priority));
            pl->get().getList().add(item);
        }
        else
        {
            if(pl->get().getPriority() > priority)
            { // Приоритет первого элемента больше вставляемого
                // Вставка очереди перед первым элементом
                pl = _list.push_front(PQueueItem<T>(priority));
                pl->get().getList().add(item);
            }
            else
            { // Поиск места среди приоритетов
                auto pln = pl->getNext();
                if(pln == nullptr)
                {
                    pl = _list.add(PQueueItem<T>(priority));
                    pl->get().getList().add(item);
                }
                else
                {
                    while(1)
                    {
                        if(pln == nullptr)
                        {
                            pl = _list.add(PQueueItem<T>(priority));
                            pl->get().getList().add(item);
                            break;
                        }
                        else if(pln->get().getPriority() == priority)
                        { // Приоритет очередного списка равен вставляемому
                            pln->get().getList().add(item);
                            break;
                        }
                        else if(pln->get().getPriority() > priority)
                        {
                            // Вставка очереди перед текущим списком
                            auto nit = new ListItem<PQueueItem<T>>(PQueueItem<T>(priority));
                            nit->setNext(pl->getNext());
                            pl->setNext(nit);
                            nit->get().getList().add(item);
                            break;
                        }
                        pl = pln;
                        pln = pl->getNext();
                    }
                }
            }
        }
        _size++;
    }


    T dequeue()
    {
        T retval;
        if(_list.head() == nullptr)
            throw std::range_error("Empty queue");
        retval = _list.head()->get().getList().pop_front();
        if(_list.head()->get().getList().size() == 0)
        {
            _list.pop_front();
        }
        _size--;
        return  retval;
    }


    int size()
    {
        return _size;
    }

    void debugPrint()
    {
        auto li = _list.head();
        std::cout << "\n";
        while(li != nullptr)
        {
            std::cout << "Priority: " << li->get().getPriority() << "\n";
            auto it = li->get().getList().head();
            while(it != nullptr)
            {
                std::cout << "   item: " << it->get() << "\n";
                it = it->getNext();
            }
            li = li->getNext();
        }
        std::cout << std::endl;
    }


};

