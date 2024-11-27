#include "MatrixDefinitions.h"
#include "SudokuInitialization.h"
#include "GreedyFill.h"
#include "SudokuEvaluation.h"
#include "PrintFuncs.h"
#include "StartSA.h"

int main() {
    //Se pregunta cual instancia abrir
    std::cout<<"Elija la cantidad de casillas vacías(10,20,30,40,50,60,80)";
    std::string casillas;
    std::cin >> casillas;
    std::string instancia = casillas + "blank.txt";
    std::ifstream archivo=abrirArchivo(instancia);


    //Inicializacion de estructuras de datos utilizadas
    auto [Sudoku, GrupoACeldas, GrupoASuma]=inicializarSudoku(archivo);
    printMatrix(Sudoku);
    printGrupoaSuma(GrupoASuma);
    printGrupoaCeldas(GrupoACeldas);

    //Solucion inicial utilizando Greedy
    std::vector<std::vector<Coords>> CeldasSwap3x3=GreedyFill(Sudoku);

    //Evaluacion Solución inicial
    float Evalinicial=EvaluarSudoku(Sudoku,GrupoACeldas,GrupoASuma);
    std::cout<< Evalinicial << std::endl;
    printMatrix(Sudoku);


    //seteo de variables
    int Semilla=110;
    float Temp=1.0;
    float Rateofcooling=0.99;
    int maxIterations=10000000;

    //inicia el SA
    StartSA(Sudoku, Evalinicial,Temp,Rateofcooling,maxIterations,Semilla,GrupoACeldas,GrupoASuma,CeldasSwap3x3);

}