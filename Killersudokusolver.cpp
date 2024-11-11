#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Celda {
    int valor;
    int grupo;
    //indica si el valor se puede mover o es valor fijo dado por el puzzle.
    bool numeroFijo; 
};

//alias Matrix=un vector de 9 vectores, donde cada sub vector contiene un struct tipo Celda.
using Matrix = vector<vector<Celda>>;

ifstream abrirArchivo(const string& nombre) {
    std::ifstream archivo("instances/"+nombre);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);  
    }
    return archivo;
}


Matrix inicializarSudoku(ifstream& archivo){

    Matrix Sudoku(9, std::vector<Celda>(9));
    string linea;

    int y = 0;
     while (getline(archivo, linea) && y < 9) {
        istringstream stream(linea);
        string celdastring;
        int x= 0;
        
        while (stream >> celdastring && x < 9) {
            if (celdastring[0] == '.') {
                Sudoku[y][x] = {0, stoi(celdastring.substr(2),0)}; 
            } else {
                int valor = stoi(celdastring.substr(0, 1)); 
                int grupo = stoi(celdastring.substr(2));  
                Sudoku[y][x] = {valor,grupo,1};
            }
            x++;
        }
        y++;
    }






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
    string instancia ="10blank.txt";
    ifstream archivo=abrirArchivo(instancia);
    Matrix Sudoku=inicializarSudoku(archivo);

    printMatrix(Sudoku);
}