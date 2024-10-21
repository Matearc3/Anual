#include <iostream>
#include<stdio.h>
using namespace std;

struct paciente{
    int idPac; 
    char nombre[25+1], apellido[25+1];
    int edad,dni,telefono;
};
struct medico
{
    int idMed;
    char nombre[25+1],apellido[25+1];
    int matricula, idEspecialidad,diasAtencion,horario,tiempoConsulta;
};

struct especialidades{
    int id;
    char descripcion[80+1];
};
struct turno
{
    int idMed,dia,mes,idPac;
    float hora;
    char estatus;
};
struct nodo{
    nodo *sgte;
    turno info;
};
int main(){
nodo *lista;

    return 0;
}