/**
	@brief Este programa genera 3 ficheros; demanda_a_y_1..dat, demanda_a_y_5.dat, demanda_a_y_10.dat
		    los cuales sirven para representar la ganancia esperada para distinto nº de veces de simulacion y distintos
			 valores de y utilizando la distribucion de probabilidad a) suministrada.
			 NOTA: Se han escogido los siguientes valores de referencia para s y x:
			 			- s=50.
						- x=10.
*/

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <fstream>

using namespace std;

/*

Genera un numero uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores disponibles en C. 
Lo utiliza el generador de demanda.

*/

double uniforme(){
        int t = random();
        double f = ((double)RAND_MAX+1);
        return (double)t/f;
}

//-----------------------------------------------

/*

Construye la tabla de busqueda de tamano n para la distribucion de la demanda del apartado (a).

*/

float* construye_prop_a(int n){
        int i;
        float* temp;

        if ((temp = (float*) malloc(n*sizeof(float))) == NULL){
                fputs("Error reservando memoria para generador uniforme\n",stderr);
                exit(1);
        }

        temp[0] = 1.0/n;

        for (i=1;i<n;i++)
                temp[i] = temp[i-1]+1.0/n;
        
		  return temp;
}

//-----------------------------------------------

/*

Construye la tabla de busqueda de tamano n para la distribucion de la demanda del apartado (b).

*/

float* construye_prop_b(int n){
        int i, max;
        float* temp;

        if ((temp = (float*) malloc(n*sizeof(float))) == NULL){
                fputs("Error reservando memoria para generador proporcional\n",stderr);
                exit(1);
        }

        max = (n/2)*(n+1);
        temp[0] = n*1.0/max;
        
		  for (i=1;i<n;i++)
                temp[i] = temp[i-1]+(float)(n-i)/max;

        return temp;

}

//-----------------------------------------------

/*

Construye la tabla de busqueda de tamano n para la distribucion de la demanda del apartado (c).

*/

float* construye_prop_c(int n){
        int i, max;
        float* temp;

        if ((temp = (float*) malloc(n*sizeof(float))) == NULL){
                fputs("Error reservando memoria para generador triangular\n",stderr);
                exit(1);
        }

        max = n*n/4;
        temp[0] = 0.0;

        for (i=1;i<(n/2);i++)
				temp[i] = temp[i-1]+(float)i/max;



        for (i=(n/2);i<n;i++)
                temp[i] = temp[i-1]+(float)(n-i)/max;
					 
        return temp;
}

//-------------------------------------------------

/*

Genera un valor de la distribucion de la demanda codificada en tabla, por el metodo de tablas de busqueda.

tama es el tamano de la tabla = 100.

*/

int genera_demanda(float* tabla,int tama){
        int i;
        double u = uniforme();
        i = 0;
		  
        while(i<tama && u>=tabla[i])

                i++;
					 
        return i;
}

int main(){

	double sum=0.0,sum2=0.0,ganancia,gananciaesperada;
	int demanda,s=50,x=10,y,veces;
	float * tablademanda;
	ofstream fo[3];
	
	int array_y[3]={1,5,10};
	
	fo[0].open("./datos/demanda_a_y_1_variacion_veces.dat");
	fo[1].open("./datos/demanda_a_y_5_variacion_veces.dat");
	fo[2].open("./datos/demanda_a_y_10_variacion_veces.dat");
	
	srand(time(NULL));
	
		for(int k=0;k<3;k++){
			y=array_y[k];
	
			for(int j=1000;j<=50000;j+=1000)	{
					
					tablademanda= construye_prop_a(100);
					sum=0.0;
					sum2=0.0;

				for(int i=0;i<j;i++){
		
					demanda = genera_demanda(tablademanda,100);

					if(s > demanda)
						ganancia=demanda*x-(s-demanda)*y;
					else
						ganancia=s*x;

					sum+=ganancia;
					sum2+=ganancia*ganancia;
				}


				gananciaesperada=sum/j;

				fo[k] << j << ' ' << gananciaesperada << endl;

			}
		}
		
	for(int i=0;i<3;i++)
		fo[i].close();
	
	return 0;
}
