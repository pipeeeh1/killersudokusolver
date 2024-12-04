#pragma once
#include "MatrixDefinitions.h"
#include <cmath>

int EvaluarColumna(Matrix Sudoku, int NumeroColumna);
int EvaluarFila(Matrix Sudoku, int NumeroFila);
int EvaluarGrupos(Matrix Sudoku,numeroGrupoaCeldas GrupoaCeldas,numeroGrupoaSuma GrupoaSuma);
int EvaluarSudoku(Matrix Sudoku, numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma);