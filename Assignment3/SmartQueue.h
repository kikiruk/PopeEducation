#pragma once

namespace assignment3
{
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();
		SmartQueue(const SmartQueue<T>& copy);
		const SmartQueue& operator=(const SmartQueue<T>& copy);

		inline void Enqueue();
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;
		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		T mTmp;
	};

	template<typename T>
	inline SmartQueue<T>::SmartQueue()
	{
		mTmp = 0;
	}

	template<typename T>
	inline SmartQueue<T>::~SmartQueue()
	{
	}

	template<typename T>
	inline SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)
	{
	}

	template<typename T>
	const SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue<T>& copy)
	{
		return SmartQueue<T>();
	}

	template<typename T>
	inline void SmartQueue<T>::Enqueue()
	{
	}

	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mTmp;
	}

	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		return mTmp;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMax() const
	{
		return mTmp;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMin() const
	{
		return mTmp;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetAverage() const
	{
		return 0.0;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetSum() const
	{
		return mTmp;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetVariance() const
	{
		return 0.0;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		return 0.0;
	}

	template<typename T>
	inline const unsigned int SmartQueue<T>::GetCount() const
	{
		return 0;
	}
}