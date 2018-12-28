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
template<class T>
class ListItem
{
private:
	T _item;
	ListItem<T>* _next;

public:
	ListItem(T item) {
		_item = item;
        _next = nullptr;
	}

	T get() {
		return _item;
	}

	void setNext(ListItem<T>* item) {
		_next = item;
	}
	ListItem<T>* getNext() {
		return _next;
	}
};



template<class T> class OList
{
private:
	ListItem<T>* _head;
	ListItem<T>* _tail;

public:
	OList()
	{
        _head = nullptr;
        _tail = nullptr;

    }

	~OList()
	{
        ListItem<T>* li;
        while(_head)
        {
            li = _head->getNext();
            delete _head;
            _head = li;
        }
    }

    ListItem<T>* head()
    {
		return _head;
	}

    void add(T item)
    {
		ListItem<T>* li = new ListItem<T>(item);
        if (_head == nullptr)
        {
			_head = li;
			_tail = li;
		}
        else
        {
			_tail->setNext(li);
			_tail = li;
		}
	}

};

