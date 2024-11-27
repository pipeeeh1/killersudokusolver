#pragma once
#include <random>
#include <cmath>
#include <iostream>
#include "MatrixDefinitions.h"
#include "SAiteration.h"
#include "PrintFuncs.h"

Matrix StartSA(Matrix& Sudoku, float& Evalinicial,float& temp,float Rateofcooling ,int maxIterations,int Semilla, numeroGrupoaCeldas GrupoACeldas, numeroGrupoaSuma GrupoASuma,std::vector<std::vector<Coords>> CeldasSwap3x3);

Matrix SwapCells(Matrix Sudoku,Coords celda1, Coords celda2);

void IteracionSA(Matrix& SudokuActual,Matrix& Sudokubest,float& EvaluacionActual,int& BestEval,float& temp ,float Rateofcooling,std::mt19937& gen,numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma, std::vector<std::vector<Coords>> CeldasSwap3x3);