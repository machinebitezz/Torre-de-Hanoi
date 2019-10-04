#include <stdio.h> 
int c = 0, n;

void troca(int origem , int destino, int matriz[20][3]){ // troca o numero na coluna(torre) origem para a coluna destino
  for(int i = 19; c == 0 && i >= 0; i--){
          for(int j = 0; c == 0 && j < 20; j++){
            if(matriz[i][destino]==0 && matriz[j][origem]!=0){ //checa se o destino está vazio e se a origem tem algum número
              matriz[i][destino] = matriz[j][origem]; //o local de destino recebe o número que está na origem
              matriz[j][origem] = 0;// origem recebe zero
              c = 1;} // c é uma variavel checadora, ela indica se a troca foi feita;
          }
        }
    c = 0;
  return;
}

#define TORRE1 20
#define TORRE2 62
#define TORRE3 104

void mostrar(int representacao[20][3]){

	int grafica[23][125]; //matriz que contem as torres prontas

    int i, j, aux, anel;

    for (i = 0; i < 23; i++){ //inicia a matriz grafica "vazia"
        for (j = 0; j < 125; j++){
            if (j == TORRE1 || j == TORRE2 || j == TORRE3){
                grafica[i][j] = 124;
            }else{
                grafica[i][j] = 32;
            }
        }
    }

    for (i = 0; i < 20; i++){ //posiciona os aneis nas posições corretas
        for (j = 0; j < 3; j++){
            if (representacao[i][j] != 0){
                anel = representacao[i][j];
                switch (j){

                case 0:
                    for (; anel > 0; anel--){
                        grafica[i + 3][TORRE1] = 35;
                        grafica[i + 3][TORRE1 + anel] = 35; //i+3 pois a matriz grafica possui 23 linhas e a matriz representacao possui 20
                        grafica[i + 3][TORRE1 - anel] = 35;
                    }
                break;

                case 1:
                    for (; anel > 0; anel--){
                        grafica[i + 3][TORRE2] = 35;
                        grafica[i + 3][TORRE2 + anel] = 35;
                        grafica[i + 3][TORRE2 - anel] = 35;
                    }
                break;

                case 2:
                    for (; anel > 0; anel--){
                        grafica[i + 3][TORRE3] = 35;
                        grafica[i + 3][TORRE3 + anel] = 35;
                        grafica[i + 3][TORRE3 - anel] = 35;
                    }
                break;
                }
            }
        }
    }

	for (i = 0; i < 23; i++){ //imprime o resultado final
        for (j = 0; j < 125; j++){
            printf("%c", grafica[i][j]);
        }
        printf("\n");
	}
  printf("\n");
}

void towerOfHanoi(int num, int origem, int dest, int aux, int matriz[20][3]) //algoritmo que define como a torre de hanoi é resolvida de acordo com o número de discos
{   
    
    if (num == 1) 
    {   
        troca(origem, dest, matriz);
        mostrar(matriz);
        return; 
    } 
    towerOfHanoi(num-1, origem, aux, dest, matriz);
    troca(origem, dest, matriz);
    mostrar(matriz); 
    towerOfHanoi(num-1, aux, dest, origem, matriz); 
} 

int main() 
{ int num_aneis;
  
  scanf("%d", &n);// lê o num de discos
  num_aneis = n;
    int mat[20][3], i , j;

    for( i = 19; i >= 0 ; i--){// construção da matriz inicial(aquela com discos somente na primeira coluna)
      for( j = 0; j < 3; j++){
        if(j == 0 && num_aneis != 0){// se for a primeira coluna e se o num_aneis != 0, o local na matriz receberá um número que corresponde ao tamanho do seu disco
          mat[i][j] = num_aneis--;
        }else{
          mat[i][j] = 0;
        }}}
    
    mostrar(mat);
    towerOfHanoi(n, 0, 2, 1, mat);
    return 0; 
} 
