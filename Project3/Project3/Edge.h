#ifndef EDGE_H
#define EDGE_H

#ifndef NULL
#define NULL	0
#endif

class Edge
{
private:
	// the key of this edge
    int m_key;
    // the weight of this edge
    int m_weight;
    // the next pointer for the linked list of the edges
    Edge* m_pNext;
	
public:
    Edge(); //Constructor
    Edge(int key, int weight); // Constructor with Parameter

    void SetNext(Edge* pNext); //Set the next pointer of this edge
	int GetKey() const; // Get the key of this edge
    int GetWeight() const; // Get the weight of this edge
    Edge* GetNext() const; // Get the next pointer of this edge
};

#endif