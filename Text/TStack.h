#pragma once

const int MAX_SIZE = 1000;

template <class T>
class Stack
{
	int size, MaxSize;
	T* mas;
public:
Stack(){}

	Stack(int _MaxSize)
	{
		if (_MaxSize <= 0 || _MaxSize > MAX_SIZE)
		{
			throw _MaxSize;
		}
		MaxSize = _MaxSize;
		mas = new T[MaxSize];
		size = 0;
	}

	Stack(const Stack <T>& m) //конструктор копирования
	{
		MaxSize = m.MaxSize;
		mas = new T[MaxSize];
		size = m.size;
		for (int i = 0; i < size; i++)
		{
			mas[i] = m.mas[i];
		}
	}

	~Stack() //деструктор
	{
		delete[]mas;
	}

	Stack& operator=(const Stack <T>& m)
	{
		if (MaxSize != m.MaxSize)
		{
			delete[]mas;
			MaxSize = m.MaxSize;
			mas = new T[MaxSize];
		}
		size = m.size;
		for (int i = 0; i < size; i++)
		{
			mas[i] = m.mas[i];
		}
		return *this;
	}

	bool Empty()
	{
		if (size == 0)
		{
			return true;
		}
		return false;
	}

	bool Full()
	{
		if (size == MaxSize)
		{
			return true;
		}
		return false;
	}

	void Push(T a)
	{
		if (Full())
		{
			throw MaxSize;
		}
		mas[size] = a;
		size++;
	}

	T Pop()
	{
		if (Empty())
		{
			throw 0;
		}
		size = size - 1;
		return mas[size];
	}

	void Clear()
	{
		size = 0;
	}

	T Top()
	{
		if (Empty())
		{
			throw 0;
		}
		return mas[size - 1];
	}

	int GetSize()
	{
		return MaxSize;
	}

	T& operator[](int pos)
	{
		if (pos < 0 || pos >= MaxSize)
		{
			throw pos;
		}
		return mas[pos];
	}

	bool operator==(const Stack<T>& m) const
	{
		if (MaxSize != m.MaxSize || size != m.size)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (mas[i] != m.mas[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Stack<T>& m) const
	{
		return !(*this == m);
	}
};
