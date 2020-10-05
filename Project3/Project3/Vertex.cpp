#include "Vertex.h"

//Constructor
Vertex::Vertex()
{
	m_key = 0;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}
//Constructor with Parameter
Vertex::Vertex(int key)
{
	m_key = key;
	m_pNext = NULL;
	m_size = 0;
	m_pEHead = NULL;
}
//Destructor
Vertex::~Vertex()
{
	this->Clear();
}
// Set the next pointer of this vertex
void Vertex::SetNext(Vertex* pNext)
{
	m_pNext = pNext;
}
// Get the key of this vertex
int Vertex::GetKey() const
{
	return m_key;
}
// Get the next pointer of this vertex
Vertex* Vertex::GetNext() const
{
	return m_pNext;
}
// Get the number of the edges
int Vertex::Size() const
{
	return m_size;
}
// Add edge with edgeNum at the end of the linked list for the edges
void Vertex::AddEdge(int edgeKey, int weight)
{
	//Not Exist Edge
	if (m_pEHead == NULL)
	{	
		Edge* New_Edge = new Edge(edgeKey, weight); //Create New Edge with Parameter

		this->m_pEHead = New_Edge; //m_pEHead is New_Edge

		m_size++; //Plus Edge Size

		New_Edge = NULL;
		delete New_Edge;

		return;
	}
	//Exist Edge
	else
	{
		Edge* CurEdge = m_pEHead; //CurEdge is Most First Edge

		//While Loop
		//CurEdge Point to the last Edge
		while (CurEdge->GetNext() != NULL)
		{
			CurEdge = CurEdge->GetNext();
		}

		Edge* New_Edge = new Edge(edgeKey, weight); //Create New Edge with Parameter
		CurEdge->SetNext(New_Edge); //Last Edge -> New_Edge

		m_size++; //Plus Edge Size

		New_Edge = NULL;
		delete New_Edge;

		return;

	}
}
// Get the head pointer of the edge
Edge* Vertex::GetHeadOfEdge() const
{
	return m_pEHead;
}
// Memory free for edges
void Vertex::Clear()
{
	if (m_pEHead == NULL)
	{
		return;   //There is no edge connected with this Vertex
	}
	else
	{   //Delete all edge from first to end connected with this Vertex
		Edge* pCur = NULL;
		for (;;)
		{
			pCur = m_pEHead;
			if (pCur->GetNext() != NULL)
			{
				m_pEHead = pCur->GetNext();
				delete pCur;
			}
			else break;
		}
		delete pCur;
		m_pEHead = NULL;
	}
}