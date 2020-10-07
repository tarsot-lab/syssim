/**
	@brief Este programa implementa el generador basico y=(a*x+c)%m donde:
					- a=2061
					- b=4321
					- c=10000
			 mediante los siguiente metodos:
			 		- Aritmetica Entera.
					- Aritmetica real "artesanal" usando variables tipo float.
					- Aritmetica real "artesanal" corregida usando variables tipo float y double.
					- Aritmetica real usando fmod.
			mostrando los resultados obtenidos por pantalla.
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool encontrado_int(vector<long int> v,long int valor){
	bool encontrado=false;
	
	for(int i=0;i<v.size() && !encontrado;i++)
		if(v[i]==valor)
			encontrado=true;
	
	return encontrado;
}

bool encontrado_float(vector<float> v,float valor){
	bool encontrado=false;
	
	for(int i=0;i<v.size() && !encontrado;i++)
		if(v[i]==valor)
			encontrado=true;
	
	return encontrado;
}

bool encontrado_double(vector<double> v,double valor){
	bool encontrado=false;
	
	for(int i=0;i<v.size() && !encontrado;i++)
		if(v[i]==valor)
			encontrado=true;
	
	return encontrado;
}

int main(){
	int a,c;
	int m=10000;

	//Aritmetica entera.
	long int x_int=1;
	vector<long int> v_int;
	long int periodo_int=0;
	a=2061;
	c=4321;
	
	while(!encontrado_int(v_int,x_int)){
		v_int.push_back(x_int);
		periodo_int++;
		
		x_int=(a*x_int+c)%m;
		
	}
	
	cout << "Periodo para Aritmetica Entera --> " << periodo_int << " con a = " << a << " y c = " << c << endl;
	
	//Aritmetica real "artesanal" float.
	
	float x_float=1;
	vector<float> v_float;
	long int periodo_float=0;
	
	while(!encontrado_float(v_float,x_float)){
		v_float.push_back(x_float);
		periodo_float++;
		
		x_float=(a*x_float+c)/m;
		
		x_float=(x_float-(int)x_float)*m;
	}
	
	cout << "Periodo para Aritmetica \"artesanal\" float  --> " << periodo_float << " con a = " << a << " y c = " << c << endl;
	
	//Aritmetica real "artesanal" double --> No se detiene debido a errores en el redondeo.
	
	//Aritmetica real "artesanal" corregida float.
	
	float x_float_1=1;
	vector<float> v_float_1;
	long int periodo_float_1=0;
	
	while(!encontrado_float(v_float_1,x_float_1)){
		v_float_1.push_back(x_float_1);
		periodo_float_1++;
		
		x_float_1=(a*x_float_1+c)/m;
		
		x_float_1=(x_float_1-(int)x_float_1)*m;
		
		x_float_1=(int)(x_float_1+0.5);
	}
	
	cout << "Periodo para Aritmetica \"artesanal\" corregida float  --> " << periodo_float_1 << " con a = " << a << " y c = " << c << endl;
	
	//Aritmetica real "artesanal" corregida double.
	
	double x_double=1;
	vector<double> v_double;
	long int periodo_double=0;
	
	while(!encontrado_double(v_double,x_double)){
		v_double.push_back(x_double);
		periodo_double++;
		
		x_double=(a*x_double+c)/m;
		
		x_double=(x_double-(int)x_double)*m;
		
		x_double=(int)(x_double+0.5);
	}
	
	cout << "Periodo para Aritmetica \"artesanal\" corregida double  --> " << periodo_double << " con a = " << a << " y c = " << c << endl;
	
	//Aritmetica real usando fmod.
	
	float x_float_f_mod=1;
	vector<float> v_float_f_mod;
	long int periodo_float_f_mod=0;
	
	while(!encontrado_float(v_float_f_mod,x_float_f_mod)){
		v_float_f_mod.push_back(x_float_f_mod);
		periodo_float_f_mod++;
		
		x_float_f_mod = fmod((a*x_float_f_mod+c), m);
	}
	
	cout << "Periodo para Aritmetica real usando fmod  --> " << periodo_float_f_mod << " con a = " << a << " y c = " << c << endl;	
	
	return 0;
}
