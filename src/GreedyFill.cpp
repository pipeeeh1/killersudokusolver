#include "GreedyFill.h"

//Funcion parte de la solución inicial greedy, la función miope solo se encarga de rellenar correctamente 
//las secciones 3x3 sin repetir valores, no revisa filas ni columnas.
//tambien retorna vector con las coordenadas vacias del 3x3
//util para despues determinar que swaps son validos
std::vector<Coords> Rellenar3x3(Matrix& Sudoku, int inicioFila, int inicioColumna){
    std::set<int> NumerosExistentes;
    std::vector<Coords> CeldasVacias;

    //Se recorre el 3x3, se guardan los numeros que existen, y se guardan las celdas vacías
     for (int y = inicioFila; y < inicioFila + 3; ++y){
        for (int x = inicioColumna; x < inicioColumna + 3; ++x){
            if (Sudoku[y][x].valor != 0) {
                NumerosExistentes.insert(Sudoku[y][x].valor);
            } else {
                CeldasVacias.push_back({x, y});
            }
        }
    }

    std::vector<int> NumerosPosibles;
    for (int num = 1; num <= 9; ++num) {
        //busca el numero del 1 al 9, si no existe(se manda al end del set) y se guarda como numero posible
        if (NumerosExistentes.find(num) == NumerosExistentes.end()){
            NumerosPosibles.push_back(num);
        }
    }

    //rellenar 3x3 con los numeros posibles
    for (std::size_t j= 0; j < CeldasVacias.size(); ++j){
        int x = CeldasVacias[j].x;
        int y = CeldasVacias[j].y;
        Sudoku[y][x].valor = NumerosPosibles[j];
    }
    return CeldasVacias;
}


std::vector<std::vector<Coords>> GreedyFill(Matrix& Sudoku){
    //se llama a la funcion rellenar 3x3 a los 9 sub grupos
    //retorna un vector de vectores que contienen las coordenadas de celdas swapeables
    //cada indice corresponde a un 3x3.
    std::vector<std::vector<Coords>> CeldasSwap3x3(9);
    int i=0;
    for (int inicioFila = 0; inicioFila < 9; inicioFila += 3){
        for (int inicioColumna = 0; inicioColumna < 9; inicioColumna += 3){
            CeldasSwap3x3[i]=Rellenar3x3(Sudoku, inicioFila, inicioColumna);
            i++;
        }
    }
    return CeldasSwap3x3;
}