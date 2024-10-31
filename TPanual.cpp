#include <iostream>
#include<stdio.h>
#include<cstring>
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
    int matricula, idEspecialidad,diasAtencion[7],horainicio,horafin,tiempoConsulta;
};
struct especialidad{
    int id;
    char descripcion[20+1];
};
struct subturno
{
    int idTurno,dia,mes,idPac,hora[2];
    char estatus;
};
struct nodo1
{
    nodo1 *sgte;
   subturno info;
};
struct turno
{nodo1 *infoSubTurno;
int idMed;
};

struct nodo2{
    nodo2 *sgte;
    turno info;
};

void cargaEspecialidad(especialidad especialidades[]);
int menu();
void altaNuevoPaciente(FILE * &Pacientes);
void altaNuevoMedico(FILE * &Medicos);

int main(){
FILE *Pacientes;
FILE *Medicos;
especialidad especialidades[20];
cargaEspecialidad(especialidades);
nodo2 *Lista=NULL;//lista//

int accion=0;

while (accion!=8){
    accion = menu();
    if (accion==1)
    {
        altaNuevoPaciente(Pacientes);
    }

    if(accion==2)
    {

    }

    if (accion==3)
    {
        altaNuevoMedico(Medicos);
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
    else
    {
        fseek(Pacientes,-sizeof(paciente),SEEK_END);
        fread(&nuevo,sizeof (paciente),1,Pacientes);
        nuevo.idPac++;
        cout<<endl<<"Escriba el nombre del paciente: ";cin>>nuevo.nombre;
        cout<<endl<<"Escriba el apellido del paciente: ";cin>>nuevo.apellido;
        cout<<endl<<"Escriba el dni del paciente: ";cin>>nuevo.dni;
        cout<<endl<<"Escriba la edad del paciente: ";cin>>nuevo.edad;
        cout<<endl<<"Escriba el numero de telefono del paciente: ";cin>> nuevo.telefono;cout<<endl;
        fseek(Pacientes,0,SEEK_END);
        fwrite(&nuevo,sizeof(paciente),1,Pacientes);
        fclose(Pacientes);
    }
}

int menu(){
    int accion;
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
    if (accion>8||accion<1)
    {
        cout<<"numero invalido, por favor ingrese un numero valido: ";
    }

    return accion;
}

void cargaEspecialidad(especialidad especialidades[]){
    int i;
    for (i=0; i < 20; i++)
    {
        especialidades[i].id=i+1;
    }

        strcpy(especialidades[0].descripcion, "Cardiologia");
        strcpy(especialidades[1].descripcion, "Dermatologia");
        strcpy(especialidades[2].descripcion, "Ginecologia");
        strcpy(especialidades[3].descripcion, "Pediatria");
        strcpy(especialidades[4].descripcion, "Neurologia");
        strcpy(especialidades[5].descripcion, "Oftalmologia");
        strcpy(especialidades[6].descripcion, "Oncologia");
        strcpy(especialidades[7].descripcion, "Ortopedia");
        strcpy(especialidades[8].descripcion, "Endocrinologia");
        strcpy(especialidades[9].descripcion, "Neumologia");
        strcpy(especialidades[10].descripcion, "Psiquiatria");
        strcpy(especialidades[11].descripcion, "Otorrinolaringologia");
        strcpy(especialidades[12].descripcion, "Gastroenterologia");
        strcpy(especialidades[13].descripcion, "Urologia");
        strcpy(especialidades[14].descripcion, "Nefrologia");
        strcpy(especialidades[15].descripcion, "Reumatologia");
        strcpy(especialidades[16].descripcion, "Cirugia General");
        strcpy(especialidades[17].descripcion, "Medicina Interna");
        strcpy(especialidades[18].descripcion, "Traumatologia");
        strcpy(especialidades[19].descripcion, "Infectologia");
}

void altaNuevoMedico(FILE * &Medicos){
    int diasdeconsultas;
    int i;
    medico nuevo;
    Medicos=fopen("MEDICOS.BIN","rb+");
    if (Medicos==NULL)
    {
    cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    else{
        fseek(Medicos,-sizeof(medico),SEEK_END);
        fread(&nuevo,sizeof(medico),1,Medicos);
        nuevo.idMed++;
        for (int i = 0; i < 7; i++) {
            nuevo.diasAtencion[i] = 0;
        }
        cout<<"Ingrese nombre del medico: ";cin>>nuevo.nombre;
        cout<<endl<<"Ingrese apellido del medico: ";cin>>nuevo.apellido;
        cout<<endl<<"Ingrese numero de matricula del medico: ";cin>>nuevo.matricula;
        cout<<endl<<"ingrese id de especialidad: ";cin>>nuevo.idEspecialidad;

        while (nuevo.idEspecialidad>20||nuevo.idEspecialidad<1)
        {
            cout<<endl<<"Id de especialidad invalido, por favor ingrese un id valido, entre 1 y 20: ";
            cin>>nuevo.idEspecialidad;
        }
        cout<<endl<<"ingrese rango horario laboral: Inicia a las: ";cin>>nuevo.horainicio;

        while (nuevo.horainicio<0||nuevo.horainicio>23)
        {
            cout<<endl<<"Hora de inicio invalida, por favor ingrese una hora valida: ";cin>>nuevo.horainicio;
        }

        cout<<endl<<"Finaliza a las: ";cin>>nuevo.horafin;

        while (nuevo.horafin<0||nuevo.horafin>23||nuevo.horafin==nuevo.horainicio)
        {
            cout<<endl<<"Hora de finalizacion invalida, por favor ingrese una hora valida: ";cin>>nuevo.horafin;
        }
        
        cout<<endl<<"ingrese tiempo de consultas (en minutos): ";cin>>nuevo.tiempoConsulta;
        cout<<endl<<"ingrese la cantidad de dias que atiende el medico: ";cin>>diasdeconsultas;

        while (diasdeconsultas>7||diasdeconsultas<1)
        {
            cout<<endl<<"Cantidad de dias invalidos, por favor ingrese una cantidad valida: ";cin>>diasdeconsultas;
        }

        for ( i = 0; i < diasdeconsultas; i++)
        {
            cout<<endl<<"ingrese el dia numero "<<i+1<<" que trabaja en la semana(comenzando desde el domingo como 1 y el sabado como 7): ";
            cin>>nuevo.diasAtencion[i];

            while (nuevo.diasAtencion[i]>7||nuevo.diasAtencion[i]<1)
            {
                cout<<endl<<"Dia invalido por favor ingrese un dia entre 1 y 7 :";
                cin>>nuevo.diasAtencion[i];
            }
        }
        fseek(Medicos,0,SEEK_END);
        fwrite(&nuevo,sizeof(medico),1,Medicos);
        fclose(Medicos);
    }        
}

void altaNuevoTurno(FILE *&Pacientes, FILE* &Medicos,nodo2 &nodo){
    nodo2 *Aux;
    nodo2 *nuevo=new nodo2();

}

void actualizacionTurnos(nodo2 *lista, nodo2 &nodo,FILE *Pacientes, FILE* Medicos ){
    nodo2 *aux=lista;
    nodo2 actualizacion;
    int ultimoID=0;
    medico m;

    cout<<"ingrese el id de medico: ";
    cin>>actualizacion.info.idMed;
    Medicos=fopen("MEDICOS.BIN","rb");

    fseek(Medicos,-sizeof(medico),SEEK_END);
    fread(&m,sizeof(medico),1,Medicos);
    
    ultimoID=m.idMed;
    while(actualizacion.info.idMed>ultimoID||actualizacion.info.idMed<0){
        cout<<"El id es invalido, ingrese otro"<<endl;
        cin>>actualizacion.info.idMed;
    }

    while (actualizacion.info.idMed)
    {
            
    }
    
    while (lista !=)
    {
        /* code */
    }
    
    
}