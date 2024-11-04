#include <iostream>
#include<cstring>
using namespace std;

//ESTRUCTURAS
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
struct nodoT
{
    nodoT *sgte;
   subturno info;
};
struct turno
{nodoT *sublista;
int idMed;
};
struct nodo2{
    nodo2 *sgte;
    turno info;
};

//PROTOTIPOS
void cargaEspecialidad(especialidad especialidades[]);
int menu();
void altaNuevoPaciente(FILE * &Pacientes);
void altaNuevoMedico(FILE * &Medicos);
void actualizacionTurnos(nodo2 *&lista, FILE* Medicos );
void atencionesEfectivas(nodo2 *lista,FILE* Medicos);

//MAIN
int main(){
    FILE *Pacientes;
    FILE *Medicos;

    especialidad especialidades[20];
    cargaEspecialidad(especialidades);

    nodo2 *Lista=NULL;//lista//

    int accion=0;

    while (accion!=8)
    {
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

        if (accion==4)
        {
            actualizacionTurnos(Lista,Medicos);
        }

        if (accion==5)
        {
            
        }

        if (accion==6)
        {
            atencionesEfectivas(Lista,Medicos);
        }

        if (accion==7)
        {
            /* code */
        }   
    }
    return 0;
}

//CARGA VECTOR ESPECIALIDADES
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

//MENU
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

//ALTAS
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



//ACTUALIZACIONES
void actualizacionTurnos(nodo2 *&lista, FILE* Medicos ){
    nodo2 *aux=lista;
  
    int IDmedico=0;
    int IDturno=0;
    int ultimoID=0;
    medico m;
    Medicos=fopen("MEDICOS.BIN","rb");
    
    if (Medicos==NULL)
    {
    cout << "No se pudo abrir el archivo para lectura." << endl;
    }

    else
    {
        cout<<"ingrese el ID de medico: ";
        cin>>IDmedico;

        fseek(Medicos,-sizeof(medico),SEEK_END);
        fread(&m,sizeof(medico),1,Medicos);
        fclose(Medicos);

        ultimoID=m.idMed;
        
        while (ultimoID<IDmedico && IDmedico<0)
        {
            cout<<endl<<"ID de medico invalido. Ingrese uno valido: ";
            cin>>IDmedico;   
        }

        cout<<endl<<"ingrese el ID de turno: ";
        cin>>IDturno;
        
        while (aux!=NULL && aux->info.idMed!=IDmedico)
        {   
            aux=aux->sgte;
        }

        if (aux->info.idMed==IDmedico)
        {
            while (aux->info.sublista!=NULL && aux->info.sublista->info.idTurno!=IDturno)
            {
                aux->info.sublista=aux->info.sublista->sgte;
            }

            if (aux->info.sublista->info.idTurno==IDturno)
            {
                cout<<endl<<"ingrese el estatus a colocar: ";
                cin>>aux->info.sublista->info.estatus;

                while (aux->info.sublista->info.estatus!='P'&& aux->info.sublista->info.estatus!='A' && aux->info.sublista->info.estatus!='C' && aux->info.sublista->info.estatus!='X')
                {
                    cout<<endl<<"Estatus invalido, por favor ingrese un estatus valido: ";
                    cin>>aux->info.sublista->info.estatus;
                }
                    
            }

            else
            {
                cout<<endl<< "No se encontro el turno.";
                return;    
            }

        }
        else
        {
            cout<<endl<< "No se encontro el turno.";
            return;
        }  
    } 
}

//LISTADOS
void atencionesEfectivas(nodo2 *lista,FILE* Medicos){
    nodo2* aux=lista;
    Medicos=fopen("MEDICOS.BIN","rb");
    int mes;
    int contador=0;
    medico tamano;
    
    if (Medicos==NULL)
    {
    cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    else
    {
        fseek(Medicos,-sizeof(medico),SEEK_END);
        fread(&tamano,sizeof(medico),0,Medicos);
        
        medico meds[tamano.idMed];
        fseek(Medicos,0,SEEK_SET);
        
        for (int i = 0; i < tamano.idMed; i++)
        {
            fread(&meds[i],sizeof(medico),1,Medicos);
            
        }

        fclose(Medicos);
        
        cout<<"Ingrese de que mes desea reportar la cantidad de atenciones efectivas: ";
        cin>>mes;
        
        while (mes>12||mes<1)
        {
            cout<<"Mes invalido, ingrese un mes valido: ";
            cin>>mes;
        }

        while (aux!=NULL)
        {
            contador=0;
            while (aux->info.sublista!=NULL)
            {
            
            if(mes==aux->info.sublista->info.mes && aux->info.sublista->info.estatus=='A')
            {    
                contador++;
            }  

            aux->info.sublista=aux->info.sublista->sgte;
            }
            
            cout<<"El doctor " <<meds[aux->info.idMed-1].nombre<<" tuvo "<< contador <<" atenciones efectivas en el mes "<<mes<<".";
            
            aux=aux->sgte;
        }
    }
}

