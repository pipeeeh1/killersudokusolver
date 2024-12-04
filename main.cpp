#include "MatrixDefinitions.h"
#include "SudokuInitialization.h"
#include "GreedyFill.h"
#include "SudokuEvaluation.h"
#include "PrintFuncs.h"
#include "SAiteration.h"
#include <chrono>

int main() {

    //Se pregunta cual instancia abrir
    std::cout<<"Elija la cantidad de casillas vacías(10,20,30,40,50,60,80)";
    std::string casillas;
    std::cin >> casillas;
    //se inicia el reloj
    auto start = std::chrono::high_resolution_clock::now();
    std::string instancia = casillas + "blank.txt";
    std::ifstream archivo=abrirArchivo(instancia);


    //Inicializacion de estructuras de datos utilizadas
    auto [Sudoku, GrupoACeldas, GrupoASuma]=inicializarSudoku(archivo);
    printMatrix(Sudoku);

    //Solucion inicial utilizando Greedy
    std::vector<std::vector<Coords>> CeldasSwap3x3=GreedyFill(Sudoku);

    //Evaluacion Solución inicial
    int Evalinicial=EvaluarSudoku(Sudoku,GrupoACeldas,GrupoASuma);
    std::cout<<"Eval Inicial:" <<Evalinicial << std::endl;
    printMatrix(Sudoku);


    //seteo de variables
    int Semilla=110;
    float temp=1.0;
    float Rateofcooling=0.99;
    int maxIterations=1000000;

    //inicia el SA
    Matrix& Bestsudoku=Sudoku;
    int& Besteval=Evalinicial;
    std::mt19937 gen(Semilla);
    int contadorNomejora;
    int BestEvalprevia;
    int i=0;
    while ((i<maxIterations)&&(Besteval!=0)){
        BestEvalprevia=Besteval;
        IteracionSA(Sudoku,Bestsudoku,Evalinicial,Besteval,temp,Rateofcooling,gen,GrupoACeldas,GrupoASuma,CeldasSwap3x3);    
        i++;

        //contador para recalentado en caso de que quede en minimo local.
        if(Besteval==BestEvalprevia){
            contadorNomejora++;
        }else{
            contadorNomejora=0;
        }

        if(contadorNomejora>500){
            temp=1.0;
            std::cout<<"Mínimo local detectado, recalentando sistema"<< std::endl;
            contadorNomejora=0;
        }
    }

    printMatrix(Bestsudoku);
    std::cout<<"Cantidad iteraciones:" <<i<<std::endl;
    std::cout<<"Evaluación final:" <<Besteval<< std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tiempo de ejecución: " << duration.count() << " milisegundos." << std::endl;
    
}