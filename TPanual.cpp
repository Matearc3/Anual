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
struct especialidad{
    int id;
    char descripcion[20+1];
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

int menu(int accion);
void altaNuevoPaciente(FILE * &Pacientes);

int main(){
FILE *Pacientes;
FILE *Medicos;
especialidad especialidades[20];
nodo *lista=NULL;
int accion=0;

while (accion!=8){
accion = menu(accion);
if (accion=1)
{
altaNuevoPaciente(Pacientes);
}

}

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
int menu(int accion){
cout<< "Por favor indique un numero del 1 al 8 indicando la que accion desea realizar: "<<endl;
cout<<"1. Alta de nuevo paciente"<<endl;
cout<<"2. Alta de nuevo turno"<<endl;
cout<<"3. Alta de nuevo medico"<<endl;
cout<<"4. Actualizacion de estado de turno"<<endl;
cout<<"5. Listado de turnos pendientes"<<endl;
cout<<"6. Listado de cantidad de atenciones efectivas"<<endl;
cout<<"7. Listado de cancelaciones"<<endl;
cout<<"8. Cerrar menu"<<endl;
cin>>accion;
if (accion>8||accion<1){
    cout<<"numero invalido, por favor ingrese un numero valido: ";}
    return accion;
}
void cargaEspecialidad(especialidad especialidades[]){
int i;
for (i=0; i < 20; i++)
{
    especialidades[i].id=i+1;
}
especialidades[0].descripcion[]= "Cardiologia";
especialidades[1].descripcion[]="Dermatologia";
especialidades[2].descripcion[]="Ginecologia";
especialidades[3].descripcion[]="Pediatria";
especialidades[4].descripcion[]="Neurologia";
especialidades[5].descripcion[]="Oftalmologia";
especialidades[6].descripcion[]="Oncologia";
especialidades[7].descripcion[]="Ortopedia";
especialidades[8].descripcion[]="Endocrinologia";
especialidades[9].descripcion[]="Neumologia";
especialidades[10].descripcion[]="Psiquiatria";
especialidades[11].descripcion[]="Otorrinolaringologia";
especialidades[12].descripcion[]="Gastroenterologia";
especialidades[13].descripcion[]="Urologia";
especialidades[14].descripcion[]="Nefrologia";
especialidades[15].descripcion[]="Reumatologia";
especialidades[16].descripcion[]="Cirugia General";
especialidades[17].descripcion[]="Medicina Interna";
especialidades[18].descripcion[]= "Traumatologia";
especialidades[19].descripcion[]= "Infectologia";
}