#pragma once
#include "MatrixDefinitions.h"
#include <cmath>

int EvaluarColumna(Matrix Sudoku, int NumeroColumna);
int EvaluarFila(Matrix Sudoku, int NumeroFila);
float EvaluarGrupos(Matrix Sudoku,numeroGrupoaCeldas GrupoaCeldas,numeroGrupoaSuma GrupoaSuma);
float EvaluarSudoku(Matrix Sudoku, numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma);