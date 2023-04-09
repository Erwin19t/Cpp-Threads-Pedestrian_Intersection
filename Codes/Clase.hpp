#ifndef _CLASE_HPP_
#define _CLASE_HPP_

#include <iostream>
#include <string>

using namespace std;

class Traffic_Light;
class Pedestrian_Light;

class Traffic_Light{
    public:
        //Atributos del Semaforo Vehicular
        string Name;    //Nombre del semaforo
        int Id;         //identificador de semaforo
        int N_Vehicles; //Cantidad de Vehiculos formados
        bool State;     //Estado del semaforo (Verde/Rojo)
        //Constructor & Destructor
        Traffic_Light(string _Name, int _Id, int _N_Vehicles, bool _State);
        ~Traffic_Light();
        //Metodos Get
        string Get_Name();
        int Get_Id();
        int Get_N_Vehicles();
        bool Get_State();
        //Metodos Set
        void Set_N_Vehicles();
        void Set_State(bool _State);
        //Metodos del Semaforo
        void Add_Vehicle();
};

class Pedestrian_Light{
    public:
        //Atributos del Semaforo Peatonal
        int Id;             //identificador de semaforo
        int N_Pedestrian;   //Cantidad de Personas Esperando
        bool State;         //Estado del semaforo (Verde/Rojo)
        //Constructor & Destructor
        Pedestrian_Light(int _Id, int _N_Pedestrian, bool _State);
        ~Pedestrian_Light();
        //Metodos Get
        int Get_Id();
        int Get_N_Pedestrian();
        bool Get_State();
        //Metodos Set
        void Set_N_Pedestrian();
        void Set_State(bool _State);
        //Metodos del Semaforo
        void Add_Pedestrian(int _N_Pedestrian);
};
#endif //_CLASS_HPP_