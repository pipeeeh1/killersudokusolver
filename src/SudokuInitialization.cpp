#include "SudokuInitialization.h"

//Funcion que abre una instancia de la carpeta instances/ dado un nombre como argumento.
std::ifstream abrirArchivo(const std::string nombre){
    std::ifstream archivo("instances/"+nombre);
    if (!archivo){
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);  
    }
    return archivo;
}

//Carga los datos del archivo en una matriz 9x9, y guarda informacion de los grupos en dos diccionarios
//El primer diccionario tipo numeroGrupoaCeldas guarda un par int numerogrupo a un vector que contiene las coords 
//de las celdas pertenecientes a ese grupo
//El segundo diccionario guarda pares int numero grupo a la suma que debería ser.
std::tuple<Matrix,numeroGrupoaCeldas,numeroGrupoaSuma>inicializarSudoku(std::ifstream& archivo){
    Matrix Sudoku(9, std::vector<Celda>(9));
    numeroGrupoaCeldas GrupoCeldasMap;
    numeroGrupoaSuma GrupoSumaMap;
    std::string linea;

    int y = 0;

    //se lee el archivo linea a linea
    while (std::getline(archivo, linea) && y < 9){
        std::istringstream stream(linea);
        std::string celdastring;
        int x= 0;
        
        //se lee celda a celda
        while (stream >> celdastring && x < 9){
            //Se guarda el grupo que siempre está presente en el substring desde indice 2 en adelante.
            int grupo = std::stoi(celdastring.substr(2));

            //si la celda vale 0 solo se guarda el grupo y se setea como celda no fija
            if (celdastring[0] == '.'){
                Sudoku[y][x] = {0,grupo,0}; 
            } else {// en caso contrario se guarda el valor, el grupo y setea como celda fija
                int valor = std::stoi(celdastring.substr(0, 1));   
                Sudoku[y][x] = {valor,grupo,1};
            }
            //Se agrega al diccionario de celdas, las coordenadas de la celda en su grupo correspondiente.
            GrupoCeldasMap[grupo].push_back({x,y});
            x++;
        }
        y++;
    }

    //Parte que lee las sumas de cada grupo
    while (std::getline(archivo, linea)){
        std::istringstream stream(linea);
        std::string grupo, suma;
        //Se separa el numero de grupo y la suma 
        if (std::getline(stream, grupo, ':') && std::getline(stream, suma)){
            int grupoint= std::stoi(grupo.substr(1));
            int sumaint= std::stoi(suma);
            //Se agrega al diccionario
            GrupoSumaMap[grupoint]=sumaint;
        }
    }
    archivo.close();
    return std::make_tuple(Sudoku,GrupoCeldasMap,GrupoSumaMap);
}
