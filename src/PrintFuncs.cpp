#include "PrintFuncs.h"

//Funcion que printea el sudoku por consola
void printMatrix(Matrix& sudoku){
     for (int y = 0; y < 9; y++){
        if (y==3 or y==6) {
            std::cout << "------+-------+------" << std::endl; 
        }

        for (int x = 0; x < 9; x++){
            if (x==3 or x==6) {
                std::cout << "| ";
            }
            std::cout << sudoku[y][x].valor << " ";
        }
        std::cout << std::endl;
    }
    std::cout<< std::endl;
}

//Funcion que printea los valores guardados en el diccionario numeroGrupoaSuma.
void printGrupoaSuma(numeroGrupoaSuma dictionary){
    for (const auto& par : dictionary){
        std::cout << "Grupo " << par.first << ": " << par.second <<std::endl;
    }
}

//Funcion que printea los valores guardados en el diccionario numeroGrupoaCeldas.
void printGrupoaCeldas(numeroGrupoaCeldas dictionary){
    for (const auto& group : dictionary){
        std::cout << "Grupo " << group.first << ": ";
        for (Coords cell : group.second){
            std::cout << "(" << cell.x << "," << cell.y << ")";
        }
        std::cout << std::endl;
        
    }
}

//testing
void PrintVectorOfVectors(const std::vector<std::vector<Coords>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "Grupo " << i + 1 << ":\n";
        for (const auto& coord : vec[i]) {
            std::cout << "(" << coord.x << ", " << coord.y << ") ";
        }
        std::cout << "\n";
    }
}