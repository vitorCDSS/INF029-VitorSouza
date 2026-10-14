#include <stdio.h>

int procuraX (int icresc, int jcresc, int y, int x, char velha[3][3]);
int procuraO (int icresc, int jcresc, int y, int x, char velha[3][3]);

int main(){
    char velha[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};
    int resultado = -1;
    int vez = 1; 
    int voltar;
    int icont;
    char ccont;
    int jcont;
    int contagem = 0;

    while(resultado == -1){
        printf("  1 / 2 / 3 \n");
        printf("A  %c / %c / %c \n", velha[0][0], velha[0][1], velha[0][2]);
        printf("  _________\n");
        printf("B  %c / %c / %c \n", velha[1][0], velha[1][1], velha[1][2]);
        printf("  _________\n");
        printf("C  %c / %c / %c \n", velha[2][0], velha[2][1], velha[2][2]);

        do{
            printf("Jogador%d digite as coordenadas\n", vez);
            scanf(" %c %d", &ccont, &jcont);

            switch(ccont){
                case 'A':
                case 'a':
                    icont = 1;
                    break;
                case 'B':
                case 'b':
                    icont = 2;
                    break;
                case 'C':
                case 'c':
                    icont = 3;
                    break;
                default: 
                    icont == -1; 
                    voltar == 1;
            }

            if(velha[icont-1][jcont-1] == ' '){
                velha[icont-1][jcont-1] = (vez == 1)? 'X' : 'O';
            
            voltar = 0;
            }
            else{
                printf("joga direito animal");
                voltar = 1;
            }
        }while(voltar == 1);
        contagem++;
        
        if(resultado == -1)
            resultado = procuraX (0, 1, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraX (1, 1, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraX (1, 0, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraX (0, -1, 2, 2, velha);
        if(resultado == -1)
            resultado = procuraX (-1, 0, 2, 2, velha);
        if(resultado == -1)
            resultado = procuraX (1, 0, 0, 1, velha);
        if(resultado == -1)
            resultado = procuraX (0, 1, 1, 0, velha);

        if(resultado == -1)
            resultado = procuraO (0, 1, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraO (1, 1, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraO (1, 0, 0, 0, velha);
        if(resultado == -1)
            resultado = procuraO (0, -1, 2, 2, velha);
        if(resultado == -1)
            resultado = procuraO (-1, 0, 2, 2, velha);
        if(resultado == -1)
            resultado = procuraO (1, 0, 0, 1, velha);
        if(resultado == -1)
            resultado = procuraO (0, 1, 1, 0, velha);

        if(resultado == 1)
            printf("Jogador1 venceu\n"); 
        if(resultado == 2)
            printf("Jogador2 venceu\n");

        if(contagem >= 9){
            printf("empate");
            return 0;
        }

        vez = (vez == 1)? 2 : 1;
        
    }
}

int procuraX (int icresc, int jcresc, int y, int x, char velha[3][3]){

  for(int kcont = 0; kcont < 3; kcont++){
    if(velha[y+icresc*kcont][x+jcresc*kcont] != 'X'){
      return -1;
    }
  }
  return 1;
 }

 int procuraO (int icresc, int jcresc, int y, int x, char velha[3][3]){

  for(int kcont = 0; kcont < 3; kcont++){
    if(velha[y+icresc*kcont][x+jcresc*kcont] != 'O'){
      return -1;
    }
  }
  return 2;
 }