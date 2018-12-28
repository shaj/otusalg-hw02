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


#pragma once
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
        {
            _list.add(PQueue(priority));
            _list.head()->getList().add(item);
        }
        else
        {
            if(pl->get().getPriority() > priority)
            { //

            }
            while(1)
            {
                if(pl->get().getPriority() == priority)
                {
                    pl->get().getList()->add(item);
                    break;
                }
                if()
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

