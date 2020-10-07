/**
	@brief Este programa crea 2 ficheros:
				originalesc.dat
				mejorados1c.dat
			los cuales sirven para representar cuanto tiempo tarda para cada determinado nº de llamadas: el generador
			original para la distribucion de probabilidad c y el generador mejorado para 
			la distribucion de probabilidad c propuesto en el punto 1.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

/*

Genera un numero uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores

disponibles en C. Lo utiliza el generador de demanda.

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

tama es el tamao de la tabla = 100.

*/

int genera_demanda(float* tabla,int tama){
        int i;
        double u = uniforme();
        i = 0;
		  
        while(i<tama && u>=tabla[i])

                i++;
					 
        return i;
}


float* construye_prop_c_orden_decreciente(int n){
        int i,j,z, max;
        float* temp;
		  
        if ((temp = (float*) malloc(n*sizeof(float))) == NULL){
                fputs("Error reservando memoria para generador triangular\n",stderr);
                exit(1);
        }
		  
        max = n*n/4;
        temp[0] = (float) (n/2)/max;
		  
			for(i=(n/2-1),j=1;j<(n-2);i--,j+=2){
				temp[j]=temp[j-1]+(float)i/max;
				temp[j+1]=temp[j]+(float)i/max;
			}
			
			temp[n-1]=temp[n-2]+0;

        return temp;
}


int main(){
	
	float * tablademanda_orig;
	float * tablademanda_c_orden_decreciente;
	srand(time(NULL));
	long int t_inic,t_fin;
	ofstream fo[2];
	
	tablademanda_orig=construye_prop_c(100);
	tablademanda_c_orden_decreciente=construye_prop_c_orden_decreciente(100);
	
		
	fo[0].open("./datos/originalesc.dat");
	fo[1].open("./datos/mejorados1c.dat");
	
	
	for(long int veces=10000000;veces<100000000;veces+=10000000){
			t_inic=time(0);

			for(int i=0;i<veces;i++)
				genera_demanda(tablademanda_c_orden_decreciente,100);

			t_fin=time(0);

			fo[1] << veces << ' ' << t_fin-t_inic << endl;
			
			t_inic=time(0);

			for(int i=0;i<veces;i++)
				genera_demanda(tablademanda_orig,100);

			t_fin=time(0);
			
			fo[0] << veces << ' ' << t_fin-t_inic << endl;
	}
	
	for(int i=0;i<2;i++)
		fo[i].close();
		
	return 0;
} 
