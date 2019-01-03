/*********************************************************
Пример использования:

OList<int>* a = new OList<int>();
for (int i = 0; i < 10; i++)
	a->add(i*i);

ListItem<int>* li = a->head();
while (li != NULL)
{
	cout << li->get() << "\n";
	li = li->getNext();
}
*********************************************************/

#pragma once

#include "OList.h"

template<class T>
class PQueueItem
{
private:
    int _priority;
    OList<T> _list;

public:
    PQueueItem(int p) : _priority(p)
    {
	}

    int getPriority()
    {
        return _priority;
	}

    OList<T> &getList() const
    {
        return *_list;
	}
};


template<class T> class PQueue
{
private:
    OList<PQueueItem<T>> _list;

public:
    PQueue()
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
            _list.add(PQueue(priority));
            _list.head()->getList().add(item);
        }
        else
        {
            if(pl->get().getPriority() > priority)
            { // Приоритет первого элемента больше вставляемого
                // Вставка очереди перед первым элементом
                pl->push_front(PQueue(priority));
                pl->getList().add(item);
            }
            else
            { // Поиск места среди приоритетов
                auto pln = pl->next();
                if(pln == nullptr)
                {
                    pl->add(PQueue(priority));
                    pl->head()->getList().add(item);
                }
                else
                {
                    while(1)
                    {
                        if(pln == nullptr)
                        {
                            pl->add(PQueue(priority));
                            pl->head()->getList().add(item);
                            break;
                        }
                        else if(pln->get().getPriority() == priority)
                        { // Приоритет очередного списка равен вставляемому
                            pln->get().getList()->add(item);
                            break;
                        }
                        else if(pln->get().getPriority() > priority)
                        {
                            // Вставка очереди перед текущим списком
                            pl->add(PQueue(priority));
                            pl->head()->getList().add(item);
                            break;
                        }
                        pl = pln;
                        pln = pl->next();
                    }
                }
            }
        }
    }




    T dequeue()
    {
        T retval = _list.head()->pop();
        if(_list.head()->getList().size() == 0)
        {
            _list.pop();
        }
    }
};

