#include "SudokuEvaluation.h"
#include "MatrixDefinitions.h"


//Se genera un vector de booleanos que indica si el valor se ha visto antes.
//Se recorre numero a numero de la columna, si el numero ya se habia visto antes se suma +1 al contador 
//de repetidos.
int EvaluarColumna(Matrix Sudoku, int NumeroColumna){
    std::vector<bool> existe(9, false);
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
    std::vector<bool> existe(9, false);
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
    float TotalDiferencia = 0;
    for (int i=1; i<=CantidadGrupos; i++){
        float DiferenciaGrupoActual=0;
        int SumaActual=0;
        int SumaReal= GrupoaSuma[i];
        int CantidadCeldasEnGrupo=GrupoaCeldas[i].size();
        for(int j=0; j<CantidadCeldasEnGrupo; j++){
            int x= GrupoaCeldas[i][j].x;
            int y= GrupoaCeldas[i][j].y;
            SumaActual += Sudoku[y][x].valor;
        }
        DiferenciaGrupoActual=(abs(SumaActual-SumaReal))/static_cast<float>(CantidadCeldasEnGrupo); 
    TotalDiferencia+=DiferenciaGrupoActual;
    }
    return (int)std::ceil(TotalDiferencia);
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