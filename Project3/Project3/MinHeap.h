#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>
using namespace std;
template<typename TKey, typename TValue>
class MinHeap
{
private:
	// array for the elements which should be heap-sorted
	std::vector<std::pair<TKey, TValue>> m_vec;

public:
	MinHeap() {
		m_vec.push_back(make_pair(INT_MAX, INT_MAX)); //Stack[0] is INT_MAX
	}

	~MinHeap()
	{
		m_vec.clear(); //Remove m_vec vector
	}

	/// <summary>
	/// insert key-value pair
	/// </summary>
	///
	/// <param name="key">
	/// the key that is used for sorting
	/// </param>
	///
	/// <param name="value">
	/// the value that is managed in this heap
	/// </param>
	void Push(TKey key, TValue value)
	{
		m_vec.push_back(make_pair(key, value)); //Push_back with Parameter <key, value>

		if (m_vec.size() == 2) return;//Call Heapify with the parent index as an argument to the pushed position

		for (int i = (m_vec.size() - 1) / 2; i > 0; i--)
		{
			Heapify(i);
		}

	}
	/// <summary>
	/// remove the minimum element
	/// </summary>
	void Pop()
	{
		if (m_vec.size() == 1) return; //m_vec have only m_vec[0]

		if (m_vec.size() == 2) //m_vec has m_vec[0], m_vec[1]
		{
			m_vec.pop_back(); //pop_back
			return;
		}

		pair<TKey, TValue> temp;
		temp = m_vec[1];
		m_vec[1] = m_vec[m_vec.size() - 1];
		m_vec.pop_back();
		Heapify(1);
	}
	/// <summary>
	/// get the minimum element
	/// </summary>
	///
	/// <returns>
	/// the minimum element
	/// </returns>
	std::pair<TKey, TValue> Top()
	{
		if (m_vec.size() != 1) return m_vec[1]; //m_vec[1] is Top, return
	}
	/// <summary>
	/// get the key-value pair which the value is the same as the target
	/// </summary>
	///
	/// <returns>
	/// the key-value pair which the value is the same as the target
	/// </returns>
	std::pair<TKey, TValue> Get(TValue target)
	{
		//explore m_vec
		for (int i = 1; m_vec.size(); i++)
		{
			if (m_vec[i].second == target) return m_vec[i]; //if find, return m_Vec[i]
		}
	}
	/// <summary>
	/// check whether this heap is empty or not
	/// </summary>
	///
	/// <returns>
	/// true if this heap is empty
	/// </returns>
	bool IsEmpty()
	{
		//size of m_vec is 1, only have m_vec[0]
		if (m_vec.size() == 1)
		{
			return true; // true, empty
		}

		return false; // false, not empty
	}
	/// <summary>
	/// change the key of the node which the value is the target.<para/>
	/// In general, the newKey should be smaller than the old key.<para/>
	/// </summary>
	///
	/// <parma name="target">
	/// the target to change the key
	/// </param>
	///
	/// <param name="newKey">
	/// new key for the target
	/// </param>
	void DecKey(TValue target, TKey newKey)
	{
		int ChangePos = 0; //Change Index

		pair<TKey, TValue> Cur = Get(target); //Cur is Find target Key, value

		for (int i = 1; i < m_vec.size(); i++)
		{
			if (m_vec[i].first == Cur.first)
			{
				m_vec[i].first = target; //Update Key
				ChangePos = i; //Get Change Index
			}
		}

		i = ChangePos;

		while (i && (m_vec[i] < m_vec[(i - 1) / 2]))
		{
			swap(m_vec[i], m_vec[(i - 1) / 2]);

			i = (i - 1) / 2;
		}
	}

private:
	/// <summary>
	/// heap-sort, heapify.<para/>
	/// this function can be called recursively
	/// </summary>
	void Heapify(int index)
	{
		int Cur = index; //Cur is Index, Parent
		int left = Cur * 2; //LeftChild index
		int right = Cur * 2 + 1; //RightChild index
		pair<TKey, TValue> temp; //for Swap

		if ((m_vec.size() > left) && (m_vec[left] < m_vec[Cur]))
		{
			Cur = left;
		}

		if ((m_vec.size() > right) && (m_vec[right] < m_vec[Cur]))
		{
			Cur = right;
		}
		//Heapfiy Recursive, Update
		if (Cur != index)
		{	
			//Swap
			temp = m_vec[index];
			m_vec[index] = m_vec[Cur];
			m_vec[Cur] = temp;
			Heapify(Cur); //Recursive Call
		}
	}
};

#endif