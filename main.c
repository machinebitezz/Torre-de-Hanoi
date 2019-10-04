#include <stdio.h>
#define TORRE1 20
#define TORRE2 62
#define TORRE3 104

void imprimirTorres(int representacao[20][3]){

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
}

int main(){

    //code goes here

}