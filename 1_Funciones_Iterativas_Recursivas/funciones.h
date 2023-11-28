#include <iostream>
#include <string>

class Funciones{
    public:
        int sumaIterativa(int n){
            long acum = 0;
            for(int i = 0;i <= n; i++ ){
                acum = acum + i;
            }
            return acum;
        }   

        int sumaRecursiva(int n){
            if (n == 0) {
		        return 0;
	        } else {
		        return n + sumaRecursiva(n - 1);
	        }
        }

        int sumaDirecta(int n){
            return n * (n + 1) / 2;
        }    
    
};
