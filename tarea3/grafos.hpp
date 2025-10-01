#include <iostream>

#define VISITADO 1
#define NOVISITADO 0
#define INFINITO INFINITY

typedef int tVertice;
struct tStructVertice{
    bool visitado; // 1 para visitado , 0 para no vistado
    int estado; // 0 para nada , 1 para pasajero , 2 para conductor
};

// Estructura para el MinHeap
struct HeapNode {
    tVertice vertice;
    int distancia;
};

class MinHeap {
private:
    HeapNode* heap;
    int capacity;
    int size;
    
    void flotar(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[parent].distancia > heap[index].distancia) {
            HeapNode temp = heap[parent];
            heap[parent] = heap[index];
            heap[index] = temp;
            flotar(parent);
        }
    }
    
    void hundir(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        
        if (left < size && heap[left].distancia < heap[smallest].distancia)
            smallest = left;
        if (right < size && heap[right].distancia < heap[smallest].distancia)
            smallest = right;
            
        if (smallest != index) {
            HeapNode temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            hundir(smallest);
        }
    }
    
public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new HeapNode[capacity];
    }
    
    ~MinHeap() {
        delete[] heap;
    }
    
    void insert(tVertice v, int dist) {
        if (size >= capacity) return;
        heap[size].vertice = v;
        heap[size].distancia = dist;
        flotar(size);
        size++;
    }
    
    HeapNode extractMin() {
        HeapNode min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        hundir(0);
        return min;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    void decreaseKey(tVertice v, int newDist) {
        for (int i = 0; i < size; i++) {
            if (heap[i].vertice == v) {
                heap[i].distancia = newDist;
                flotar(i);
                break;
            }
        }
    }
    
    bool contains(tVertice v) {
        for (int i = 0; i < size; i++) {
            if (heap[i].vertice == v) return true;
        }
        return false;
    }
};

class tGrafo{
    private:
        tVertice** matriz;
        tStructVertice* info;
        int nVertices;
        int nArcos;
        int maxVertices;
        
    public:
        tGrafo(int n); //constructor
        ~tGrafo();  //destructor
        void setArco(tVertice v1 , tVertice v2);  //crea un arco entre dos vertices
        void quitarArco(tVertice v1 , tVertice v2);  //quita un arco entre dos vertices
        int getNvertices(); //para obtener el numero de vertices
        tVertice first(tVertice v); //primer vecino
        tVertice next(tVertice v, tVertice w); //vecino siguiente al w
        int weight (tVertice v , tVertice w); //retorna siempre 1, es para que dijsktra funcione
        bool esArco (tVertice v, tVertice w); // true para si arco, false para no arco
        void setMark (tVertice v, int g);
        bool getMark (tVertice v); // funcion auxiliar para obtener el estado de visitado
};

tGrafo :: tGrafo (int n){   //O(n)
    matriz = new tVertice*[n];
    for (int i = 0 ; i < n ; i++){
        matriz[i] = new tVertice[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0; // Inicializar matriz
        }
    }
    info = new tStructVertice[n]; // Inicializar el array info
    for (int i = 0; i < n; i++) {
        info[i].visitado = NOVISITADO;
        info[i].estado = 0;
    }
    nVertices = maxVertices = n;
    nArcos = 0;
}

void tGrafo :: setArco(tVertice v1 , tVertice v2){  //O(1)
    matriz[v1-1][v2-1]=1;
    nArcos++;
}

void tGrafo :: quitarArco(tVertice v1 , tVertice v2){   //O(1)
    matriz[v1-1][v2-1]=0;
    nArcos--;
}

int tGrafo :: getNvertices(){   //O(1)
    return nVertices;
}

tVertice tGrafo :: first(tVertice v){   //O(n)
    for (tVertice w=1 ; w<= nVertices ; w++){
        if (matriz[v-1][w-1] == 1 ){return w;} 
    }
    return -1;
}

tVertice tGrafo :: next(tVertice v , tVertice w){   //O(n)
    for (tVertice z=w+1 ; z<= nVertices ; z++){
        if (matriz[v-1][z-1] == 1 ){return z;} 
    }
    return -1;
}

int tGrafo :: weight(tVertice v, tVertice w){   //O(1)
    return 1;
}

bool tGrafo :: esArco(tVertice v, tVertice w){  //O(1)
    return matriz[v-1][w-1]==1;
}

void tGrafo :: setMark(tVertice v, int g){ //O(1)
    info[v-1].visitado = g;
}

bool tGrafo :: getMark(tVertice v){ //O(1)
    return info[v-1].visitado;
}

tGrafo :: ~tGrafo() {   //O(n)
    if (matriz != nullptr) {
        for (int i = 0; i < nVertices; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
    if (info != nullptr) {
        delete[] info;
    }
}

// Implementacion de minVertex usando MinHeap
tVertice minVertex(tGrafo& G, int* D) {
    MinHeap heap(G.getNvertices());
    
    // Insertar todos los vertices no visitados en el heap
    for (int i = 1; i <= G.getNvertices(); i++) {
        if (!G.getMark(i)) {
            heap.insert(i, D[i]);
        }
    }
    
    // Si el heap esta vacio, no hay vertices no visitados
    if (heap.isEmpty()) {
        return -1;
    }
    
    // Extraer el vertice con menor distancia
    HeapNode minNode = heap.extractMin();
    return minNode.vertice;
}

void Dijkstra(tGrafo& G, int *D, tVertice s){   // O(n**3) n = numero de vertices
    tVertice v, w;
    
    // Inicializar todas las distancias como infinito
    for (int i = 1; i <= G.getNvertices(); i++) {
        D[i] = INFINITO;
        G.setMark(i, NOVISITADO);
    }
    
    D[s] = 0; // Distancia del origen a si mismo es 0
    
    for (int i = 0; i < G.getNvertices(); i++) {
        v = minVertex(G, D); // obtiene vertice no visitado con minima distancia a s
        if (v == -1 || D[v] == INFINITO) { // solo vertices inalcanzables por procesar
            return;
        }
        G.setMark(v, VISITADO);  // marca vertice actual como visitado
        for (w = G.first(v); w != -1; w = G.next(v, w)) {
            if (!G.getMark(w) && D[w] > (D[v] + G.weight(v, w))) {
                D[w] = D[v] + G.weight(v, w);
            }
        }
    }
}