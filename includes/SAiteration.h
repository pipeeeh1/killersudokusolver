#pragma once
#include <random>
#include <cmath>
#include <iostream>
#include "MatrixDefinitions.h"
#include "SAiteration.h"
#include "PrintFuncs.h"

Matrix SwapCells(Matrix Sudoku,Coords celda1, Coords celda2);

void IteracionSA(Matrix& SudokuActual,Matrix& Sudokubest,int& EvaluacionActual,int& BestEval,float& temp ,float Rateofcooling,std::mt19937& gen,numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma, std::vector<std::vector<Coords>> CeldasSwap3x3);