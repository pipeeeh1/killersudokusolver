#include "SAiteration.h"
#include "SudokuEvaluation.h"

Matrix SwapCells(Matrix Sudoku,Coords celda1, Coords celda2){
    int x1=celda1.x;
    int y1=celda1.y;

    int x2=celda2.x;
    int y2=celda2.y;

    int aux= Sudoku[y1][x1].valor;

    Sudoku[y1][x1].valor=Sudoku[y2][x2].valor;
    Sudoku[y2][x2].valor=aux;

    return Sudoku;
}

void IteracionSA(Matrix& SudokuActual,Matrix& Sudokubest,int& EvaluacionActual,int& BestEval,float& temp ,float Rateofcooling,std::mt19937& gen,numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma, std::vector<std::vector<Coords>> CeldasSwap3x3){
    std::uniform_int_distribution<> Rand3x3(0, 8);
    std::uniform_int_distribution<> CeldaAleatoria(0, 0);
    int CantidadCeldasSwapeables=0;
    int Cuadrante=0;
    //elegir un cuadrante hasta que el cuadrante tenga más de dos valores swapeables
    //si tiene un solo valor entonces el cuadrante esta correcto y no hay que swapear.
    while (CantidadCeldasSwapeables<2){
        Cuadrante=Rand3x3(gen);
        CantidadCeldasSwapeables = CeldasSwap3x3[Cuadrante].size();
    }
 
    //eleccion de celdas
    CeldaAleatoria.param(std::uniform_int_distribution<>::param_type(0,CantidadCeldasSwapeables-1));

    int pos1=CeldaAleatoria(gen);
    int pos2=CeldaAleatoria(gen);
    while (pos1==pos2){
        pos2= CeldaAleatoria(gen);
    }

    Coords celda1= CeldasSwap3x3[Cuadrante][pos1];
    Coords celda2= CeldasSwap3x3[Cuadrante][pos2];

    //Se hace el swap aleatorio
    Matrix SudokuSwapd = SwapCells(SudokuActual,celda1,celda2);

    //evaluación del swap

    int EvalSwapd = EvaluarSudoku(SudokuSwapd,GrupoaCeldas,GrupoaSuma);
    int dif = EvalSwapd-EvaluacionActual;  //minimizar el valor, por lo que si la dif es negativa, el resultado se acepta instantaneamente. 

    if (dif<0){
        //aceptar
        SudokuActual=SudokuSwapd;
        EvaluacionActual=EvalSwapd;
        if(EvaluacionActual<BestEval){
            BestEval=EvaluacionActual;
            Sudokubest=SudokuActual;
        }
    }else{
        float chance = std::exp(-dif/temp);
        std::uniform_real_distribution rand(0.0,1.0);
        float randvalue = rand(gen);
        if(randvalue<chance){
            SudokuActual=SudokuSwapd;
            EvaluacionActual=EvalSwapd;
        }
    }
    std::cout<<"Evaluación actual:"<<EvaluacionActual<<"\n";
    temp=temp*Rateofcooling;
}
