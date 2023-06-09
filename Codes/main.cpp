/*
Este programa hace tantas cosas que para este punto no se 
resumirlo en pocas lineas. Pasemos a la compilacion y ejecucion.

Compilacion: g++ main.cpp Clase.cpp -o Ejecutable -std=c++11 -lpthread
Ejecucion: ./Ejecutable
*/
#include "Clase.hpp"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <mutex>

using namespace std;

int Initial_Vehicles(int);
int Initial_Pedestrians(int);
void V_Lights_Control(Traffic_Light*, Traffic_Light*, Traffic_Light*, Traffic_Light*);
void P_Lights_Control(Traffic_Light*, Traffic_Light*, Traffic_Light*, Traffic_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*);
void Vehicles_Control(Traffic_Light*, Traffic_Light*, Traffic_Light*, Traffic_Light*, mutex*);
void Pedestrian_Control(Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, mutex*);
void AddVehicles(Traffic_Light*, Traffic_Light*, Traffic_Light*, Traffic_Light*, mutex*);
void AddPedestrians(Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, mutex*);
void Print_TF_Status(Traffic_Light*, Traffic_Light*, Traffic_Light*, Traffic_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, Pedestrian_Light*, mutex*);

int main(int argc, char* argv[]){
    mutex m1;
    //Creamos los Objetos Necesarios
    Traffic_Light Av1("Top_Bottom", 1, Initial_Vehicles(1), false);
    Traffic_Light Av2("Right_Left", 2, Initial_Vehicles(2), false);
    Traffic_Light Av3("Bottom_Top", 3, Initial_Vehicles(3), false);
    Traffic_Light Av4("Left_Right", 4, Initial_Vehicles(4), false);
    Pedestrian_Light P1(1, Initial_Pedestrians(1), false);
    Pedestrian_Light P2(2, Initial_Pedestrians(2), false);
    Pedestrian_Light P3(3, Initial_Pedestrians(3), false);
    Pedestrian_Light P4(4, Initial_Pedestrians(4), false);
    Pedestrian_Light P5(5, Initial_Pedestrians(5), false);
    Pedestrian_Light P6(6, Initial_Pedestrians(6), false);
    Pedestrian_Light P7(7, Initial_Pedestrians(7), false);
    Pedestrian_Light P8(8, Initial_Pedestrians(8), false);
    //Se crean los hilos necesarios
    thread V_L_Control(V_Lights_Control, &Av1, &Av2, &Av3, &Av4);
    thread P_L_Control(P_Lights_Control, &Av1, &Av2, &Av3, &Av4, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8);
    thread V_Control(Vehicles_Control, &Av1, &Av2, &Av3, &Av4, &m1);
    thread P_Control(Pedestrian_Control, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &m1);
    thread AddV(AddVehicles, &Av1, &Av2, &Av3, &Av4, &m1);
    thread AddP(AddPedestrians, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &m1);
    thread Print(Print_TF_Status, &Av1, &Av2, &Av3, &Av4, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &m1);

    V_L_Control.join();
    P_L_Control.join();
    V_Control.join();
    P_Control.join();
    AddV.join();
    AddP.join();
    Print.join();
    
    return 0;
}

int Initial_Vehicles(int Id){
    int NC = 0;
    srand(Id + (int)time(NULL));
    NC = 1 + rand()%5;  //Generamos una cantidad inicial de vehiculos entre 1 y 5.
    return NC;
}

int Initial_Pedestrians(int Id){
    int NP = 0;
    srand(Id + (int)time(NULL));
    NP = 1 + rand()%20;  //Generamos una cantidad inicial de peatones entre 1 y 20.
    return NP;
}

void V_Lights_Control(Traffic_Light* Av1, Traffic_Light* Av2, Traffic_Light* Av3, Traffic_Light* Av4){
    bool Av_State_01 = false;
    bool Av_State_02 = false;
    bool Av_State_03 = false;
    bool Av_State_04 = false;
    while(1){
        //Creamos una secuencia que seguiran los semaforos
        //Los semaforos va a ir cambiando de color en sentido horario
        Av1 -> Set_State(Av_State_01 = true);
        Av2 -> Set_State(Av_State_02 = false);
        Av3 -> Set_State(Av_State_03 = false);
        Av4 -> Set_State(Av_State_04 = false);
        sleep(5);
        Av1 -> Set_State(Av_State_01 = false);
        Av2 -> Set_State(Av_State_02 = true);
        Av3 -> Set_State(Av_State_03 = false);
        Av4 -> Set_State(Av_State_04 = false);
        sleep(5);
        Av1 -> Set_State(Av_State_01 = false);
        Av2 -> Set_State(Av_State_02 = false);
        Av3 -> Set_State(Av_State_03 = true);
        Av4 -> Set_State(Av_State_04 = false);
        sleep(5);
        Av1 -> Set_State(Av_State_01 = false);
        Av2 -> Set_State(Av_State_02 = false);
        Av3 -> Set_State(Av_State_03 = false);
        Av4 -> Set_State(Av_State_04 = true);
        sleep(5);
    }
}

void P_Lights_Control(Traffic_Light* Av1, Traffic_Light* Av2, Traffic_Light* Av3, Traffic_Light* Av4, Pedestrian_Light* P1, Pedestrian_Light* P2, Pedestrian_Light* P3, Pedestrian_Light* P4, Pedestrian_Light* P5, Pedestrian_Light* P6, Pedestrian_Light* P7, Pedestrian_Light* P8){
    bool P_State_01 = false;
    bool P_State_02 = false;
    bool P_State_03 = false;
    bool P_State_04 = false;
    bool P_State_05 = false;
    bool P_State_06 = false;
    bool P_State_07 = false;
    bool P_State_08 = false;
    while(1){
        if(((Av1 -> Get_State()) == true) || ((Av3 -> Get_State()) == true)){
            P1 -> Set_State(P_State_01 = false);
            P2 -> Set_State(P_State_02 = true);
            P3 -> Set_State(P_State_03 = true);
            P4 -> Set_State(P_State_04 = false);
            P5 -> Set_State(P_State_05 = false);
            P6 -> Set_State(P_State_06 = true);
            P7 -> Set_State(P_State_07 = true);
            P8 -> Set_State(P_State_08 = false);
        }
        if(((Av2 -> Get_State()) == true) || ((Av4 -> Get_State()) == true)){
            P1 -> Set_State(P_State_01 = true);
            P2 -> Set_State(P_State_02 = false);
            P3 -> Set_State(P_State_03 = false);
            P4 -> Set_State(P_State_04 = true);
            P5 -> Set_State(P_State_05 = true);
            P6 -> Set_State(P_State_06 = false);
            P7 -> Set_State(P_State_07 = false);
            P8 -> Set_State(P_State_08 = true);
        }
    }
}

void Vehicles_Control(Traffic_Light* Av1, Traffic_Light* Av2, Traffic_Light* Av3, Traffic_Light* Av4, mutex* m){
    while(1){
        sleep(1);
        if(Av1 -> Get_State()){
            if((Av1 -> Get_N_Vehicles()) >= 1){
                m->lock();
                Av1 -> Set_N_Vehicles();
                m->unlock();
            }
        }
        if(Av2 -> Get_State()){
            if((Av2 -> Get_N_Vehicles()) >= 1){
                m->lock();
                Av2 -> Set_N_Vehicles();
                m->unlock();
            }
        }
        if(Av3 -> Get_State()){
            if((Av3 -> Get_N_Vehicles()) >= 1){
                m->lock();
                Av3 -> Set_N_Vehicles();
                m->unlock();
            }
        }
        if(Av4 -> Get_State()){
            if((Av4 -> Get_N_Vehicles()) >= 1){
                m->lock();
                Av4 -> Set_N_Vehicles();
                m->unlock();
            }
        }
    }
}

void Pedestrian_Control(Pedestrian_Light* P1, Pedestrian_Light* P2, Pedestrian_Light* P3, Pedestrian_Light* P4, Pedestrian_Light* P5, Pedestrian_Light* P6, Pedestrian_Light* P7, Pedestrian_Light* P8, mutex* m){
    while(1){
        if(P1 -> Get_State()){
            P1 -> Set_N_Pedestrian();
        }
        if(P2 -> Get_State()){
            P2 -> Set_N_Pedestrian();
        }
        if(P3 -> Get_State()){
            P3 -> Set_N_Pedestrian();
        }
        if(P4 -> Get_State()){
            P4 -> Set_N_Pedestrian();
        }
        if(P5 -> Get_State()){
            P5 -> Set_N_Pedestrian();
        }
        if(P6 -> Get_State()){
            P6 -> Set_N_Pedestrian();
        }
        if(P7 -> Get_State()){
            P7 -> Set_N_Pedestrian();
        }
        if(P8 -> Get_State()){
            P8 -> Set_N_Pedestrian();
        }
    }
}

void AddVehicles(Traffic_Light* Av1, Traffic_Light* Av2, Traffic_Light* Av3, Traffic_Light* Av4, mutex* m){
    while(1){
        sleep(4);   //Se agrega un vehiculo a cada carril cada 4 segundos.
        m->lock();
        Av1 -> Add_Vehicle();
        Av2 -> Add_Vehicle();
        Av3 -> Add_Vehicle();
        Av4 -> Add_Vehicle();
        m->unlock();
    }
}

void AddPedestrians(Pedestrian_Light* P1, Pedestrian_Light* P2, Pedestrian_Light* P3, Pedestrian_Light* P4, Pedestrian_Light* P5, Pedestrian_Light* P6, Pedestrian_Light* P7, Pedestrian_Light* P8, mutex* m){
    int N_Pedestrian = 0;
    int P_Light      = 0;
    while(1){
        cin.get();
        srand(time(NULL));
        N_Pedestrian = 1 + rand()%20;  //Generamos una cantidad de peatones entre 1 y 20.
        srand(time(NULL));
        P_Light = 1 + rand()%8;  //Generamos un numero entre 1 y 8 donde se asignaran los peatones.
        if(P_Light == (P1 -> Get_Id())){
            P1 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P2 -> Get_Id())){
            P2 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P3 -> Get_Id())){
            P3 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P4 -> Get_Id())){
            P4 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P5 -> Get_Id())){
            P5 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P6 -> Get_Id())){
            P6 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P7 -> Get_Id())){
            P7 -> Add_Pedestrian(N_Pedestrian);
        }
        if(P_Light == (P8 -> Get_Id())){
            P8 -> Add_Pedestrian(N_Pedestrian);
        }
    }
}

void Print_TF_Status(Traffic_Light* Av1, Traffic_Light* Av2, Traffic_Light* Av3, Traffic_Light* Av4, Pedestrian_Light* P1, Pedestrian_Light* P2, Pedestrian_Light* P3, Pedestrian_Light* P4, Pedestrian_Light* P5, Pedestrian_Light* P6, Pedestrian_Light* P7, Pedestrian_Light* P8, mutex* m){
    system("clear");
    while(1){
        //Estado del Semaforo 1
        cout<<"El semaforo '"<<Av1 -> Get_Name()<<"' con Id "<<Av1 -> Get_Id()<<endl;
        cout<<"Tiene "<<Av1 -> Get_N_Vehicles()<<" vehiculos en fila"<<endl;
        if(Av1 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo 2
        cout<<"El semaforo '"<<Av2 -> Get_Name()<<"' con Id "<<Av2 -> Get_Id()<<endl;
        cout<<"Tiene "<<Av2 -> Get_N_Vehicles()<<" vehiculos en fila"<<endl;
        if(Av2 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo 3
        cout<<"El semaforo '"<<Av3 -> Get_Name()<<"' con Id "<<Av3 -> Get_Id()<<endl;
        cout<<"Tiene "<<Av3 -> Get_N_Vehicles()<<" vehiculos en fila"<<endl;
        if(Av3 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo 4
        cout<<"El semaforo '"<<Av4 -> Get_Name()<<"' con Id "<<Av4 -> Get_Id()<<endl;
        cout<<"Tiene "<<Av4 -> Get_N_Vehicles()<<" vehiculos en fila"<<endl;
        if(Av4 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 1
        cout<<"El Semaforo Peatonal "<<P1 -> Get_Id()<<" tiene "<<P1 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P1 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 2
        cout<<"El Semaforo Peatonal "<<P2 -> Get_Id()<<" tiene "<<P2 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P2 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 3
        cout<<"El Semaforo Peatonal "<<P3 -> Get_Id()<<" tiene "<<P3 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P3 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 4
        cout<<"El Semaforo Peatonal "<<P4 -> Get_Id()<<" tiene "<<P4 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P4 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 5
        cout<<"El Semaforo Peatonal "<<P5 -> Get_Id()<<" tiene "<<P5 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P5 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 6
        cout<<"El Semaforo Peatonal "<<P6 -> Get_Id()<<" tiene "<<P6 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P6 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 7
        cout<<"El Semaforo Peatonal "<<P7 -> Get_Id()<<" tiene "<<P7 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P7 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }

        //Estado del Semaforo Peatonal 8
        cout<<"El Semaforo Peatonal "<<P8 -> Get_Id()<<" tiene "<<P8 -> Get_N_Pedestrian()<<" personas esperando."<<endl;
        if(P8 -> Get_State()){
            cout<<"Y esta en Verde."<<endl<<endl;
        }
        else{
            cout<<"Y esta en Rojo."<<endl<<endl;
        }
        sleep(1);
        system("clear");
    }
}
