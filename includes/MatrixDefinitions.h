
#pragma once
#include <vector>
#include <map>

struct Celda{
    int valor;
    int grupo;
    //indica si el valor se puede mover o es valor fijo dado por el puzzle.
    bool numeroFijo; 
};

struct Coords{
    int x;
    int y;
};

//alias Matrix=un vector de 9 vectores, donde cada sub vector contiene un struct tipo Celda.
using Matrix = std::vector<std::vector<Celda>>;
//alias numeroGrupoaSuma= diccionario que contiene la suma de cada grupo
using numeroGrupoaSuma = std::map<int, int>;
//alias numeroGrupoaCeldas= diccionario que contiene las coordenadas de celdas que pertenecen a cada grupo
using numeroGrupoaCeldas= std::map<int, std::vector<Coords>>;