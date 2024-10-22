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
nodo *lista=NULL;

    return 0;
}

void altaNuevoPaciente(FILE * &Pacientes){
paciente nuevo;
Pacientes=fopen("PACIENTES.BIN","rb+");
if (Pacientes==NULL)
{
 cout << "No se pudo abrir el archivo para lectura." << endl;
}
else{
fseek(Pacientes,-sizeof(paciente),SEEK_END);
fread(&nuevo,sizeof (paciente),1,Pacientes);
nuevo.idPac++;
cout<<endl<<"Escriba el nombre del paciente: ";cin>>nuevo.nombre;
cout<<endl<<"Escriba el apellido del paciente: ";cin>>nuevo.apellido;
cout<<endl<<"Escriba el dni del paciente: ";cin>>nuevo.dni;
cout<<endl<<"Escriba la edad del paciente: ";cin>>nuevo.edad;
cout<<endl<<"Escriba el numero de telefono del paciente: ";cin>> nuevo.telefono;
fseek(Pacientes,0,SEEK_END);
fwrite(&nuevo,sizeof(paciente),1,Pacientes);
fclose(Pacientes);
}}