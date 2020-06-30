#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {//Definizione della struttura dati che definisce una regola di produzione in forma normale di Chomsky
                //  A->a      A->BC
  char leftOp;
  char* rightFstOp;
  char rightScnOp;
} productionRule;

typedef enum boolean {false, true} boolean;//Definizione di variabili booleane in C (assenti nello standard utilizzato)

boolean CNFCheck(char * f, char s){//Controllo delle regole di produzione, se essa non è in CNF, viene restituito false
  if(((nonTerminal(f) == true) && s!= NULL) || ((nonTerminal(f) == false) && s == NULL)){
    return true;
  }else{
    return false;
  }
}

boolean nonTerminal(char *f){//Controllo di un carattere non terminale, definito come una stringa di lunghezza 1 (2 se consideriamo il carattere di terminazione) formato da una carattere alfabetico maiuscolo
  if(strlen(f) == 2 && 'A'<=f && f>= 'Z'){
    return true;
  }else{
    return false;
  }
}

boolean CYK(char* t, char* nT, productionRule* gr, int grNum){
  //Inizializzazione delle linghezze degli array di elementi terminali e non terminali
  size_t tNum = strlen(t) - 1;
  size_t ntNum = strlen(nT) - 1;

  //Inizializzazione di un vettore tridimensionale P con tutti gli elementi impostati a false
  boolean P[tNum][tNum][ntNum];
  for(i = 0; i< TNum; i++)
    for(j = 0; j < tNum ; j++)
      for(k = 0; k < nTNum ; k++)
        P[i][j][k] = false;
  for(z = 0; z < grNum; z++){
    for(v = 0; v < ntNum ; v++){
      for(s = 0; s < tNum; s++){
        if(gr[z].leftOp == nT[v] && nonTerminal(gr[z].rightFstOp) == false && gr[z].rightFstOp == t[s] && gr[z].rightScnOp == NULL){//Se il z-esimo elemento di gr è la regola di produzione
                                                                                                                                    //nt[v] -> t[s]
          P[1][s][v] = true;
        }
      }
    }
  }

  for(z = 0; z < grNum; z++){
    for(l = 2; l< tNum; l++){
      for(s = 1; s< (tNum - l + 1); s++){
        for(p = 1; p< (l - 1); p++){

          for(a = 0; a< ntNum; a++){
            for(b = 0; b< ntNum; b++){
              for(c = 0; c< ntNum; c++){
                if(gr[z].leftOp == nT[a] && gr[z].rightFstOp ==nT[b] && gr[z].rightScnOp == nT[c]){
                  if(P[p][s][b] && P[l - p][s - p][c]){
                    P[l][s][a] = true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if(P[n][1][1] == true){
    return true;
  }else{
    return false;
  }
}
