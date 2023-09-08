
#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

template <class T>
class Sorts
{
public:
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> ordenaBurbuja(std::vector<T>&);
    void swap(std::vector<T>&, int , int );

	std::vector<T> ordenaMerge(std::vector<T>&);
	void copyArray(std::vector<T>&,std::vector<T>&,int,int);
    void mergeArray(std::vector<T>&,std::vector<T>&,int, int, int);
    void mergeSplit(std::vector<T>&, std::vector<T>&,int,int);
    std::vector<T> mergeSort(std::vector<T>&);
    
    int busqBinaria(std::vector<T>&, int);
    int busqbAux(std::vector<T>&, int,int, int);
    int busqSecuencial(std::vector<T>&,int);
    };

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(vec[i], vec[minIndex]);
        }
    }
	return vec;
}

template<class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector <T>& vec){
	int n = vec.size() ;
    for(int i = 0; i < n - 1 ; i++ ){//orden
        for(int j = 0; j < n - 1; j++){
            if(vec[j] > vec[j + 1]){
            std::swap(vec[j], vec[j+1]);
            }
        }
    }

	return vec;
}


template<class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector <T>& vec){
	std::vector<T> temporal(vec.size());
    mergeSplit(vec,temporal, 0, vec.size() - 1);
	return vec;
}

template<class T>
void Sorts<T>::mergeSplit(std::vector <T> &A, std::vector<T> &B, int inicio, int alto){
	int mitad;
    if((alto - inicio < 1)){
        return ; //si el rango es menor a uno no hace falta hacer mas recursividad
    }
    mitad = (alto + inicio)/ 2;
    mergeSplit(A , B,inicio,mitad);//llamada recursiva izquierda
    mergeSplit(A, B,mitad + 1, alto );//llamada recursiva derecha
    mergeArray(A, B, inicio, mitad, alto);
    copyArray(A, B, inicio, alto);
}


template<class T>
void Sorts<T>::mergeArray(std::vector <T> &A, std::vector<T> &B, int inicio, int mitad ,int alto){
	int i, j, k;
    i = inicio;
    j = mitad + 1;
    k = inicio;
    while (i <= mitad && j<= alto) {//condicion de paro
        if(A [i]< A[j]) {
            B[k] = A[i];
            i++;
        }else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if(i > mitad){
        for(; j <= alto; j++){
            B[k++] = A[j];
        }
    }else{
        for (; i <= mitad; i++) {
            B[k++]=A[i];
        }
    }
}


template<class T>
void Sorts<T>::copyArray(std::vector <T> &A, std::vector <T> &B, int inicio, int alto){
    for(int i=inicio; i <= alto; ++i ){
        A[i] = B[i];
    }
}

template<class T>
int Sorts<T>::busqSecuencial(std::vector<T> &vec, int n){
    for(int i= 0; i < vec.size(); i++){
        if(vec[i]==n){
            return i; // se encontro
        }
    }
    return -1;// no se encontró
}

template<class T>
int Sorts<T>::busqBinaria(std::vector<T>&vec,int n){
    return busqbAux(vec, 0, vec.size() - 1, n);
}

template<class T>
int Sorts<T>::busqbAux(std::vector<T>& vec, int inicio, int alto,int n){
    int mitad;

	if (inicio <= alto) {
		mitad = (alto + inicio) / 2;
		if (n == vec[mitad]) {
			return mitad;//encuentra caso base
		} else if (n < vec[mitad]) {
			return busqbAux(vec, inicio, mitad - 1, n);//busqueda en la rama izquierda
		} else if (n > vec[mitad]) {
			return busqbAux(vec, mitad + 1, alto, n);//busca en la rama derecha
		}
	}
	return -1;
}

#endif /* SORTS_H_ */
