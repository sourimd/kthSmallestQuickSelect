#include <iostream>
#include <string>
#include <cstdlib>

class Node{
private:
	Node * prev;
	int value;
	Node * next;
public:
	Node * getPrev(){ return prev; }
	int getValue(){ return value; }
	Node * getNext(){ return next; }

	void setPrev(Node * n){ prev = n; }
	void setValue(int v){ value = v; }
	void setNext(Node * n){ next = n; }

	Node(int v):prev(NULL),value(v),next(NULL){}
	~Node(){ delete prev; delete next; }
};

void insert(Node ** st, int v){
	if( *st == NULL ){
		*st = new Node(v);
	}
	else{
		Node * p = *st;
		while(p->getNext() != NULL){
			p=p->getNext();
		}
		Node * newNode = new Node(v);
		newNode->setPrev( p );
		p->setNext( newNode );
	}
}

Node * getEndNode(Node ** st){
	Node * p = *st;
	while( p->getNext() != NULL ){
		p=p->getNext();
	}
	return p;
}

void quickSelect(Node ** start, Node ** end, int rankLookingFor){
	//std::cout << (*start)->getValue() << " " << (*end)->getValue() << " " << rankLookingFor << " ";
	if( *start == *end ){
		std::cout << (*start)->getValue() << std::endl;
		return;
	}
	int numberOfItemsLessThanPivot = 0;
	Node * pivot = *start;
	Node * p = pivot->getNext();
	Node * theOneBeforeStart;
	Node * theOneAfterEnd;
	Node * temp;
	while( p != *end){
		if( p->getValue() < pivot->getValue() ){
			++numberOfItemsLessThanPivot;
			temp = p;

			p->getPrev()->setNext( p->getNext() );
			p->getNext()->setPrev( p->getPrev() );
			p = p->getNext();
			theOneBeforeStart = (*start)->getPrev();
			if( theOneBeforeStart != NULL ){
				theOneBeforeStart->setNext( temp );
			}
			temp->setPrev( theOneBeforeStart);

			temp->setNext( *start );
			(*start)->setPrev( temp );
			*start = temp;
		}
		else{
			p=p->getNext();
		}
	}
	if( p == *end){
		if( pivot->getValue() > (*end)->getValue() ){
			++numberOfItemsLessThanPivot;
			theOneAfterEnd = (*end)->getNext();
			temp = p;
			p->getPrev()->setNext( p->getNext() );
			if( theOneAfterEnd != NULL ){
				theOneAfterEnd->setPrev( p->getPrev() );
			}
			*end = p->getPrev();
			
			theOneBeforeStart = (*start)->getPrev();
			if(theOneBeforeStart != NULL){
				theOneBeforeStart->setNext( temp );
			}
			temp->setPrev( (*start)->getPrev() );
			temp->setNext( *start );
			(*start)->setPrev( temp );
			*start = temp;
		}
	}

	//std::cout << "Computed " << numberOfItemsLessThanPivot + 1 << " Looking for " << rankLookingFor << std::endl;
	if( numberOfItemsLessThanPivot + 1 == rankLookingFor ){
		std::cout << pivot->getValue() << std::endl;
		return;
	}
	else if( numberOfItemsLessThanPivot + 1 < rankLookingFor ){
		Node * dummyEnd = *end ;
		Node * newStart = pivot->getNext(); // 2nd half
		if( pivot != dummyEnd){
			quickSelect( &newStart, &dummyEnd, rankLookingFor - numberOfItemsLessThanPivot - 1);
		}
		
	}
	else{
		Node * dummyStart = *start ;
		Node * newEnd = pivot->getPrev();  // 1st half
		if( pivot != dummyStart ){
			quickSelect( &dummyStart, &newEnd, rankLookingFor);
		}
	}
}

int main(int argc, char * argv[]){
	Node * startNode = NULL;
	Node * endNode;

	std::string s = argv[1];
	int rank = std::atoi(s.c_str());

	insert(&startNode, 34);
	insert(&startNode, 12);
	insert(&startNode, 71);
	insert(&startNode, 21);
	insert(&startNode, 25);
	insert(&startNode, 56);
	insert(&startNode, 85);
	insert(&startNode, 92);
	insert(&startNode, 43);
	insert(&startNode, 87);
	insert(&startNode, 55);
	insert(&startNode, 11);
	insert(&startNode, 90);
	insert(&startNode, 8);
	insert(&startNode, 57);
	insert(&startNode, 84);
	insert(&startNode, 3);

	endNode = getEndNode(&startNode);
	quickSelect( &startNode, &endNode, rank);
}