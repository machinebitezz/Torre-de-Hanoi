#include <stdio.h> 
#include <ctype.h>
#define TORRE1 20
#define TORRE2 62
#define TORRE3 104
#define clear() printf("\033[H\033[J"); //funciona como clear screen(limpar a tela), o "clear" aparece antes de todos "imprimirTorres" para que possamos vizualizar uma de cada vez
int n; // variavel global que representa o numero de discos

void troca(int origem , int destino, int matriz[20][3]){ // troca o disco na coluna(torre) origem para a coluna destino
  
    int c = 0;
  
    for(int i = 19; c == 0 && i >= 0; i--){
        for(int j = 0; c == 0 && j < 20; j++){
            if(matriz[i][destino]==0 && matriz[j][origem]!=0){ //checa se o destino está vazio e se a origem tem algum número nãp nulo
              matriz[i][destino] = matriz[j][origem]; //o local de destino recebe o número que está na origem
              matriz[j][origem] = 0;// origem recebe zero
              c = 1;
            } //c é uma variavel checadora, ela indica se a troca foi feita, se tiver sido feita os dois "for" param
        }	// assim, apenas uma troca é feita por vez
    }
    c = 0;
}
void imprimirTorres(int representacao[20][3]){

    int grafica[23][125]; //matriz que contem as torres prontas
    int i, j, aux, anel;

    printf("\n");//utilizado para separar as linhas de texto da ilustração da torre

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
  printf("\n"); //utilizado para separar as linhas de texto da ilustração da torre
  getchar(); //funciona como o readkey do pascal, serve para facilitar a vizualição de cada passo do jogo e da resolução
}

void Hanoi(int num, int origem, int dest, int aux, int matriz[20][3]){ //algoritmo recursivo que define como a torre de hanoi é resolvida de acordo com o número de discos   
    
    if (num == 1){
        troca(origem, dest, matriz);
        clear();
        printf("Mova o disco %d da torre %d para a torre %d:\n", num, origem + 1, dest + 1); // explica o que aconteceu em cada passo da resolução
        imprimirTorres(matriz);
        return; 
    }
    
    Hanoi(num-1, origem, aux, dest, matriz);
    troca(origem, dest, matriz);
    clear();
    printf("Mova o disco %d da torre %d para a torre %d:\n", num, origem + 1, dest + 1);
    imprimirTorres(matriz); 
    Hanoi(num-1, aux, dest, origem, matriz);
}

void jogo(int matriz[20][3]){ //procedimento que define o jogo
  
    int orig, dest, c = 0;

    printf("Escreva o numero da torre de origem e numero da torre de destino.\n");
    lerOD: scanf("%d %d", &orig, &dest); // lê o local de onde se quer tirar o disco e local no qual se quer colocar o disco
    orig --; // o jogador selecionará as colunas(torres) pelos números 1, 2 e 3
    dest--;  // porém os indices das torres no código são 0, 1 e 2. Por isso é necessário a subtração por 1

    for(int i = 20 - n; c == 0 && i < 20; i++){ // a linha i == 20-n corresponde a altura máxima da torre, o algoritmo também funcionaria se i == 0, porém seriam repetições desnecessárias
        if(matriz[i][orig] != 0){			//verifica se o movimento é valido
            for(int j = 20 - n; c == 0 && j < 20; j++){
                if(matriz[i][orig] < matriz[j][dest] || (matriz[j][dest] == 0 && j == 19)){ // não será válido se um disco maior for colocado em cima de um menor
                    c = 1; //variavel para verificação
                }
            }
        }
    }

    switch (c){
    
    case 1:
        troca(orig, dest, matriz); 
        clear();
        imprimirTorres(matriz);	// caso o movimento seja válido, o procedimento se repetirá até a vitória do jogador
        if(matriz[20 - n][2] == 1 || matriz[20 - n][1] == 1){ // verificação se o jogo foi vencido
            printf("Voce venceu!!\n");
            break; //faz isso checando se as torres 2 e 3, na linha 20-n (altura máxima da torre) tem o disco 1
        }else{
            jogo(matriz);
        }
    break;
    
    case 0:
        printf("Movimento inválido. Tente novamente.\n");
        goto lerOD;	// caso seja inválido, o programa voltará a linha de código de leitura dos locais (orig e dest)
    break;
    }
}

int main(void) {

    int num_aneis, mat[20][3], i, j;
    char opcao;

    printf("O que deseja fazer?\n");
    printf("Jogar Torre de Hanoi (J)\n");
    printf("Resolver Torre de Hanoi (R)\n");
    lerOp: scanf(" %c", &opcao);

    opcao = toupper(opcao);

    if(opcao != 74 && opcao != 82){			//verifica se o caracter é válido
          printf("Opção inválida.\nEscreva novamente.\n");	// caso não seja, volta-se para linha de leitura da opção
          goto lerOp;
    }

    printf("Com quantos aneis deseja jogar?\n");
    scanf(" %d", &num_aneis);

    n = num_aneis; // variavel global recebe o número de aneis

    for( i = 19; i >= 0 ; i--){// construção da matriz inicial(aquela com discos somente na primeira coluna)
        for( j = 0; j < 3; j++){
            if(j == 0 && num_aneis != 0){// se for a primeira coluna e se o num_aneis != 0, o local na matriz receberá um número que corresponde ao tamanho do seu disco
                mat[i][j] = num_aneis--;
            }else{
                mat[i][j] = 0;
            }
        }
    }
    clear(); // apaga o que foi escrito até agora, para ficar mais organizado a vizualizção dos próximos passos (jogo ou resolução)
    
    switch (opcao){
    
    case 'J':
        imprimirTorres(mat);
        jogo(mat);
        break;
    
    case 'R':
        clear();
        printf("Para resolver a torre de hanoi:\n");
        imprimirTorres(mat);
        getchar();
        Hanoi(n, 0, 2, 1, mat);
        printf("Resolvido\n");
        break;
    }
    return 0;
}