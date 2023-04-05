#include <iostream>
#include<windows.h>
#include<conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

void cor_texto (int fonte, int fundo=0) {
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (fonte | fundo<<4));
}


void moverCaixa(int matriz[10][10], int caixaX, int CaixaY, int deslocamentox, int deslocamentoy) {
  int novoX = caixaX + deslocamentox;
  int novoY = CaixaY + deslocamentoy;
  if (matriz[novoX][novoY] != 1 && matriz[novoX][novoY] != 2) {
    matriz[caixaX][CaixaY] = 0;
    matriz[novoX][novoY] = 2;
  }
} //Sub Rotina usada para mover a caixa

void moverJogador(int matriz[10][10], int& player_x, int& player_y, int deslocamentox, int deslocamentoy) {
  int novoX = player_x + deslocamentox;
  int novoY = player_y + deslocamentoy;

    if (matriz[novoX][novoY] != 1) {
        player_x = novoX;
        player_y = novoY;

    if (matriz[novoX][novoY] == 2 || matriz[novoX][novoY] == 5){

        moverCaixa(matriz, novoX, novoY, deslocamentox, deslocamentoy);
    }
  }
} //Sub Rotina usada para mover o player

//Cada mapa tem sua função
void mapa1(){
        ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        //IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, ACIMA.

    int miniCosmo3[10][10]={ 1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,0,0,0,1,1,1,
                             1,1,0,2,0,1,0,1,1,1,
                             1,1,0,1,0,0,3,0,1,1,
                             1,1,0,3,0,0,1,0,1,1,
                             1,1,1,2,1,3,2,0,1,1,
                             1,1,1,0,0,0,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1 };

    //Posi  o inicial do personagem no console
    int x=7, y=3;
    //Vari vel para tecla precionada
    char tecla;


    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (miniCosmo3[i][j]){
                        case 0: cor_texto(8,0); cout<<" "; cor_texto(7,0); break; //Espaco Vazio
                        case 1: cor_texto(8,0); cout<<char(219); cor_texto(7,0); break; //Parede
                        case 2: cor_texto(12,0); cout<<char(254); cor_texto(7,0); break; //Caixa
                        case 3: cor_texto(13,0); cout<<char(5); cor_texto(7,0); break; //Local de Armazenagem
                        default: cout<<"-"; //Erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                   moverJogador(miniCosmo3,x,y,-1,0); //Chama a função para o jogador se movimentar, dentro dela está a função para movimentar as caixas.
                break;
                case 80: case 's': ///baixo
                   moverJogador(miniCosmo3,x,y,+1,0);
                break;
                case 75:case 'a': ///esquerda
                   moverJogador(miniCosmo3,x,y,0,-1);
                break;
                case 77: case 'd': ///direita
                   moverJogador(miniCosmo3,x,y,0,+1);
                break;
            }

         }

          if (miniCosmo3[5][3] == 2 && miniCosmo3[6][5] == 2 && miniCosmo3[4][6] == 2) {
    cout << "Parabens, voce ganhou!" <<endl;
    system ("pause");
    system("cls");
    break; //Nesse If ele vai verificar se as posições das caixas é igual a posição do locais de armazenagem, caso for verdadeiro, ele Declara o jogador como vencedor.

      } //fim do laço do jogo

    }
}

    void mapa2(){
        ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        //IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, ACIMA.

    int microBanII1[10][10]={ 1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,0,0,1,1,1,1,1,
                              1,1,1,0,0,1,1,1,1,1,
                              1,1,1,0,0,1,1,1,1,1,
                              1,1,1,3,2,2,0,1,1,1,
                              1,1,1,0,0,3,0,1,1,1,
                              1,1,1,0,0,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1 };

    //Posi  o inicial do personagem no console
    int x=5, y=6;
    //Vari vel para tecla precionada
    char tecla;

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (microBanII1[i][j]){
                        case 0: cor_texto(8,0); cout<<" "; cor_texto(7,0); break;
                        case 1: cor_texto(8,0); cout<<char(219); cor_texto(7,0); break;
                        case 2: cor_texto(12,0); cout<<char(254); cor_texto(7,0); break;
                        case 3: cor_texto(13,0); cout<<char(5); cor_texto(7,0); break;
                        default: cout<<"-";
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    moverJogador(microBanII1,x,y,-1,0);
                break;
                case 80: case 's': ///baixo
                    moverJogador(microBanII1,x,y,+1,0);
                break;
                case 75:case 'a': ///esquerda
                    moverJogador(microBanII1,x,y,0,-1);
                break;
                case 77: case 'd': ///direita
                    moverJogador(microBanII1,x,y,0,+1);
                break;
            }
         }

            if (microBanII1[5][3] == 2 && microBanII1[6][5] == 2) {
                cout << "Parabens, voce ganhou!" <<endl;
                        system ("pause");
                        system("cls");
                        break;

            } //fim do laço do jogo
        }
    }
    void mapa3(){
        ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        //IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
    ///ALERTA: N O MODIFICAR O TRECHO DE C DIGO, ACIMA.



    int microBanII2[10][10]={ 1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,0,0,0,1,1,1,
                              1,1,1,1,3,1,0,1,1,1,
                              1,1,1,0,0,0,0,1,1,1,
                              1,1,1,0,0,2,0,1,1,1,
                              1,1,1,0,1,2,1,1,1,1,
                              1,1,1,0,0,0,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1 };

    //Posi  o inicial do personagem no console
    int x=4, y=5;
    //Vari vel para tecla precionada
    char tecla;



    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (microBanII2[i][j]){
                        case 0: cor_texto(8,0); cout<<" "; cor_texto(7,0); break;
                        case 1: cor_texto(8,0); cout<<char(219); cor_texto(7,0); break;
                        case 2: cor_texto(12,0); cout<<char(254); cor_texto(7,0); break;
                        case 3: cor_texto(13,0); cout<<char(5); cor_texto(7,0); break;
                        default: cout<<"-";
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    moverJogador(microBanII2,x,y,-1,0);
                break;
                case 80: case 's': ///baixo
                    moverJogador(microBanII2,x,y,+1,0);
                break;
                case 75:case 'a': ///esquerda
                    moverJogador(microBanII2,x,y,0,-1);
                break;
                case 77: case 'd': ///direita
                    moverJogador(microBanII2,x,y,0,+1);
                break;
            }
         }
        if (microBanII2[3][4] == 2 && microBanII2[6][5] == 2) {
                cout << "Parabens, voce ganhou!" <<endl;
                system ("pause");
                system("cls");
            break;
            } //fim do laço do jogo
        }
    }

void escolhermapa(){

    srand(time(NULL));

        int escolha;

        cout << "\nEscolha um mapa: " << endl;
        cout << "1. Mini Cosmo 3" << endl;
        cout << "2. Micro Ban II 1" << endl;
        cout << "3. Micro Ban II 2" << endl;
        cout << "4. Sortear aleatoriamente" << endl;
        cin >> escolha;

        if (escolha == 4) {
        escolha = rand() % 3 + 1; // sorteia um número entre 1 e 3
        cout << "O mapa sorteado foi o " << escolha << endl;
        }
        switch (escolha) {
        case 1:
            system ("pause");
            system("cls");
            mapa1();
            // código para carregar o mapa 1
            break;
        case 2:
            system ("pause");
            system("cls");
            mapa2();
            // código para carregar o mapa 2
            break;
        case 3:
            system ("pause");
            system("cls");
            mapa3();
            // código para carregar o mapa 3
                    break;
                default:
                    cout << "Opção inválida" << endl;
                }
            }

    void menu(){
        int opcao;
        bool jogando = true;

    while (jogando) {
        cout << " ----    ------   -   -   ------   -----       -      --    -\n--       -    -   -  -    -    -   -    -     ---     ---   -\n ----    -    -   - -     -    -   -----     -- --    - --  -\n    --   -    -   - -     -    -   ------   --   --   -  -- -\n   --    -    -   -  -    -    -   -     -  - --- -   -   ---\n----     ------   -   -   ------   ------   -     -   -    --\n\n";
        cout << "    Menu" << endl << endl;
        cout << "Selecione uma opcao:" << endl;
        cout << "1. Novo jogo" << endl;
        cout << "2. Continuar" << endl;
        cout << "3. Sobre" << endl;
        cout << "4. Fim" << endl;
        cin >> opcao;

        switch(opcao) {
            case 1:
                escolhermapa();
                // Iniciar novo jogo
                break;
            case 2:
                // Continuar jogo salvo
                break;
            case 3:
                cout << "\nJogo desenvolvido por: Luiggi de Sousa Lechinski \nData: abril/2023 \nOrientador: Thiago Felski Pereira - Algoritmos e Programacao II\n\n";
                cout << "Sokoban - Regras e Como Jogar:\n" <<"O jogo e constituido por um agente, no qual esse se localiza dentro de um armazem de diferentes tamanhos \ne formas variadas (mapas). Seu objetivo e mover as caixas, que devem ser empurrados para as areas \nde armazenamento (marcadas no mapa), o jogo acaba quando o jogador empurrar todas as caixas para os \nlocais de armazenamento.  \nRegras: \n1 - O jogador nao pode puxar os blocos ou empurrar para o lado.\n2 - Nao pode empurrar mais do que um bloco por vez,\n3 - O jogador nao pode ocupar a mesma posicao que um bloco ou parede, em um mesmo instante de tempo.\n\n";
                system ("pause");
                system("cls");
                // Exibir informações sobre o jogo
                break;
            case 4:
                // Finalizar o programa
                jogando = false;
                break;
            default:
                cout << "Opcao invalida!" << endl;
                system ("pause");
                system("cls");
                break; // Caso o jogador selecione um numero diferente das opções do menu.
            }
        }
    }



    int main()
    {

    menu();

    return 0;
} //fim main
