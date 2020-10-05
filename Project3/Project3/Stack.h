#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;

		StackNode(T data) : Data(data), pNext(NULL) {}
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;

public:
	//constructor
	Stack()
	{
		m_pTop = NULL;
	}

	//Destructor
	//Until stack is empty, recursive Call Pop function
	~Stack()
	{
		if (IsEmpty()) return; //if stack is empty

		//Until stack is empty, recursive Call Pop function
		while (m_pTop != NULL)
		{
			Pop();
		}
	}
	/// <summary>
	/// push the data into this stack
	/// </summary>
	///
	/// <param name="data">
	/// a data to push into this stack
	/// </param>
	void Push(T data)
	{
		//if m_pTop is Not Exist
		if (m_pTop == NULL)
		{
			StackNode *New_Node = new StackNode(data); //new Stack Node
			m_pTop = New_Node; //m_pTop is New_Node
		}
		//if m_pTop is Exist
		else
		{
			StackNode *New_Node = new StackNode(data); //new Stack Node
			New_Node->pNext = m_pTop; //New_Node -> m_pTop
			m_pTop = New_Node; //Set NewNode to m_pTop
		}
	}
	/// <summary>
	/// pop(remove) the last-in data from this stack
	/// </summary>
	void Pop()
	{
		if (IsEmpty()) return; //if Stack is Empty()

		StackNode *Cur = m_pTop; //Cur Pointer is m_pTop

		m_pTop = Cur->pNext; //m_pTop is Cur's Next

		delete Cur; // Memory free for the StackNode

	}
	/// <summary>
	/// get the last-in data of this stack
	/// </summary>
	/// 
	/// <returns>
	/// the last-in data of this stack
	/// </returns>
	T Top()
	{
		if (m_pTop != NULL) return m_pTop->Data; //return Data of m_pTop
	}
	/// <summary>
	/// check whether this stack is empty or not.
	/// </summary>
	///
	/// <returns>
	/// true if this stack is empty.
	/// false otherwise.
	/// </returns>
	bool IsEmpty()
	{
		if (m_pTop == NULL)
		{
			return true; //Stack is Empty
		}

		return false; //Stack is NotEmpty
	}
};
#endif