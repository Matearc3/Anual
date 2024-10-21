#include <iostream>
#include<stdio.h>
using namespace std;

struct paciente{
    int id; 
    char nombre[25+1], apellido[25+1];
    int edad,dni,telefono;
};
struct medico
{
    int id;
    char nombre[25+1],apellido[25+1];
    int matricula, idEspecialidad,diasAtencion,horario,tiempoConsulta;
};

struct especialidades{
    int id;
    char descripcion[80+1];
};
