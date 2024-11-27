#pragma once

#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include "MatrixDefinitions.h"

//Funcion que abre una instancia de la carpeta instances/ dado un nombre como argumento.
std::ifstream abrirArchivo(const std::string nombre);

//Carga los datos del archivo en una matriz 9x9, y guarda informacion de los grupos en dos diccionarios
//El primer diccionario tipo numeroGrupoaCeldas guarda un par int numerogrupo a un vector que contiene las coords 
//de las celdas pertenecientes a ese grupo
//El segundo diccionario guarda pares int numero grupo a la suma que debería ser.
std::tuple<Matrix,numeroGrupoaCeldas,numeroGrupoaSuma>inicializarSudoku(std::ifstream& archivo);
