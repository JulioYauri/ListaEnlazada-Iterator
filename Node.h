#ifndef __NODE_H__
#define __NODE_H__
#include<iomanip>

template<typename T>
class Node{
	private:	
		T elem;
		Node<T>* next;
	public:
		Node(){elem = 0; next = nullptr;}
		Node(T _elem){elem = _elem; next = nullptr;}
		Node(Node& n){elem = n.getElem(); next = n.getNext();}
		
		T getElem(){return elem;}
		Node<T>* getNext(){return next;}
		
		void setElem(T n){elem = n;}
		void setNext(Node<T>* n){next = n;}
		
		friend std::ostream &operator<<(std::ostream& salida, Node<T>& n){
			salida << n.elem << " ";
			return salida;
		}
};

#endif
