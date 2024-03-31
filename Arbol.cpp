#include <iostream>
#include <fstream>//para leer archivos
#include <vector> //Estructura de dato vector, con push etc... ya implementado
#include <algorithm>
#include <chrono>// Para medir el tiempo de ejecución
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::max; //Es para obtener el maximo
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


class Node;

class Node {
  public:
    int key;  //Un entero que representa la clave del nodo.
    Node *parent; //Un puntero a Node que apunta al nodo padre. Si el nodo es la raíz del árbol, este puntero será nullptr.
    vector < Node *> children;  //Un vector de punteros a Node, que contiene los nodos hijos del nodo actual. O(1)
    
    //constructor
    Node(){
      this->parent = nullptr;//inicializa el puntero parent a nullptr, lo que significa que inicialmente el nodo no tiene padre.
    }
    
    //Establecer padre
    void setParent(Node *theparent){
      this->parent = theparent; // asigna el puntero theparent al miembro parent del nodo actual. Esto establece quién es el padre del nodo actual.
      this->parent->children.push_back(this);  
      /* Aquí, estamos accediendo al vector de hijos del nodo padre (this->parent->children) 
	  y agregando al nodo hijo (this) como uno de los hijos del nodo padre*/
    }    
};

vector<Node> newTree_desdeArchivo(const string& nombrearchivo){//funcion nuevo arbol, desde archivo
    ifstream archivo(nombrearchivo); //crea objeto ifstream para leer datos de un archivo

//Si el archivo no se puede abrir correctamente
    if(!archivo.is_open()){
		cerr<<"Error al abrir el archivo."<<endl;//salida de error
		exit(1);//finalizacion del programa por error
		}
		
	int n;
	archivo>>n;

  
  vector <Node> Nodos(n);  //Este es el arbol
  /*Se crea un vector de objetos tipo Node llamado Nodos con una longitud igual a n. 
  Este vector almacenará todos los nodos del árbol que se está construyendo.*/
  for (int child_index =0 ; child_index < n ; child_index++){
    int parent_index;
    archivo >> parent_index;  
    
    if(parent_index  == -1){
      Nodos[child_index].key = child_index;  //Nodo raiz
    }
    else{
      Nodos[child_index].key = child_index;
      Nodos[child_index].setParent(&Nodos[parent_index]);  
    }  
  }
  archivo.close();//cerrar archivo
  return Nodos;
}

void monstrarArbol(vector<Node> A){

  cout<<"\nIMPRIMIENDO ARBOL: "<<endl;
  cout<<"----------------- "<<endl;
  for (int i = 0; i < A.size(); i++){
    cout<<"\nPadre: "<<i<<endl;
    vector<Node *> hijos = A[i].children;
    if(A[i].parent == NULL)
      cout<<"Raiz del Arbol"<<endl;

    if(hijos.size() != 0){
      cout<<"Hijos: ";
      for (int h = 0; h < hijos.size(); h++)
      {
        cout<<hijos[h]->key<<" ";
      }
      cout<<endl;
    }
    else
      cout<<"Hoja"<<endl;
  }  
}
//Metodo 1 O(n^2)
int  Height_1(vector<Node> A){ //Vector de hojas 
  int altura; //variable para almacenar la altura del arbol
  for(int indice_hoja = 0 ; indice_hoja<A.size() ; indice_hoja++)//itera sobre todos los nodos del arbol representados por vector A
  {
    int mi_altura=0;  // Para cada nodo calculamos la altura de ese nodo 
    for(Node *v= &A[indice_hoja] ; v != NULL ; v = v->parent){
      mi_altura++; //La altura "del nodo" es decir desde el nodo hasta la raiz  
    }
  if( mi_altura > altura ){
    altura = max(altura,mi_altura);
    altura=mi_altura;
  } 
  }
  
  
  return altura;
}


int calcularHeight(Node* node, vector<int>& heights) {
    if (node == nullptr) {
        return 0;
    }
    // Verifica si la altura del nodo actual ya ha sido calculada y almacenada en el vector heights
    if (heights[node->key] != -1) { 
        return heights[node->key];
    }

//Almacenar la altura máxima de los hijos del nodo actual.
    int maxChildHeight = 0;
    //recorre todos los hijos del nodo actual 
    for (Node* child : node->children) {
        maxChildHeight = max(maxChildHeight, calcularHeight(child, heights));
    }
    heights[node->key] = 1 + maxChildHeight; 
    return heights[node->key]; //devuelve la altura del nodo actual.
}

//Metodo 2 O(n)
int Height_2(vector<Node>& arbol) {
    vector<int> heights(arbol.size(), -1); // Inicializamos la matriz de alturas con -1
    int maxHeight = 0; //almacenará la altura máxima del árbol, inicializa en 0 
    for (Node& node : arbol) {
        maxHeight = max(maxHeight, calcularHeight(&node, heights));
    }
    return maxHeight;
}


int main() {
    vector<Node> arbol1;
    string Archivo1 ="1.dat";
    arbol1 = newTree_desdeArchivo(Archivo1);
    //monstrarArbol(arbol1);

    
    // Medición del tiempo de ejecución para el método 1 O(n^2)
    auto inicio_1 = high_resolution_clock::now(); // tiempo de inicio 
    int altura_1 = Height_1(arbol1);
    auto final_1 = high_resolution_clock::now();//tiempo final
    auto duracion_1 = duration_cast<milliseconds>(final_1 - inicio_1); // Usamos ms  para comparar tiempo final-inicial
 
 // Medición del tiempo de ejecución para el método 2 O(n)
    auto inicio_2 = high_resolution_clock::now(); 
    int altura_2 = Height_2(arbol1);
    auto final_2 = high_resolution_clock::now();
    auto duracion_2 = duration_cast<milliseconds>(final_2 - inicio_2); 
    
 // Imprimiendo los resultados
 cout<<"\n\tImprimiendo 1.dat"<<endl;
 cout<<"\t*****************"<<endl;
 cout<< "\nAltura con la función con complejidad computacional O(n^2)"<<endl;
 cout<<"----------------------------------------------------------"<<endl;
 cout << "Altura del árbol: " << altura_1<< endl;
 cout << "Tiempo de ejecución: " << duracion_1.count() << " ms" << endl;
 cout<< "\nAltura con la función con complejidad computacional O(n)"<<endl;
 cout<<"--------------------------------------------------------"<<endl;
 cout << "Altura del árbol: " << altura_2<< endl;
 cout << "Tiempo de ejecución: " << duracion_2.count() << " ms" << endl;
  cout<<"\n\tEs claro que "<<duracion_1.count()<<" ms > " <<duracion_2.count()<<" ms"<<endl;
  cout<<"________________________________________________________"<<endl<<endl;
 
  vector<Node> arbol2;
    string Archivo2 ="2.dat";
    arbol2 = newTree_desdeArchivo(Archivo2);
    //monstrarArbol(arbol2);

    
    // Medición del tiempo de ejecución para el método 1 O(n^2)
    auto inicio_3 = high_resolution_clock::now(); // tiempo de inicio 
    int altura_3 = Height_1(arbol2);
    auto final_3 = high_resolution_clock::now();
    auto duracion_3 = duration_cast<milliseconds>(final_3 - inicio_3); // Usamos microsegundos compara tiempo final-inicial
 
 // Medición del tiempo de ejecución para el método 2 O(n)
    auto inicio_4 = high_resolution_clock::now(); // tiempo de inicio 
    int altura_4 = Height_2(arbol2);
    auto final_4 = high_resolution_clock::now();
    auto duracion_4 = duration_cast<milliseconds>(final_4 - inicio_4); // Usamos milisegundos compara tiempo final-inicial
 // Imprimimos los resultados
 cout<<"\n\tImprimiendo 2.dat"<<endl;
 cout<<"\t*****************"<<endl;
 cout<< "\nAltura con la función con complejidad computacional O(n^2)"<<endl;
 cout<<"----------------------------------------------------------"<<endl;
 cout << "Altura del árbol: " << altura_3<< endl;
 cout << "Tiempo de ejecución: " << duracion_3.count() << " ms" << endl;
 cout<< "\nAltura con la función con complejidad computacional O(n)"<<endl;
 cout<<"--------------------------------------------------------"<<endl;
 cout << "Altura del árbol: " << altura_4<< endl;
 cout << "Tiempo de ejecución: " << duracion_4.count() << " ms" << endl;
  cout<<"\n\tEs claro que "<<duracion_3.count()<<" ms > " <<duracion_4.count()<<" ms"<<endl;
  cout<<"________________________________________________________"<<endl;

    return 0;
}

