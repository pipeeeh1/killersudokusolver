#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Celda{
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
using numeroGrupoaCeldas= map<int, vector<Coords>>;

ifstream abrirArchivo(const string nombre){
    ifstream archivo("instances/"+nombre);
    if (!archivo){
        cerr << "Error al abrir el archivo" << endl;
        exit(1);  
    }
    return archivo;
}

tuple<Matrix,numeroGrupoaCeldas,numeroGrupoaSuma>inicializarSudoku(ifstream& archivo){

    Matrix Sudoku(9, vector<Celda>(9));
    numeroGrupoaCeldas GrupoCeldasMap;
    numeroGrupoaSuma GrupoSumaMap;
    string linea;

    int y = 0;
    while (getline(archivo, linea) && y < 9){
        istringstream stream(linea);
        string celdastring;
        int x= 0;
        
        while (stream >> celdastring && x < 9){
                int grupo = stoi(celdastring.substr(2));
            if (celdastring[0] == '.'){
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

    while (getline(archivo, linea)){
        istringstream stream(linea);
        string grupo, suma;
        if (getline(stream, grupo, ':') && getline(stream, suma)){
            int grupoint= stoi(grupo.substr(1));
            int sumaint= stoi(suma);
            GrupoSumaMap[grupoint]=sumaint;
        }
    }
    archivo.close();
    return make_tuple(Sudoku,GrupoCeldasMap,GrupoSumaMap);
}

void Rellenar3x3(Matrix& Sudoku, int inicioFila, int inicioColumna){
    set<int> NumerosExistentes;
    vector<Coords> CeldasVacias;

    //Se recorre el 3x3, se guardan los numeros que existen, y se guardan las celdas vacías
     for (int y = inicioFila; y < inicioFila + 3; ++y){
        for (int x = inicioColumna; x < inicioColumna + 3; ++x){
            if (Sudoku[y][x].valor != 0) {
                NumerosExistentes.insert(Sudoku[y][x].valor);
            } else {
                CeldasVacias.push_back({x, y});
            }
        }
    }

    vector<int> NumerosPosibles;
    for (int num = 1; num <= 9; ++num) {
        //busca el numero del 1 al 9, si no existe(se manda al end del set) y se guarda como numero posible
        if (NumerosExistentes.find(num) == NumerosExistentes.end()){
            NumerosPosibles.push_back(num);
        }
    }

    //rellenar 3x3 con los numeros posibles
    for (size_t j= 0; j < CeldasVacias.size(); ++j){
        int x = CeldasVacias[j].x;
        int y = CeldasVacias[j].y;
        Sudoku[y][x].valor = NumerosPosibles[j];
    }
}

void GreedyFill(Matrix& Sudoku){
    //se rellena de 3x3 en 3x3
    for (int inicioFila = 0; inicioFila < 9; inicioFila += 3){
        for (int inicioColumna = 0; inicioColumna < 9; inicioColumna += 3){
            Rellenar3x3(Sudoku, inicioFila, inicioColumna);
        }
    }
}

int EvaluarColumna(Matrix Sudoku, int NumeroColumna){
    vector<bool> existe(9, false);
    int counter=0;
    for(int y=0; y<9; y++){
        int numero= Sudoku[y][NumeroColumna].valor;
        int indice= numero-1;

        if(existe[indice]== true){
            counter++;
        }else{
            existe[indice]=true;
        }
    }
    return counter;
};

int EvaluarFila(Matrix Sudoku, int NumeroFila){
    vector<bool> existe(9, false);
    int counter=0;
    for(int x=0; x<9; x++){
        int numero= Sudoku[NumeroFila][x].valor;
        int indice= numero-1;

        if(existe[indice]== true){
            counter++;
        }else{
            existe[indice]=true;
        }
    }
    return counter;
}

int EvaluarGrupos(Matrix Sudoku,numeroGrupoaCeldas GrupoaCeldas,numeroGrupoaSuma GrupoaSuma){
    int CantidadGrupos= GrupoaSuma.size();
    for (int=0; i<CantidadGrupos; i++){

    }
}
 
int EvaluarSudoku(Matrix Sudoku){
    int sum=0;
    for(int y=0; y<9; y++){
        sum += EvaluarFila(Sudoku,y);
    }

    for(int x=0; x<9; x++){
        sum += EvaluarColumna(Sudoku,x);
    }
    return sum;


}

void printMatrix(Matrix& sudoku){
     for (int y = 0; y < 9; y++){
        if (y==3 or y==6) {
            cout << "------+-------+------" << endl; 
        }

        for (int x = 0; x < 9; x++){
            if (x==3 or x==6) {
                cout << "| ";
            }
            cout << sudoku[y][x].valor << " ";
        }
        cout << endl;
    }
}

void printGrupoaSuma(numeroGrupoaSuma dictionary){
    for (const auto& par : dictionary){
        cout << "Grupo " << par.first << ": " << par.second <<endl;
    }
}

void printGrupoaCeldas(numeroGrupoaCeldas dictionary){
    for (const auto& group : dictionary){
        cout << "Grupo " << group.first << ": ";
        for (Coords cell : group.second){
            cout << "(" << cell.x << "," << cell.y << ")";
        }
        cout << endl;
        
    }
}

int main() {

    cout<<"Elija la cantidad de casillas vacías(10,20,30,40,50,60,80)";
    string casillas;
    cin >> casillas;
    string instancia = casillas + "blank.txt";
    ifstream archivo=abrirArchivo(instancia);


    auto [Sudoku, GrupoACeldas, GrupoASuma]=inicializarSudoku(archivo);
    printMatrix(Sudoku);
    cout << endl;
    GreedyFill(Sudoku);

    int repetidos;
    repetidos=EvaluarSudoku(Sudoku);

    cout<< repetidos << endl;
    printMatrix(Sudoku);
    

    //printGrupoaSuma(GrupoASuma);
    //printGrupoaCeldas(GrupoACeldas);
    
}