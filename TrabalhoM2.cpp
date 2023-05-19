#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>




using namespace std;
void menu(int m[10][10], int &x, int &y, bool &jogando, ifstream &arquivo, int &passos);
struct Funcionalidades;

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

struct Sokobanengine {
    int x,y;
    int passos;
    int escolha;
    bool jogando=false;
    ifstream arquivo;
    ofstream arquivo2;


    void posicaoxy( int column, int line )
    {
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
    }

    void mostrarCursor(bool showFlag)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO     cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
    }
    void cor_texto (int cor, int cordois) {

        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(out, cor);
    }
};

    struct Ranking {
    string nome;
    ofstream arquivo2;


    void lerRank (ifstream &arquivo){

    string frase;
    int escolhateste;

    cout << "\n1. Mini Cosmo 3 \n2. Micro Ban II 1 \n3. Micro Ban II 2\n Escolha o ranking de qual mapa deseja ver: ";
    cin >> escolhateste;



        switch(escolhateste){
        case 1:
        system ("cls");
        cout << "\nRanking Mini Cosmo 3: \n";
        arquivo.open ("ranking1.txt");
        while (arquivo.eof()== false){
        getline(arquivo,frase);
        cout <<frase << "\n";
        }
        arquivo.close();
        system ("pause");
        break;

        case 2:
        system ("cls");
        cout << "\nRanking Micro Ban II 1: \n";
        arquivo.open ("ranking2.txt");
        while (arquivo.eof()== false){
        getline(arquivo,frase);
        cout <<frase << "\n";
        }
        arquivo.close();
        system ("pause");
        break;

        case 3:
        system ("cls");
        cout << "\nRanking Micro Ban II 2: \n";
        arquivo.open ("ranking3.txt");
        while (arquivo.eof()== false){
        getline(arquivo,frase);
        cout <<frase << "\n";
        }
        arquivo.close();
        system ("pause");
        break;
        }
        system ("cls");

    }

    void adicionarJogadorRank (string &nome, int &passos, ofstream& arquivo2, int &escolha){

        Sokobanengine jogo1;
        cout << "Digite seu nome: ";
        cin >> nome;
        int TAM=1;
        int *vet;
        vet = new int [TAM];

        switch(escolha){
            case 1:

                   for (int i=0; i< TAM; i++){
            arquivo2.open ("ranking1.txt",ios_base::app);
            arquivo2 << nome << " " << passos << "\n";
            arquivo2.close();
                   }
            TAM ++;
                break;
                case 2:

                   for (int i=0; i< TAM; i++){
            arquivo2.open ("ranking2.txt",ios_base::app);
            arquivo2 << nome << " " << passos << "\n";
            arquivo2.close();
                   }
            TAM ++;
            break;
            case 3:

            for (int i=0; i< TAM; i++){
            arquivo2.open ("ranking3.txt",ios_base::app);
            arquivo2 << nome << " " << passos << "\n";
            arquivo2.close();
            }
            TAM ++;

            break;
            default:
            cout << "Opção inválida" << endl;
            } //fim switch

        }

    };


 struct Funcionalidades {


    void escrevematriz (int m[10][10], int &x, int &y, ifstream &arquivo){
        arquivo >> x >>y;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
            arquivo >> m[i][j];
            }
        }
    }

    void imprimir(int m[10][10], int &x, int &y, int &passos){
        Sokobanengine jogo1;

        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0: jogo1.cor_texto(8,0); cout<<" "; jogo1.cor_texto(7,0); break; //Espaço Livre
                        case 1: jogo1.cor_texto(8,0); cout<<char(219); jogo1.cor_texto(7,0);  break; // Parede
                        case 2: jogo1.cor_texto(13,0); cout<<char(254); jogo1.cor_texto(7,0);  break; // Caixas
                        case 3: jogo1.cor_texto(11,0); cout<<char(219); jogo1.cor_texto(7,0);  break; // Espaço para Entregar caixa
                        case 4: jogo1.cor_texto(1,0); cout<<char(254); jogo1.cor_texto(7,0);  break; // Caixa No Local de Entrega
                        default: cout<<"-";
                    } //fim switch
                }
            }
            cout<<"\n";

        } //fim for mapa
        cout <<"\n\nNumero de Passos: " <<passos;
        cout <<"\nCaso queira retornar para o menu aperte a tecla Q";

    } //fim imprime


    void movimentar (int m[10][10], int &x, int &y, bool jogando, ifstream &arquivo, int &passos, int &escolha, ofstream& arquivo2) {
        char tecla;
        Sokobanengine jogo1;
        Ranking jogador1;
        arquivo2.open ("jogadas.txt",ios_base::app);

     if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    if(m[x-1][y]==0 or m[x-1][y]==3){
                        x--; passos++;
                        arquivo2 << x << " " << y << "\n";
                    }
                    ///caixa livre -> livre
                    else if(m[x-1][y]==2 and m[x-2][y]==0){
                        x--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x-1][y]=2;  ///a frente do movimento

                    }
                    ///caixa fim -> livre
                    else if(m[x-1][y]==4 and m[x-2][y]==0){
                        x--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x-1][y]=2;  ///a frente do movimento

                    }
                    ///caixa livre -> fim
                    else if(m[x-1][y]==2 and m[x-2][y]==3){
                        x--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x-1][y]=4;  ///a frente do movimento

                    }
                    ///caixa fim -> fim
                    else if(m[x-1][y]==4 and m[x-2][y]==3){
                        x--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x-1][y]=4;  ///a frente do movimento

                    }
                break;
                case 80: case 's': ///baixo
                    if(m[x+1][y]==0 or m[x+1][y]==3){
                        x++; passos++;
                        arquivo2 << x << " " << y << "\n";;
                    }
                    ///caixa livre -> livre
                    else if(m[x+1][y]==2 and m[x+2][y]==0){
                        x++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x+1][y]=2;  ///a frente do movimento

                    }
                    ///caixa fim -> livre
                    else if(m[x+1][y]==4 and m[x+2][y]==0){
                        x++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x+1][y]=2;  ///a frente do movimento

                    }
                    ///caixa livre -> fim
                    else if(m[x+1][y]==2 and m[x+2][y]==3){
                        x++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x+1][y]=4;  ///a frente do movimento

                    }
                    ///caixa fim -> fim
                    else if(m[x+1][y]==4 and m[x+2][y]==3){
                        x++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x+1][y]=4;  ///a frente do movimento

                    }
                break;
                case 75:case 'a': ///esquerda
                     if(m[x][y-1]==0 or m[x][y-1]==3){
                        y--; passos++;
                        arquivo2 << x << " " << y << "\n";
                    }
                    ///caixa livre -> livre
                    else if(m[x][y-1]==2 and m[x][y-2]==0){
                        y--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x][y-1]=2;  ///a frente do movimento

                    }
                    ///caixa fim -> livre
                    else if(m[x][y-1]==4 and m[x][y-2]==0){
                        y--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x][y-1]=2;  ///a frente do movimento

                    }
                    ///caixa livre -> fim
                    else if(m[x][y-1]==2 and m[x][y-2]==3){
                        y--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x][y-1]=4;  ///a frente do movimento

                    }
                    ///caixa fim -> fim
                    else if(m[x][y-1]==4 and m[x][y-1]==3){
                        y--; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x][y-1]=4;  ///a frente do movimento

                    }

                break;
                case 77: case 'd': ///direita
                if(m[x][y+1]==0 or m[x][y+1]==3){
                        y++; passos++;
                        arquivo2 << x << " " << y << "\n";
                    }
                    ///caixa livre -> livre
                    else if(m[x][y+1]==2 and m[x][y+2]==0){
                        y++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x][y+1]=2;  ///a frente do movimento

                    }
                    ///caixa fim -> livre
                    else if(m[x][y+1]==4 and m[x][y+2]==0){
                        y++; passos++;
                       arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x][y+1]=2;  ///a frente do movimento

                    }
                    ///caixa livre -> fim
                    else if(m[x][y+1]==2 and m[x][y+2]==3){
                        y++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=0;  ///após o movimento
                        m[x][y+1]=4;  ///a frente do movimento

                    }
                    ///caixa fim -> fim
                    else if(m[x][y-1]==4 and m[x][y-2]==3){
                        y++; passos++;
                        arquivo2 << x << " " << y << "\n";
                        m[x][y]=3;  ///após o movimento
                        m[x][y+1]=4;  ///a frente do movimento

                    }

                break;
                case'q':
                system("cls");
                cout << "Retornando para o menu!" <<endl;
                char tecla=getch();
                system("cls");
                menu(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                break;
            }

         } arquivo2.close();
    }


    void escolhermapa(int m[10][10], int &x, int &y, ifstream &arquivo, int &escolha){

    srand(time(NULL));


        int n_itens=3;

        cout << "\nEscolha um mapa: " << endl;
        cout << "1. Mini Cosmo 3" << endl;
        cout << "2. Micro Ban II 1" << endl;
        cout << "3. Micro Ban II 2" << endl;
        cout << "4. Sortear aleatoriamente" << endl;
        cin >> escolha;

        if (escolha == 4) {
        escolha = rand() % n_itens + 1; // sorteia um número entre 1 e 3
        cout << "O mapa sorteado foi o " << escolha << endl;
        system ("pause");
        }
        switch(escolha){
            case 1:

                   arquivo.open ("mapa1.txt");
                   escrevematriz(m, x, y, arquivo);
                   arquivo.close();



                break;
                case 2:

                   arquivo.open ("mapa2.txt");
                   escrevematriz(m, x, y, arquivo);
                   arquivo.close();


            break;
            case 3:

                   arquivo.open ("mapa3.txt");
                   escrevematriz(m, x, y, arquivo);
                   arquivo.close();

            break;
            default:
            cout << "Opção inválida" << endl;
            } //fim switch
        }

        bool vitoria (int m[10][10]){
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                if (m[i][j]==3){
                    return false;
                }
            }
        }
        return true;
    }


    void sokoban(int m[10][10], int &x, int &y, bool &jogando, ifstream &arquivo, int &passos, int &escolha, ofstream& arquivo2){

    Sokobanengine jogo1;
    Ranking jogador1;
    arquivo2.open ("jogadas.txt");
    arquivo2.close();


        while (!vitoria(m)){

                imprimir(m, x, y, passos);
                movimentar(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                jogo1.posicaoxy(0,0); ///posiciona a escrita no console no eixo x,y. A posição 0,0 é a do canto superior esquerdo.


            }


            jogando=false;

            system("cls");
            cout<<"\nParabens Voce venceu!\nVoce completou o Mapa em " <<passos <<" passos!\n";
            jogador1.adicionarJogadorRank(jogador1.nome, passos, jogador1.arquivo2, escolha);
            passos = 0;
            cout <<"\nAperte qualquer tecla para retornar ao menu.\n";
            char tecla=getch();
            system("cls");
            menu(m, x, y, jogando, arquivo, passos, escolha, arquivo2);


    }
    void sobre(int m[10][10], int &x, int &y, bool &jogando, ifstream &arquivo, int &passos, int &escolha, ofstream& arquivo2){
        cout <<"\n\nJogo desenvolvido por: Luiggi de Sousa Lechinski \nData: Abril/2023 \nOrientador: Thiago Felski Pereira - Algoritmos e Programacao II\n\n";
        cout <<"\n\nSokoban - Regras e Como Jogar:\n" <<"O jogo e constituido por um agente, no qual esse se localiza dentro de um armazem de diferentes tamanhos \ne formas variadas (mapas). Seu objetivo e mover as caixas, que devem ser empurrados para as areas \nde armazenamento (marcadas no mapa), o jogo acaba quando o jogador empurrar todas as caixas para os \nlocais de armazenamento.  \nRegras: \n1 - O jogador nao pode puxar os blocos ou empurrar para o lado.\n2 - Nao pode empurrar mais do que um bloco por vez,\n3 - O jogador nao pode ocupar a mesma posicao que um bloco ou parede, em um mesmo instante de tempo.\n\n";
        char tecla=getch();
        system("cls");
        menu(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
    }

    void menu(int m[10][10], int &x, int &y, bool &jogando, ifstream &arquivo, int &passos, int &escolha, ofstream& arquivo2){

        Sokobanengine jogo1;
        Ranking jogador1;
        int opcao;

        system("cls");
        cout << " ----    ------   -   -   ------   -----       -      --    -\n--       -    -   -  -    -    -   -    -     ---     ---   -\n ----    -    -   - -     -    -   -----     -- --    - --  -\n    --   -    -   - -     -    -   ------   --   --   -  -- -\n   --    -    -   -  -    -    -   -     -  - --- -   -   ---\n----     ------   -   -   ------   ------   -     -   -    --\n\n";
        cout << "    Menu" << endl << endl;
        cout << "Selecione uma opcao: \n1. Novo jogo \n2. Continuar \n3. Sobre \n4. Ranking \n5. Fim" << endl;
        cin >> opcao;

        switch(opcao) {
            case 1:
                jogando = true;
                passos = 0;
                system("cls");
                escolhermapa(m, x, y, arquivo, escolha);
                system("cls");
                sokoban(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                // Iniciar novo jogo
                break;
            case 2:
                if(jogando== true){
                    system ("cls");
                    sokoban(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                } else {
                    jogando = true;
                    passos = 0;
                    system("cls");
                    escolhermapa(m, x, y, arquivo, escolha);
                    system("cls");
                    sokoban(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                }// Continuar jogo salvo

                break;
            case 3:
                system("cls");
                sobre(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                break;
            case 4:
                jogador1.lerRank(arquivo);
                menu(m, x, y, jogando, arquivo, passos, escolha, arquivo2);
                break;
            case 5:
                exit(0);
            default:
                cout << "Opcao invalida!" << endl;
                system ("pause");
                system("cls");
                break; // Caso o jogador selecione um numero diferente das opções do menu.
            }
            system("cls");
        }

 };

int main()
{
    int m[10][10];
    Sokobanengine jogo1;
    Funcionalidades jogar;
    Ranking jogador1;

    jogo1.mostrarCursor(FALSE);

    jogar.menu(m, jogo1.x, jogo1.y, jogo1.jogando, jogo1.arquivo, jogo1.passos, jogo1.escolha, jogador1.arquivo2);

    return 0;
}
