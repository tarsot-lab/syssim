// Modelo de Simulacion Dinamico y Discreto - Especificación

#include <iostream>
#include <list>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

#define suceso_llegada 0
#define suceso_salida 1
#define suceso_finsimulacion 3
#define suceso_monitor 4
#define graficar 1

typedef struct {
  int suceso;
  float tiempo;
  int retraso;
} suc;

bool parar;
float acum_cola, acum_ocio, acum_retraso, acum_sistema, reloj, tlleg, tparada, tserv, valor;
float acum_sincola, init_sincola, tultsuc_cola, tultsuc_ocio, tultsuc_sistema;
int atendidos, encola, ensistema, libres, nada = 0, numSimul, m, maximacola;
list<float> cola;
list<suc> lsuc;
suc nodo;

float totalMedidasMed[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int totalMaxColaMed = 0;
vector<vector<float>> totalMedidasDesv;
vector<int> totalMaxColaDesv;
bool compare(const suc &s1, const suc &s2);
float generador_exponencial(float media);
float genera(float media);
void inicializacion();
void insertar_lsuc(suc n);
void temporizacion();
void llegada();
void salida();
void fin(int ciclo);
void monitor();
void suceso(int ciclo);
