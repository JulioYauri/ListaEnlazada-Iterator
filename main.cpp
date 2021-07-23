#include <iostream>
#include "Node.h"
#include "LinkedList.h"
using namespace std;
int main(){
	//primer ejemplo 
	LinkedList<int> enteros;  //constructor por defecto 
	enteros.push_back(4);
	cout << "Primera lista (enteros): ";
	auto itr = enteros.begin();
	cout << *itr << ' ';
	enteros.push_back(9);
	cout << *(++(itr)) << "\n\n";
	
	//constructor con un nodo como parametro
	Node<string> cabeza("buenos");
	LinkedList<string> strings(cabeza);
	cout << "segunda lista de strings (1 elemento): " << strings << '\n';		//operador de flujo de salida
	strings.push_back("dias");			
	strings.push_back("mundo");			//strings = {"buenos", "dias", "mundo"}
	cout << "misma lista, 3 elementos y utilizando iteradores\n";
	for(LinkedList<string>::iterator it = strings.begin(); it != strings.end(); it++) {
		cout << *it << " ";	
	}
	cout << "\n\n";
	
	//asignacion por lvalue
	LinkedList<string> strings2 = strings;
	cout << "Comprobando operador de igualdad \n";
	cout << (strings2 == strings ? "Son iguales\n" : "Son diferentes\n"); //usando operador ==
	
	//asignacion por rvalue
	LinkedList<string> strings3 = move(strings);
	strings3.push_back(", adios");
	cout << "\nMostrando lista 3\n";
	for(auto it = strings3.begin(); it != strings3.end(); it++) cout << *it << " ";
	cout << '\n';
	return 0;
}
