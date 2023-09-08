// 3_GameRGV.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>

#define MAXNAMESIZE 18 

enum NWeapon
{
	none, sword, lance, gloves 
};

struct GameData
{
	char name[MAXNAMESIZE];
	NWeapon currentWeapon; 
	unsigned int enemysKills; 

};

void Log(const char* msg)
{
	std::cout << msg << "\n";

}

const char* WhatWeapon(NWeapon arma)
{
	if (arma == none)
	{
		return "nada";

	}
	else if (arma == sword)
	{
		return "espada"; 
	}
	else if (arma == lance)
	{
		return "lanza";
	}
	else if (arma == gloves)
	{
		return "guantes";
	}
}

int main()
{

	//savegame
	std::fstream savefile("data.save", std::ios::in | std::ios::out);

	if (savefile.is_open())
	{
		Log("save abierto");

		//Lee datos de archivo 
		GameData data; 
		savefile.read(data.name, MAXNAMESIZE);
		savefile.read((char*)&data.currentWeapon, 3); 
		savefile.read((char*)&data.enemysKills, 3);

		std::cout << "hola " << data.name; 
		std::cout << ", tienes una arma " << WhatWeapon(data.currentWeapon) << " y has matado a " << data.enemysKills << " enemigos.";


            Log("Te despiertas en un lugar desconocido, al lado de ti parece ser que hay alguien a tu lado con una tunica larga.");
        Log("Avanzas un poco y a lo lejo ves dos caminos diferentes, a uno de estos caminos la figura con una tunica se decanta a ir.");
        Log("¿Cual camino eliges?.");
        Log("Presiona 1 para izquierda, 2 para derecha con la persona con tunica.");

        std::string respuesta;
        std::cin >> respuesta;

        if (respuesta == "1")
        {
            Log("Avanzas por el camino sin la figura con la tunica");
            savefile.close();
            savefile.open("data.sav", std::ios::out);
            data.currentWeapon = NWeapon::lance;
            Log("La tomas y continuas tu camino.");
            Log("Has caminado mucho, estas cansado y sin dinero");
            Log("Ves una cueva con alimentos y por otro camino de la cueva un tesoro.");
            Log("Presiona 1 para ir por el alimento o 2 para ir por el tesoro.");

            std::cin >> respuesta;

            if (respuesta == "1")
            {
                Log("Comes el alimento pero ya tenia algunos dias ");
                Log("Bueno,tuve que haber cargado un lonche");
            }
            else if (respuesta == "2")
            {
                Log("¡La figura con tunica resulta ser una maga peligrosa!");
                Log("¿Intentas atacar?");
                Log("Presiona 1 para si o 2 para no");

                savefile.close();
                std::cin >> respuesta;

                if (respuesta == "1")
                {
                    Log("Sin esfuerzo, logras matar a la maga");
                    savefile.open("data.sav", std::ios::out);
                    data.enemysKills += 3;
                    if (savefile.is_open())
                    {
                 
                        savefile.seekp(0, std::ios::beg);
                        savefile.write((const char*)&data, sizeof(GameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (respuesta == "2")
                {
                    Log("La maga en realidad no trataba de atacarte, solo hablaba en un lenguaje con un acento extraño y agresivo");
                    Log("La maga y tu continuan viajando, ahora juntos ");
                }

            }
        }
        else if (respuesta == "2")
        {
            Log("Te encuentras unos guantes, los tomas?");
            Log("1. Si");
            Log("2. No");

            savefile.close();
            std::cin >> respuesta;

            if (respuesta == "1")
            {
                savefile.open("data.sav", std::ios::out);
                data.currentWeapon = NWeapon::gloves;
            }
            else {
            }

            Log("Continuas avanzando y te encuentras con una ciudad");
            Log("Aprovechas para descansar y sentar cabeza en algun lugar");
            savefile.close();
            savefile.open("data.sav", std::ios::out);


        }
        else
        {

        }

    }
    else
    {
        Log("crear savefile vacio e inicial");
        GameData data;
        Log("Escribe tu nombre, aventurero");
        std::cin >> data.name;
        data.currentWeapon = NWeapon::none;
        data.enemysKills = 0;
        savefile.open("data.sav", std::ios::out);
        if (savefile.is_open())
        {
            //dumpear la estructura data
            savefile.seekp(0, std::ios::beg);
            savefile.write((const char*)&data, sizeof(GameData));
        }
        else

        {
            Log("no se pudo crear el archivo");
        }

    }

    savefile.close();

    return 0;
}
