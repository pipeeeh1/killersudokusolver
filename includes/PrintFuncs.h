#pragma once
#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include "MatrixDefinitions.h"

void printMatrix(Matrix& sudoku);
void printGrupoaSuma(numeroGrupoaSuma dictionary);
void printGrupoaCeldas(numeroGrupoaCeldas dictionary);
void PrintVectorOfVectors(const std::vector<std::vector<Coords>>& vec);