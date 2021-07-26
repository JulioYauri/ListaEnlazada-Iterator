#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include<iostream>
#include<utility>
#include "Node.h"
template<typename T>
class LinkedList;

template<typename T> 
std::ostream& operator<<(std::ostream& salida, LinkedList<T> l);

template<typename T>
class LinkedList{
	private:
		int size;
		Node<T>* head;
	public:
		//constructores y destructor
		LinkedList() : size(0), head(nullptr) {}; //constructor por defecto
		LinkedList(T); //constructor usando un dato para la cabeza
		LinkedList(Node<T>);//constructor usando un nodo para la cabeza
		LinkedList(LinkedList<T> &);//constructor copia
		LinkedList(LinkedList<T> &&);//constructor por movimiento
		~LinkedList();	//destructor
		
		//setters y getters
		Node<T>* getHead(){return head;}
		int getSize(){return size;}
		void setSize(int _size){size = _size;}
		
		//metodos
		void clear();
		void insert(T, int);
		void removeInd(int);
		void removeVal(T);	
		void push_back(T);
		void push_front(T);
		void pop_back();
		void pop_front();
		void print();
		
		//patron iterator
		class iterator {
			friend class LinkedList;
			private:
				Node<T> *ptr;
				iterator(Node<T> *nuevoPtr) : ptr(nuevoPtr) {}
			public:
				iterator() : ptr(nullptr) {}
				//preincremento
				iterator operator++() {
					ptr = ptr -> getNext();
					return *this;	
				}
				//posincremento
				iterator operator++(int) {
					iterator tmp = *this;
					ptr = ptr -> getNext();
					return tmp;	
				}
				//desreferencia 
				T operator*() {return ptr -> getElem();}
				// comparacion
				bool operator!= (const iterator& itr) {return ptr != itr.ptr;}
				bool operator== (const iterator& itr) {return ptr == itr.ptr;}
		};
		iterator begin() const {
			return iterator(head);	
		}
		iterator end() const {
			return iterator();	
		}
		
		//operadores
		friend std::ostream& operator<< <>(std::ostream& salida, LinkedList<T> l); //operador de flujo de salida
		LinkedList<T>& operator= (LinkedList<T>&); //asignacion por lvalue
		LinkedList<T>& operator= (LinkedList<T>&&); //asignacion por rvalue
		bool operator== (LinkedList<T>&) const; //operador de comparacion (igualdad)
		bool operator!= (LinkedList<T>&) const; //operador de comparacion (diferencia)
};

//operador de flujo de salida
template<typename T>
std::ostream& operator<<(std::ostream& salida, LinkedList<T> l){
	Node<T>* aux1 = l.getHead();
	if(aux1 == nullptr){
		salida << "Lista vacia\n";
		return salida;
	}
	while(aux1 != nullptr){
		salida << *aux1;
		aux1 = aux1->getNext();
	}
	salida << '\n';
	return salida;
}

//constructor usando una variable
template<typename T>
LinkedList<T>::LinkedList(T _elem) {
	head = nullptr;
	size = 0;
	push_back(_elem);
}

//constructor usando un nodo (cabeza)
template<typename T>
LinkedList<T>::LinkedList(Node<T> _nodo) {
	head = nullptr;
	size = 0;
	push_back(_nodo.getElem());	
}

//destructor
template<typename T>
LinkedList<T>::~LinkedList(){
	Node<T>* tmp = nullptr;
	if(head != nullptr) {
		while(head != nullptr) {
			tmp = head -> getNext();
			delete head;
			head = tmp;
		}
	}
}

//constructor copia
template<typename T>
LinkedList<T>::LinkedList(LinkedList<T> &lista) {
	Node<T>* tmp = lista.getHead();
	head = nullptr;
	size = 0;
	while(tmp != nullptr) {
		push_back( tmp -> getElem());
		tmp = tmp -> getNext();	
	}
}

//constructor de movimiento
template<typename T> 
LinkedList<T>::LinkedList(LinkedList<T> &&lista) {
	head = lista.head;
	size = lista.size;	
	lista.head = nullptr;
	lista.size = 0;
}

//asignacion por lvalue
template<typename T>
LinkedList<T>& LinkedList<T>::operator= (LinkedList<T> &lista) {
	clear();
	Node<T>* tmp = lista.getHead();
	while(tmp != nullptr) {
		push_back(tmp -> getElem());
		tmp = tmp->getNext();
	}
	return *this;
}

//asignacion por rvalue
template<typename T>
LinkedList<T>& LinkedList<T>::operator= (LinkedList<T> &&lista) {
	if ( &lista != this ){
        head = lista.getHead();     
        size = lista.getSize();
        lista.getHead() = nullptr;
        lista.setSize(0);
    }
    return *this;
}

template<typename T> 
bool LinkedList<T>::operator== (LinkedList<T> &lista) const{
	if(size != lista.getSize()) return false;
	else{
		Node<T>* tmp1 = head;
		Node<T>* tmp2 = lista.getHead();
		while(tmp1 != nullptr && tmp2 != nullptr) {
			if(tmp1 -> getElem() != tmp2 -> getElem()) return false;
			tmp1 = tmp1 -> getNext();
			tmp2 = tmp2 -> getNext();	
		}
	}
	return true;
}

template<typename T>
bool LinkedList<T>::operator!= (LinkedList<T> &lista) const{
	return !(*this == lista);
}

template<typename T>
void LinkedList<T>::clear() {
	Node<T> *tmp = nullptr;
	while(head != nullptr) {
		tmp = head -> getNext();
		delete head;
		head = tmp;	
	}
	head = nullptr;
	size = 0;
}

//inserta un elemento en la lista
//empieza a contar los índices desde 1
template<typename T>
void LinkedList<T>::insert(T n, int pos){
	Node<T> *aux1 = new Node<T>(n);
    Node<T> *aux2 = head;
    //posiciones invalidas
    if(pos <= 0 || pos > size + 1) {
    	std::cout << "Posicion invalida\n";
		return;	
    }
	
	//inserta al inicio
    if(pos == 1) {
    	push_front(n);	
    	return;
	}
	
	//inserta al final 
	if(pos == size + 1) {
		push_back(n);
		return;
	}
//    
//	//lista vacía
//    if (head == nullptr) {
//        head = aux1;
//        size++;
//        return;
//    }
//    //inserta al inicio
//    if(head->getElem() > n) {
//        aux1->setNext(head);
//        head = aux1;
//    }else{
//    	//busca la posicion
//        while((aux2->getNext() != nullptr) && (aux2->getNext())->getElem() < n){
//            aux2=(aux2->getNext());
//        }
//        aux1->setNext(aux2->getNext());
//        aux2->setNext(aux1);
//    }
	Node<T>* nuevoElemento = new Node<T>(n);
	Node<T>* tmp = head;
	int aux = pos;
	aux--;
	while(--aux) tmp = tmp -> getNext();
	nuevoElemento->setNext(tmp->getNext());
	tmp->setNext(nuevoElemento);
    size++;
}

template<typename T> 
void LinkedList<T>::push_back(T n){
	Node<T> *nuevoElemento = new Node<T>(n);
	if(head == nullptr) {
		head = nuevoElemento;
		size++;
		return;	
	}
	
	Node<T> *aux = head;
	while(aux -> getNext() != nullptr) {
		aux = (aux -> getNext());	
	}
	aux->setNext(nuevoElemento);
	size++;
}

template<typename T> 
void LinkedList<T>::push_front(T n){
	Node<T> *nuevoElemento = new Node<T>(n);
	if(head == nullptr) {
		head = nuevoElemento;
		size++;
		return;
	}	
	nuevoElemento->setNext(head);
	head = nuevoElemento;
	size++;
}

template<typename T>
void LinkedList<T>::pop_back(){	
	this->removeInd(this->size);
}

template<typename T> 
void LinkedList<T>::pop_front(){
	this->removeInd(1);	
}

template<typename T>
void LinkedList<T>::removeInd(int pos){
	Node<T> *aux = head;
	Node<T> *ant = nullptr;
    if(aux == nullptr){
    	std::cout << "Lista vacia\n";
    	return;
	}
	if(pos > size){
		std::cout << "Elemento fuera de rango\n";
		return;
	}
	if(pos == 1){
		head = head->getNext();
		size--;
		return;
	}
	pos--;
	while(pos--){
		ant = aux;
		aux = aux -> getNext();
	}
	ant -> setNext(aux->getNext());
	size--;
}

template<typename T>
void LinkedList<T>::removeVal(T val){
	Node<T> *aux = head;
	Node<T> *sig = head->getNext();
	if(head == nullptr){
		std::cout << "Lista vacia\n";
		return;
	}
	while(sig != nullptr){
		if(sig->getElem() == val){
			aux->setNext(sig->getNext());
			size--;
			return;
		}
		aux = aux -> getNext();
		sig = sig -> getNext();
	}
	std::cout << "No se encontro el dato\n";
}

template<typename T> 
void LinkedList<T>::print(){
	Node<T>* aux1 = head;
	if(aux1 == nullptr){
		std::cout << "Lista vacia\n";
		return;
	}
	while(aux1 != nullptr){
		std::cout << *aux1;
		aux1 = aux1->getNext();
	}
	std::cout << '\n';
}

#endif
