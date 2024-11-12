#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

struct Celda {
    int valor;
    int grupo;
    //indica si el valor se puede mover o es valor fijo dado por el puzzle.
    bool numeroFijo; 
};

struct Coords{
    int x;
    int y;
};

//alias Matrix=un vector de 9 vectores, donde cada sub vector contiene un struct tipo Celda.
using Matrix = vector<vector<Celda>>;
using numeroGrupoaSuma = map<int, int>;
using numeroGrupoaCeldas= unordered_map<int, vector<Coords>>;

ifstream abrirArchivo(const string& nombre) {
    std::ifstream archivo("instances/"+nombre);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);  
    }
    return archivo;
}


tuple<Matrix,numeroGrupoaCeldas,numeroGrupoaSuma> inicializarSudoku(ifstream& archivo){

    Matrix Sudoku(9, std::vector<Celda>(9));
    numeroGrupoaCeldas GrupoCeldasMap;
    numeroGrupoaSuma GrupoSumaMap;
    string linea;

    int y = 0;
    while (getline(archivo, linea) && y < 9) {
        istringstream stream(linea);
        string celdastring;
        int x= 0;
        
        while (stream >> celdastring && x < 9) {
                int grupo = stoi(celdastring.substr(2));
            if (celdastring[0] == '.') {
                Sudoku[y][x] = {0,grupo,0}; 
            } else {
                int valor = stoi(celdastring.substr(0, 1));   
                Sudoku[y][x] = {valor,grupo,1};
            }
            GrupoCeldasMap[grupo].push_back({x,y});
            x++;
        }
        y++;
    }

    while (getline(archivo, linea)) {
        istringstream stream(linea);
        string grupo, suma;
        if (getline(stream, grupo, ':') && getline(stream, suma)) {
            int grupoint= stoi(grupo.substr(1));
            int sumaint= stoi(suma);
            GrupoSumaMap[grupoint]=sumaint;
        }
    }

    return make_tuple(Sudoku,GrupoCeldasMap,GrupoSumaMap);
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

void printGrupoaSuma(numeroGrupoaSuma dictionary){
    for (const auto& par : dictionary) {
        cout << "Grupo " << par.first << ": " << par.second <<endl;
    }
}

int main() {
    string instancia ="10blank.txt";
    ifstream archivo=abrirArchivo(instancia);

    auto [Sudoku, GrupoACeldas, GrupoASuma]=inicializarSudoku(archivo);

    printMatrix(Sudoku);
    printGrupoaSuma(GrupoASuma);
    
}