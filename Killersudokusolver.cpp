#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Celda {
    int valor;
    int grupo=0;
    //indica si el valor se puede mover o es valor fijo dado por el puzzle.
    bool numeroFijo=0; 
};

//alias Matrix=un vector de 9 vectores, donde cada sub vector contiene un struct tipo Celda.
using Matrix = vector<vector<Celda>>;

Matrix inicializarSudoku(string& Nombre){
    ifstream archivo(Nombre);

    if (!archivo) {
        std::cerr << "No se puede abrir archivo" << std::endl;
        //matriz vacia
        return {};
    }

    Matrix Sudoku;






    return Sudoku;
}

void printMatrix(Matrix& sudoku){
     for (int y = 0; y < 9; y++) {
        if (y==3 or y==6) {
            cout << "------+-------+------" << endl; 
        }

        for (int x = 0; x < 9; x++) {
            if (x==3 or x==6) {
                cout << "| ";
            }
            cout << sudoku[y][x].valor << " ";
        }
        cout << endl;
    }
}

int main() {
    //string instancia ="10blank.txt";

    //Matrix Sudoku=inicializarSudoku(instancia);

    Matrix sudokutest(9, std::vector<Celda>(9));
    
    for (int y=0; y<9; y++){
        for(int x=0; x<9 ;x++){
            sudokutest[y][x].valor=x;   
        }
    }
    
    printMatrix(sudokutest);
}