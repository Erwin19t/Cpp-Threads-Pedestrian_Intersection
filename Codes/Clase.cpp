#include "Clase.hpp"
#include <unistd.h>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
Seccion de Semaforos de las Avenidas
*/
Traffic_Light::Traffic_Light(string _Name, int _Id, int _N_Vehicles, bool _State){
    this->Name       = _Name;
    this->Id         = _Id;
    this->N_Vehicles = _N_Vehicles;
    this->State      = _State;
}

Traffic_Light::~Traffic_Light(){}

string Traffic_Light::Get_Name(){
    return this->Name;
}

int Traffic_Light::Get_Id(){
    return this->Id;
}

int Traffic_Light::Get_N_Vehicles(){
    return this->N_Vehicles;
}

bool Traffic_Light::Get_State(){
    return this->State;
}

void Traffic_Light::Set_N_Vehicles(){
    this->N_Vehicles-=1;
}

void Traffic_Light::Set_State(bool _State){
    this->State = _State;
}

void Traffic_Light::Add_Vehicle(){
    this->N_Vehicles++;     //se agrega un auto
}

/*
Seccion de Semaforos Peatonales
*/
Pedestrian_Light::Pedestrian_Light(int _Id, int _N_Pedestrian, bool _State){
    this->Id           = _Id;
    this->N_Pedestrian = _N_Pedestrian;
    this->State        = _State;
}

Pedestrian_Light::~Pedestrian_Light(){}

int Pedestrian_Light::Get_Id(){
    return this->Id;
}

int Pedestrian_Light::Get_N_Pedestrian(){
    return this->N_Pedestrian;
}

bool Pedestrian_Light::Get_State(){
    return this->State;
}

void Pedestrian_Light::Set_N_Pedestrian(){
    this->N_Pedestrian = 0;
}

void Pedestrian_Light::Set_State(bool _State){
    this->State = _State;
}

void Pedestrian_Light::Add_Pedestrian(int _N_Pedestrian){
    this->N_Pedestrian = _N_Pedestrian;     //se agrega un auto
}