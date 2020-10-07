// Metodo de Incremento Fijo de Tiempo - Especificacion

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define graficar 1

bool servidor;
double acum_cola, inicio_ocio, ocio, tLlegada, tServicio;
long atendidos, encola, infinito, numSimul, reloj, tiempo_llegada, tiempo_salida, total_a_atender, tultsuc;

float genera(float tiempo);
void iniciarValores();
