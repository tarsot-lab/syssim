#include <iostream>
#include <cmath>

#define numeq 2

using namespace std;

void procedimiento_integracion(float * inp, float * out, float &t, const float dt, 
                               const float tfin,      
                               float * f, const float a11, const float a12,
                               const float a21, const float a22);
void one_step_runge_kutta(float * inp,float * out,const float tt,const float hh,
                          float * f, const float a11, const float a12,
                          const float a21, const float a22);
void derivacion(float * est,float * f,const float tt,
                const float a11, const float a12, const float a21, const float a22);

int main(int argc, char ** argv){
    //comprobación del número de parámetros
    if(argc != 9){
       cerr << "Numero de parametros incorrectos" << endl;
       cerr << "Uso: %euler inc_tiempo tfin a11 a12 a21 a22 xinicial yinicial" << endl;
       exit(1);
    }
    
    //se inicializan los parametros
    float dt,tiempo;
    dt = atof(argv[1]);
    float tfin = atof(argv[2]);
    float a11 = atof(argv[3]);
    float a12 = atof(argv[4]);
    float a21 = atof(argv[5]);
    float a22 = atof(argv[6]);
    tiempo = 0;
    float inp[2]={0,0};
    float out[2]={atof(argv[7]),atof(argv[8])};
    float f[2]={0,0};
    
    procedimiento_integracion(inp,out,tiempo,dt,tfin,f,a11,a12,a21,a22);
    
    cout << "#Informe de la simulacion" << endl;
    cout << "#Poblacion de x: " << out[0] << endl;
    cout << "#Poblacion de y: " << out[1] << endl;
    cout << "#En el instante de tiempo " << tiempo << endl;
    cout << "#Con un incremento de " << dt << endl;
    cout << "#Se simularon " << tfin << " unidades de tiempo." << endl;
    cout << endl << endl;
    
    return 0;
}


void procedimiento_integracion(float * inp, float * out, float &t, const float dt,
                               const float tfin, 
                               float * f, const float a11, const float a12,
                               const float a21, const float a22){
   do{
      for(int i=0; i < numeq; i++)
         inp[i]=out[i];
      one_step_runge_kutta(inp,out,t,dt,f,a11,a12,a21,a22);
      cout << t << " " << out[0] << " " << out[1] << endl;
      t+=dt;
   }while(t < tfin);
}


void one_step_runge_kutta(float * inp,float * out,const float tt,const float hh,
                          float * f, const float a11, const float a12,
                          const float a21, const float a22){
   float time, incr;
   int i,j;
   float k[numeq][4];
   for (i=0; i<numeq; i++)
      out[i]=inp[i]; 
   time=tt;
   for (j=0; j<4; j++){
      derivacion(out,f,time,a11,a12,a21,a22);
      for (i=0; i<numeq; i++) 
         k[i][j]=f[i];
      if (j<2)
         incr=hh/2;
      else 
         incr=hh;
      time=tt+incr;
      for (i=0; i<numeq; i++)
         out[i]=inp[i]+k[i][j]*incr;
   }
   for (i=0; i<numeq; i++)
      out[i]=inp[i]+hh/6*(k[i][0]+2*k[i][1]+2*k[i][2]+k[i][3]);
}


void derivacion(float * est,float * f,const float tt,
                const float a11, const float a12, const float a21, const float a22){
   f[0]=a11*est[0]-a12*est[0]*est[1];
   f[1]=a21*est[0]*est[1]-a22*est[1];
}
