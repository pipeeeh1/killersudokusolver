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
//alias numeroGrupoaSuma= diccionario que contiene la suma de cada grupo
using numeroGrupoaSuma = map<int, int>;
//alias numeroGrupoaCeldas= diccionario que contiene las coordenadas de celdas que pertenecen a cada grupo
using numeroGrupoaCeldas= map<int, vector<Coords>>;

//Funcion que abre una instancia de la carpeta instances/ dado un nombre como argumento.
ifstream abrirArchivo(const string nombre){
    ifstream archivo("instances/"+nombre);
    if (!archivo){
        cerr << "Error al abrir el archivo" << endl;
        exit(1);  
    }
    return archivo;
}

//Carga los datos del archivo en una matriz 9x9, y guarda informacion de los grupos en dos diccionarios
//El primer diccionario tipo numeroGrupoaCeldas guarda un par int numerogrupo a un vector que contiene las coords 
//de las celdas pertenecientes a ese grupo
//El segundo diccionario guarda pares int numero grupo a la suma que debería ser.
tuple<Matrix,numeroGrupoaCeldas,numeroGrupoaSuma>inicializarSudoku(ifstream& archivo){
    Matrix Sudoku(9, vector<Celda>(9));
    numeroGrupoaCeldas GrupoCeldasMap;
    numeroGrupoaSuma GrupoSumaMap;
    string linea;

    int y = 0;

    //se lee el archivo linea a linea
    while (getline(archivo, linea) && y < 9){
        istringstream stream(linea);
        string celdastring;
        int x= 0;
        
        //se lee celda a celda
        while (stream >> celdastring && x < 9){
            //Se guarda el grupo que siempre está presente en el substring desde indice 2 en adelante.
            int grupo = stoi(celdastring.substr(2));

            //si la celda vale 0 solo se guarda el grupo y se setea como celda no fija
            if (celdastring[0] == '.'){
                Sudoku[y][x] = {0,grupo,0}; 
            } else {// en caso contrario se guarda el valor, el grupo y setea como celda fija
                int valor = stoi(celdastring.substr(0, 1));   
                Sudoku[y][x] = {valor,grupo,1};
            }
            //Se agrega al diccionario de celdas, las coordenadas de la celda en su grupo correspondiente.
            GrupoCeldasMap[grupo].push_back({x,y});
            x++;
        }
        y++;
    }

    //Parte que lee las sumas de cada grupo
    while (getline(archivo, linea)){
        istringstream stream(linea);
        string grupo, suma;
        //Se separa el numero de grupo y la suma 
        if (getline(stream, grupo, ':') && getline(stream, suma)){
            int grupoint= stoi(grupo.substr(1));
            int sumaint= stoi(suma);
            //Se agrega al diccionario
            GrupoSumaMap[grupoint]=sumaint;
        }
    }
    archivo.close();
    return make_tuple(Sudoku,GrupoCeldasMap,GrupoSumaMap);
}

//Funcion parte de la solución inicial greedy, la función miope solo se encarga de rellenar correctamente 
//las secciones 3x3 sin repetir valores, no revisa filas ni columnas.
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
    //se llama a la funcion rellenar 3x3 a los 9 sub grupos
    for (int inicioFila = 0; inicioFila < 9; inicioFila += 3){
        for (int inicioColumna = 0; inicioColumna < 9; inicioColumna += 3){
            Rellenar3x3(Sudoku, inicioFila, inicioColumna);
        }
    }
}

//Se genera un vector de booleanos que indica si el valor se ha visto antes.
//Se recorre numero a numero de la columna, si el numero ya se habia visto antes se suma +1 al contador 
//de repetidos.
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

//Se genera un vector de booleanos que indica si el valor se ha visto antes.
//Se recorre numero a numero de la fila, si el numero ya se habia visto antes se suma +1 al contador 
//de repetidos.
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

//Se recorre cada grupo, sumando las celdas que pertenecen a ese grupo
//luego se resta el valor SumaActual con el valor SumaReal
//se saca el valor absoluto de esta diferencia y se divide por la cantidad de celdas del grupo.
int EvaluarGrupos(Matrix Sudoku,numeroGrupoaCeldas GrupoaCeldas,numeroGrupoaSuma GrupoaSuma){
    int CantidadGrupos = GrupoaSuma.size();
    int TotalDiferencia = 0;
    for (int i=1; i<=CantidadGrupos; i++){
        int DiferenciaGrupoActual=0;
        int SumaActual=0;
        int SumaReal= GrupoaSuma[i];
        int CantidadCeldasEnGrupo=GrupoaCeldas[i].size();
        for(int j=0; j<CantidadCeldasEnGrupo; j++){
            int x= GrupoaCeldas[i][j].x;
            int y= GrupoaCeldas[i][j].y;
            SumaActual += Sudoku[y][x].valor;
        }
        DiferenciaGrupoActual=(abs(SumaActual-SumaReal))/CantidadCeldasEnGrupo; 
    TotalDiferencia+=DiferenciaGrupoActual;
    }
    return TotalDiferencia;
}


//Se llaman a las funciones EvaluarFila por cada fila, EvaluarColumna por cada columna
//y se llama a la funcion EvaluarGrupos que calcula las diferencias para todos los grupos
//Luego se suma todo y se consigue el valor Evaluación.
//Un sudoku perfecto tiene valor evaluación 0, por lo que se debe minimizar este valor.
int EvaluarSudoku(Matrix Sudoku, numeroGrupoaCeldas GrupoaCeldas , numeroGrupoaSuma GrupoaSuma){
    int sum=0;
    for(int y=0; y<9; y++){
        sum += EvaluarFila(Sudoku,y);
    }

    for(int x=0; x<9; x++){
        sum += EvaluarColumna(Sudoku,x);
    }
    sum+= EvaluarGrupos(Sudoku, GrupoaCeldas, GrupoaSuma);
    return sum;
}

//Funcion que printea el sudoku por consola
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
//Funcion que printea los valores guardados en el diccionario numeroGrupoaSuma.
void printGrupoaSuma(numeroGrupoaSuma dictionary){
    for (const auto& par : dictionary){
        cout << "Grupo " << par.first << ": " << par.second <<endl;
    }
}

//Funcion que printea los valores guardados en el diccionario numeroGrupoaCeldas.
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
    //Se pregunta cual instancia abrir
    cout<<"Elija la cantidad de casillas vacías(10,20,30,40,50,60,80)";
    string casillas;
    cin >> casillas;
    string instancia = casillas + "blank.txt";
    ifstream archivo=abrirArchivo(instancia);
    //Inicializacion de estructuras de datos utilizadas
    auto [Sudoku, GrupoACeldas, GrupoASuma]=inicializarSudoku(archivo);

    //Solucion inicial utilizando Greedy
    GreedyFill(Sudoku);
    //Evaluacion Solución inicial
    int repetidos=EvaluarSudoku(Sudoku,GrupoACeldas,GrupoASuma);
    cout<< repetidos << endl;
    printMatrix(Sudoku);
    
}