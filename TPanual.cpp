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
void cargaListaMed(FILE *Medicos,nodo2*&Lista);
void cargaSublistas(nodo2*&Lista);
void cargarTurnosAutomaticamente(FILE* Pacientes, FILE* Medicos, nodo2* &listaTurnos);
int menu();
void altaNuevoPaciente(FILE * &Pacientes);
void altaNuevoMedico(FILE * &Medicos, nodo2*&Lista);
void altaNuevoTurno(FILE* Pacientes, FILE* Medicos, nodo2* &listaTurnos);
void actualizacionTurnos(nodo2 *&lista, FILE* Medicos );
void atencionesEfectivas(nodo2 *lista,FILE* Medicos);
void turnosPendientes(nodo2* lista,FILE* Medicos);
void listarCancelaciones(nodo2 *listaTurnos, especialidad especialidades[], FILE* Medicos,FILE* Pacientes);

//MAIN
int main(){
    FILE *Pacientes;
    FILE *Medicos;

    especialidad especialidades[20];
    cargaEspecialidad(especialidades);

    nodo2 *Lista=NULL;
    cargaListaMed(Medicos,Lista);
    cargarTurnosAutomaticamente(Pacientes,Medicos,Lista);

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
            altaNuevoTurno(Pacientes, Medicos,Lista);
        }

        if (accion==3)
        {
            altaNuevoMedico(Medicos,Lista);
        }

        if (accion==4)
        {
            actualizacionTurnos(Lista,Medicos);
        }

        if (accion==5)
        {
            turnosPendientes(Lista,Medicos);
        }

        if (accion==6)
        {
            atencionesEfectivas(Lista,Medicos);
        }

        if (accion==7)
        {
            listarCancelaciones(Lista,especialidades,Medicos,Pacientes);
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


//CARGA LISTA
void cargaListaMed(FILE *Medicos,nodo2*&Lista)
{
    nodo2*aux;
    medico auxMed;
    Medicos=fopen("MEDICOS.BIN","rb");

    if (Medicos==NULL)
    {
        cout<<"Error al abrir el archivo para lectura.";
        return;
    }
    
    fseek(Medicos,0,SEEK_SET);
    while (fread(&auxMed,sizeof(medico),1,Medicos))
    {
        aux=Lista;
        nodo2* nuevo=new nodo2();
        nuevo->info.idMed=auxMed.idMed;
        nuevo->sgte=NULL;
        if (Lista==NULL)
        {
            Lista=nuevo;
        }
        else
        {
            while(aux->sgte!=NULL)
            {
                aux=aux->sgte;
            }
            aux->sgte=nuevo;
        }
    }
    fclose(Medicos);
}

void cargarTurnosAutomaticamente(FILE* Pacientes, FILE* Medicos, nodo2* &listaTurnos) 
{
    paciente p;
    medico m;
    int totalPacientes = 0, totalMedicos = 0;
    int numTurnos =12;


    Pacientes = fopen("PACIENTES.BIN", "rb");
    Medicos = fopen("MEDICOS.BIN", "rb");

    if (Medicos == NULL || Pacientes == NULL) 
    {
        cout << "No se pudieron abrir los archivos para lectura." << endl;
        return;
    }

    fseek(Pacientes, -sizeof(paciente), SEEK_END);
    fread(&p,sizeof(paciente),1,Pacientes);
    totalPacientes=p.idPac;

    fseek(Medicos, -sizeof(medico), SEEK_END);
    fread(&m,sizeof(medico),1,Medicos);
    totalMedicos=m.idMed;    

    
    for (int i = 0; i < numTurnos; i++) {
        nodoT* nuevoTurno = new nodoT();
        nuevoTurno->sgte = NULL;

      
        if (i % 3 == 0) {
            nuevoTurno->info.estatus = 'P';  
        } else if (i % 3 == 1) {
            nuevoTurno->info.estatus = 'A';  
        } else {
            nuevoTurno->info.estatus = 'C'; 
        }

        
        int pacienteID = ( i % totalPacientes ) + 1;
        fseek(Pacientes,  sizeof(paciente)* ((pacienteID)-1) , SEEK_SET);
        fread(&p, sizeof(paciente), 1, Pacientes);
        nuevoTurno->info.idPac = p.idPac;

        
        int medicoID = ( i % totalMedicos ) + 1;
        fseek(Medicos, sizeof(medico)* ((medicoID)-1), SEEK_SET);
        fread(&m, sizeof(medico), 1, Medicos);

        int diaLaboral = 1;
        for (int j = 0; j < 7; j++) {
            if (m.diasAtencion[j] != 0) {
                diaLaboral = m.diasAtencion[j];
                j=7;
            }
        }
        nuevoTurno->info.dia = diaLaboral;
        nuevoTurno->info.mes = 1; 


        nuevoTurno->info.hora[0] = m.horainicio; 
        nuevoTurno->info.hora[1] = 0; 

       
        nodo2* auxMedico = listaTurnos;
        while (auxMedico != NULL && auxMedico->info.idMed != m.idMed) {
            auxMedico = auxMedico->sgte;
        }

        if (auxMedico != NULL) {
            nodoT* auxTurno = auxMedico->info.sublista;
            while (auxTurno != NULL && auxTurno->sgte != NULL) {
                auxTurno = auxTurno->sgte;
            }

            if (auxTurno == NULL) {
                auxMedico->info.sublista = nuevoTurno;
            } else {
                auxTurno->sgte = nuevoTurno;
            }
        }
    }

    fclose(Pacientes);
    fclose(Medicos);
}


//MENU
int menu(){
    int accion;
    cout<< "Por favor indique un numero del 1 al 8 indicando la que accion desea realizar: "<<endl;
    cout<<"1. Alta de nuevo paciente."<<endl;
    cout<<"2. Alta de nuevo turno."<<endl;
    cout<<"3. Alta de nuevo medico."<<endl;
    cout<<"4. Actualizacion de estado de turno."<<endl;
    cout<<"5. Listado de turnos pendientes para cierto medico en cierto mes."<<endl;
    cout<<"6. Listado de cantidad de atenciones efectivas para un medico en cierto mes."<<endl;
    cout<<"7. Listado de cancelaciones en cierto mes."<<endl;
    cout<<"8. Cerrar menu."<<endl;
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
        int ingresar=0;
        cout<<"Desea ingresar un paciente nuevo al sistema? Ingrese 0 para no o cualquier otro digito para si."<<endl;
        cin>>ingresar;
        if (ingresar==0)
        {   
            fclose(Pacientes);
            return;
        }
        
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
        cout<<"El paciente a sido agregado con exito."<<endl;
        cout<<"El id del paciente es de: "<<nuevo.idPac<<endl;
    }
}

void altaNuevoMedico(FILE * &Medicos,nodo2*&Lista){
    int diasdeconsultas;
    int i;
    nodo2* aux=Lista;
    nodo2* nuevoM=new nodo2();

    medico nuevo;
    Medicos=fopen("MEDICOS.BIN","rb+");

    if (Medicos==NULL)
    {
    cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    else
    {
        int ingresar=0;
        cout<<"Desea ingresar un Medico nuevo al sistema? Ingrese 0 para no o cualquier otro digito para si."<<endl;
        cin>>ingresar;
        if (ingresar==0)
        {   
            fclose(Medicos);
            return;
        } 

        fseek(Medicos,-sizeof(medico),SEEK_END);
        
        fread(&nuevo,sizeof(medico),1,Medicos);
        nuevo.idMed++;
        
        fseek(Medicos,0,SEEK_END);

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
        
        while (nuevo.tiempoConsulta!=15 && nuevo.tiempoConsulta!=30&&nuevo.tiempoConsulta!=45&&nuevo.tiempoConsulta!=60)
        {
            cout<<"Tiempo de consulta invalido, por favor ingrese una de las siguientes opciones: 15, 30, 45 o 60 minutos.";
        }
        
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
        
        fwrite(&nuevo,sizeof(medico),1,Medicos);
        fclose(Medicos);
        
        nuevoM->info.idMed=nuevo.idMed;
        nuevoM->sgte=NULL;
        nuevoM->info.sublista=NULL;

        while (aux->sgte!=NULL)
        {   
            
            aux=aux->sgte;
        }
        aux->sgte=nuevoM;
        cout<<"El medico fue agregado con exito."<<endl;
        cout<<"El id del medico es: "<<nuevo.idMed<<endl;
    }       
     
}

void altaNuevoTurno(FILE* Pacientes, FILE* Medicos, nodo2* &listaTurnos)
{
    nodoT* nuevoTurno = new nodoT();
    nuevoTurno->sgte=NULL; 

	nodo2* aux= listaTurnos;
    paciente p;
    medico m;
    int horaInicio[2]={};
    int horaFin[2]={};
    int idMed;
    int horaInicioAux[2]={};
    int horaFinAux[2]={};

    int ultimoID;
    
    Pacientes=fopen("PACIENTES.BIN","rb");
    Medicos=fopen("MEDICOS.BIN","rb");

    if (Medicos==NULL ||Pacientes==NULL)
    {
        cout << "No se pudieron abrir los archivos para lectura." << endl;
        return ;
    }

    fseek(Pacientes,-sizeof(paciente),SEEK_END);
    fread(&p,sizeof(paciente),1,Pacientes);
    fclose(Pacientes);

    int ingresar=0;
    cout<<"Desea ingresar un Turno nuevo al sistema? Ingrese 0 para no o cualquier otro digito para si."<<endl;
    cin>>ingresar;
    if (ingresar==0)
    {   
        fclose(Medicos);
        return;
    } 
    ultimoID=p.idPac;
    cout<<"Ingrese id Paciente: "<<endl;
    cin>>nuevoTurno->info.idPac;

    while(nuevoTurno->info.idPac>ultimoID || nuevoTurno->info.idPac<=0)
    {
        cout<<"El id es invalido, ingrese otro"<<endl;
        cin>>nuevoTurno->info.idPac;
    }

    fseek(Medicos,-sizeof(medico),SEEK_END);
    fread(&m,sizeof(medico),1,Medicos);
    

    ultimoID=m.idMed;
    
    cout<<"Ingrese id Medico: "<<endl;
    cin>>idMed;

    while(idMed>ultimoID||idMed<=0)
    {
        cout<<"El id es invalido, ingrese otro"<<endl;
        cin>>idMed;
    }
    
    fseek(Medicos,sizeof(medico)*(idMed-1),SEEK_SET);
    fread(&m,sizeof(medico),1,Medicos);
    fclose(Medicos);

    if (aux==NULL)
    {
        cout<<"ERROR. No hay medicos cargados en el sistema.";
        return;
    }

    while(aux->info.idMed != idMed)
    {
        aux=aux->sgte;
	}

    nodoT *sublistAux=aux->info.sublista;
    if (sublistAux!=NULL)
    {
        while(sublistAux->sgte!=NULL && sublistAux->sgte->info.idPac!=nuevoTurno->info.idPac)
        {
            sublistAux=sublistAux->sgte;
        }

        if(aux->info.sublista->info.idPac==nuevoTurno->info.idPac)
        {
            cout<<"Ya hay turno de este paciente con este medico"<<endl;
            return;
        }
    }

    else
    {
        sublistAux=aux->info.sublista;        
        
        cout<<"Ingrese hora (despreciando los minutos):"<<endl;
        cin>>nuevoTurno->info.hora[1];
        while (nuevoTurno->info.hora[0]<0 || nuevoTurno->info.hora[0]>23)
        {
            cout<<"Hora invalida. Ingrese una hora valida (despreciando los minutos), entre 00 y 23: "<<endl;
            cin>>nuevoTurno->info.hora[0];
        }

        cout<<"Ingrese los minutos de la hora:"<<endl;
        cin>>nuevoTurno->info.hora[1];
        while (nuevoTurno->info.hora[1]<0 || nuevoTurno->info.hora[1]>59)
        {
            cout<<"Minutos invalidos. Ingrese minutos validos, entre 00 y 59: "<<endl;
            cin>>nuevoTurno->info.hora[1];
        }

        cout<<"Ingrese dia: "<<endl;
        cin>>nuevoTurno->info.dia;
        
        while (nuevoTurno->info.dia<1 || nuevoTurno->info.dia>30)
        {
            cout<<"dia invalico, ingrese un dia de 1 al 30: "<<endl;
            cin>>nuevoTurno->info.dia;
        }
        int diaAux=nuevoTurno->info.dia;
        bool diaLaboral= false;

        while (diaAux>7)
        {
            diaAux-=7;
        }
        int cantdias=0;

        for (int i = 0; i < 7; i++)
        {
            if (m.diasAtencion[i]!=0)
            {
                cantdias++;
            }
        }
        
        for (int i = 0; i < cantdias; i++)
        {
            if(m.diasAtencion[i]==diaAux)
            {
                diaLaboral=true;
            }
        }
        
        if (diaLaboral==false)
        {
            cout<<"El medico no trabaja dicho dia."<<endl;
            return;
        }
        
        
        

        cout<<"Ingrese mes: "<<endl;
        cin>>nuevoTurno->info.mes;
        while (nuevoTurno->info.mes>12||nuevoTurno->info.mes<0)
        {
            cout<<"Mes invalido, Ingrese el mes como un numero del uno al 12: "<<endl;
            cin>>nuevoTurno->info.mes;
        }
        
        horaInicio[0]=nuevoTurno->info.hora[0];
        horaInicio[1]=nuevoTurno->info.hora[1];
        horaFin[0]=nuevoTurno->info.hora[0];
        horaFin[1]= nuevoTurno->info.hora[1]+m.tiempoConsulta;

        if (horaFin[1]>59)
        {
            horaFin[0]++;
            horaFin[1]%=60;
        }
        
        while(sublistAux!=NULL )
        {
            
            if (sublistAux->info.mes==nuevoTurno->info.mes && sublistAux->info.dia==nuevoTurno->info.dia && sublistAux->info.estatus =='P')
            {
                horaInicioAux[0]=sublistAux->info.hora[0];
                horaInicioAux[1]=sublistAux->info.hora[1];
                horaFinAux[0]=sublistAux->info.hora[0];
                horaFinAux[1]= sublistAux->info.hora[1]+m.tiempoConsulta;

                if (horaFinAux[1]>59)
                {
                    horaFinAux[0]++;
                    horaFinAux[1]%=60;
                }

                if (nuevoTurno->info.hora==horaInicioAux)
                {
                    cout<<"El medico ya tiene un turno en ese dia y hora"<<endl;
                }
                

                if ((horaInicio[0] < horaFinAux[0] || (horaInicio[0] == horaFinAux[0] && horaInicio[1] < horaFinAux[1])) && (horaFin[0] > horaInicioAux[0] || (horaFin[0] == horaInicioAux[0] && horaFin[1] > horaInicioAux[1])))
                {
                    cout << "El medico ya tiene un turno en esta franja horaria." << endl;
                    return;
                }
                
            }
            sublistAux=sublistAux->sgte;
        }
        sublistAux=aux->info.sublista;
        if (sublistAux==NULL)
        {
            nuevoTurno->info.estatus='P';
            nuevoTurno->info.idTurno=aux->info.sublista->info.idTurno+1;
            sublistAux=nuevoTurno;
            cout<<"Turno ingresado correctamente."<<endl;
            return;
        }
        
        while (sublistAux->sgte!=NULL)
        {
            sublistAux=sublistAux->sgte;
        }
        nuevoTurno->info.estatus='P';
        nuevoTurno->info.idTurno=aux->info.sublista->info.idTurno+1;
        sublistAux->sgte=nuevoTurno;
        cout<<"El turno fue agregado con exito."<<endl;
        cout<<"El id del turno es: "<<nuevoTurno->info.idTurno<<endl;
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
        int ingresar=0;
        cout<<"Desea actualizar el estado de un turno existente? Ingrese 0 para no o cualquier otro digito para si."<<endl;
        cin>>ingresar;
        if (ingresar==0)
        {   
            fclose(Medicos);
            return;
        } 

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
        
        if (aux==NULL)
        {
            cout<<"ERROR. No hay medicos cargados en el sistema.";
            return;
        }


        while (aux!=NULL && aux->info.idMed!=IDmedico)
        {   
            aux=aux->sgte;
        }

        if (aux->info.idMed==IDmedico)
        {   
            nodoT* subaux=aux->info.sublista;
            while (subaux!=NULL && subaux->info.idTurno!=IDturno)
            {   
                subaux=subaux->sgte;
            }

            if (subaux->info.idTurno==IDturno)
            {
                cout<<endl<<"ingrese el estatus a colocar: ";
                cin>>aux->info.sublista->info.estatus;

                while (subaux->info.estatus!='P'&& subaux->info.estatus!='A' && subaux->info.estatus!='C' && subaux->info.estatus!='X')
                {
                    cout<<endl<<"Estatus invalido, por favor ingrese un estatus valido: ";
                    cin>>subaux->info.estatus;
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
        fread(&tamano,sizeof(medico),1,Medicos);
        
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

        if (aux==NULL)
        {
            cout<<"ERROR. No hay medicos cargados en el sistema.";
            return;
        }


        while (aux!=NULL)
        {
            nodoT* auxSub=aux->info.sublista;
            contador=0;
            while (auxSub!=NULL)
            {
            
            if(mes==auxSub->info.mes && auxSub->info.estatus=='A')
            {    
                contador++;
            }  

            auxSub=auxSub->sgte;
            }
            
            cout<<"El Medico " <<meds[aux->info.idMed-1].nombre<<" tuvo "<< contador <<" atenciones efectivas en el mes "<<mes<<"."<<endl;
            
            aux=aux->sgte;
        }
    }
}

void turnosPendientes(nodo2* lista,FILE* Medicos){
    int idMed,mes;
    medico auxMed;
    nodo2* aux=lista;

    Medicos=fopen("MEDICOS.BIN","rb");
    if (Medicos==NULL)
    {
        cout << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    fseek(Medicos, -sizeof(medico),SEEK_END);
    fread(&auxMed,sizeof(medico),1,Medicos);
    

    cout<<"Ingrese id Medico: "<<endl;
    cin>>idMed;

    while(idMed>auxMed.idMed||idMed<=0)
    {
        cout<<"El id es invalido, ingrese otro"<<endl;
        cin>>idMed;
    }
    fseek(Medicos, sizeof(medico)*idMed,SEEK_SET);
    fread(&auxMed,sizeof(medico),1,Medicos);

    fclose(Medicos);

    if (aux==NULL)
    {
        cout<<"ERROR. No hay medicos cargados en el sistema.";
        return;
    }


    cout<<"Ingrese mes: "<<endl;
    cin>>mes;
    while (mes>12||mes<1)
    {
        cout<<"Mes invalido, Ingrese el mes como un numero del uno al 12: "<<endl;
        cin>>mes;
    }


	while(aux!=NULL && aux->info.idMed!=idMed)
    {
		aux=aux->sgte;
	}
	if (aux==NULL)
    {
        cout<<"No se encontro el medico."<<endl;
        return;
    }
    bool hayTurno=false;
    int contador=1;
    cout<<"Turnos pendientes del medico "<< auxMed.nombre<<" "<<auxMed.apellido<<" en el mes "<<mes<<": "<<endl;
    nodoT* auxSub=aux->info.sublista;
    while (auxSub!=NULL)
    {   
        if (mes==auxSub->info.mes && auxSub->info.estatus=='P')
        {
            hayTurno=true;
            cout<<endl;
            cout<<"Turno numero: "<<contador<<endl;
            cout<<"ID del turno: "<<auxSub->info.idTurno<<endl;
            cout<<"ID del paciente: "<<auxSub->info.idPac<<endl;
            cout<<"Dia del turno: "<<auxSub->info.dia<<endl;
            cout<<"Horario: "<<auxSub->info.hora[0]<<":"<<auxSub->info.hora[1]<<endl;
            contador++;
            
        }
        
        auxSub=auxSub->sgte;
    }
    if (hayTurno==false)
    {
        cout<<"No hay turnos pendientes para este medico en este mes"<<endl;
    }
    

}

void listarCancelaciones(nodo2 *listaTurnos, especialidad especialidades[], FILE* Medicos,FILE* Pacientes) 
{
    int mes=0;
    Medicos = fopen("MEDICOS.BIN", "rb");
    Pacientes = fopen("PACIENTES.BIN", "rb");

    if (Medicos == NULL || Pacientes == NULL) {
        cout << "Error al abrir los archivos" << endl;
        return;
    }

    nodo2 *auxLista = listaTurnos;
    medico med;
    paciente pac;

    cout<<"Ingrese mes: "<<endl;
    cin>>mes;
    while (mes>12||mes<1)
    {
        cout<<"Mes invalido, Ingrese el mes como un numero del uno al 12: "<<endl;
        cin>>mes;
    }

    if (auxLista==NULL)
    {
        cout<<"ERROR. No hay medicos cargados en el sistema.";
        fclose(Medicos);
        fclose(Pacientes);
        return;
    }
    
    cout << "\n--- CANCELACIONES DEL MES " << mes << " ---\n" << endl;
    cout << "PACIENTE\t\tMEDICO\t\tESPECIALIDAD\tDIA" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    

    while (auxLista != NULL) {
       
        nodoT* auxTurnos = auxLista->info.sublista;

        
        fseek(Medicos, sizeof(medico)*(auxLista->info.idMed),SEEK_SET);
        fread(&med, sizeof(medico), 1, Medicos);
        
        
        while (auxTurnos != NULL) {
            
            if (auxTurnos->info.mes == mes && auxTurnos->info.estatus == 'C') {
                
                fseek(Pacientes, (auxTurnos->info.idPac - 1) * sizeof(paciente), SEEK_SET);
                fread(&pac, sizeof(paciente), 1, Pacientes);
                
                
                cout << pac.nombre << " " << pac.apellido << "\t";
                cout << med.nombre << " " << med.apellido << "\t";
                cout << especialidades[med.idEspecialidad - 1].descripcion << "\t";
                cout << "Dia " << auxTurnos->info.dia << endl;
            }
            
            auxTurnos = auxTurnos->sgte;
        }
        
        auxLista = auxLista->sgte;
    }

    fclose(Medicos);
    fclose(Pacientes);
}
