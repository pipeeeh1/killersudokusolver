#pragma once
#include <set>
#include "MatrixDefinitions.h"

std::vector<Coords> Rellenar3x3(Matrix& Sudoku, int inicioFila, int inicioColumna);

std::vector<std::vector<Coords>> GreedyFill(Matrix& Sudoku);