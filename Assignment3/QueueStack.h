#pragma once

namespace assignment3
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack();
		~QueueStack();
		QueueStack(const QueueStack<T>& copy);
		const QueueStack<T>& operator=(const QueueStack<T>& copy);

		inline void Enqueue();
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;
		inline const unsigned int GetCount() const;
		inline const unsigned int GetStackCount() const;

	};

	template<typename T>
	inline QueueStack<T>::QueueStack()
	{
	}

	template<typename T>
	inline QueueStack<T>::~QueueStack()
	{
	}

	template<typename T>
	inline QueueStack<T>::QueueStack(const QueueStack<T>& copy)
	{
	}

	template<typename T>
	inline const QueueStack<T>& QueueStack<T>::operator=(const QueueStack<T>& copy)
	{
		return T();
	}

	template<typename T>
	inline void QueueStack<T>::Enqueue()
	{
	}

	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return T();
	}

	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		return T();
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMax() const
	{
		return T();
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMin() const
	{
		return T();
	}

	template<typename T>
	inline const double QueueStack<T>::GetAverage() const
	{
		return 0.0;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetSum() const
	{
		return T();
	}

	template<typename T>
	inline const unsigned int QueueStack<T>::GetCount() const
	{
		return 0;
	}

	template<typename T>
	inline const unsigned int QueueStack<T>::GetStackCount() const
	{
		return 0;
	}
}