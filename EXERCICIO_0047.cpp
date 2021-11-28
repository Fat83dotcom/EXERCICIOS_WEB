/*
DESAFIO: Faça um jogo no qual o computador desafia dois usuários para ver quem tem
mais memória. O jogo deve gerar um número de 0 a 9 e apresentar ao jogador 1 durante
5 segundos. Depois deve repetir este procedimento para o jogador 2. Em seguida, ele
deve pedir ao jogador 1 para informar o número escolhido, e após pedir ao jogador 2 para
fazer a mesma coisa. Na segunda rodada, o computador deve gerar mais um número
entre 0 e 9, que será ’concatenado’ à direita do primeiro número. Então repetiremos o
procedimento de exibição e teste de memorização para os dois usuários. O programa
deve continuar adicionando números (casas adicionadas ao final do número) até que
um dos dois jogadores não consiga mais memorizar perfeitamente o número. Para con-
cluir, o programa deve informar qual dos dois jogadores ganhou, quantas casas foram
memorizadas ao total, e em que casa foi que o jogador perdedor errou (primeira casa
errada começando da esquerda para a direita). Dicas: procure desenvolver o programa
em módulos; armazene a sequência de números dentro de uma string.
*/
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

#define MAXIMO_NUMEROS 50
#define TEMPO_ESPERA_SEGUNDOS 5

using std::cout;
using std::cin;
using std::endl;
using std::sprintf;


class Jogador {
    private:
    char *concatenados = new char[MAXIMO_NUMEROS];
    int entrada_Concatenada;

    public:
    void recebe_Escolhas_Aleatorias(int *escolha, int contador) {
        sprintf((concatenados + contador), "%d", *escolha);

    }

    void mostra_Dados() {
        cout << concatenados << endl;

    }

    bool verifica_Entrada(int entrada_Jogador) {
        entrada_Concatenada = atoi(concatenados);
        return (entrada_Concatenada == entrada_Jogador) ? true : false;

    }

    void limpa_Memoria() {
        delete[] concatenados;

    }
};

void limparTela() {
    cout << "\x1B[2J\x1B[H";

}

int *geradorAleatorio() {
    
    int numeroAleatorio, *pNumeroAleatorio = &numeroAleatorio;
    unsigned semente = time(0);
    srand(semente);
    numeroAleatorio = rand()%10;

    return pNumeroAleatorio;

}

bool operacaoJogador(Jogador *jogador, int *contador, int numeroJogador){
    int entradaJogador;
    cout << "Jogador " << numeroJogador << ":" << endl;
    cout << "Memorize: \n\n";
    jogador->recebe_Escolhas_Aleatorias(geradorAleatorio(), *contador);
    jogador->mostra_Dados();
    sleep(TEMPO_ESPERA_SEGUNDOS);
    limparTela();
    cout << "Digite o número mostrado na tela: ";
    cin >> entradaJogador;

    return (jogador->verifica_Entrada(entradaJogador)) ? limparTela(), true : false;
   

}

void mensagemFinal(Jogador *JogadorPerdedor,  int *contadorJogadorGanhador, int *contadorJogadorPerdedor, int numeroJogadorGanhador) {
    cout << "Você perdeu, Jogador" << numeroJogadorGanhador <<" ganhou!!" << endl;
    cout << "A sequência correta é: ";
    JogadorPerdedor->mostra_Dados();
    cout << "Você conseguiu memorizar " << *contadorJogadorGanhador << " casas." << endl;
    cout << "O outro jogador conseguiu memorizar " << *contadorJogadorPerdedor << " casas." << endl;
}

int main(int argc, char const *argv[]) {

    Jogador J_1;
    Jogador J_2;
    
    int contador1 = 0, contador2 = 0, *pcontador1, *pcontador2;
    pcontador1 = &contador1;
    pcontador2 = &contador2;

    do{
        
        if (operacaoJogador(&J_1, pcontador1, 1)) {
            contador1++;
        }
        else {
            mensagemFinal(&J_1, pcontador2, pcontador1, 2);
            break;
        }
        if (operacaoJogador(&J_2, pcontador2, 2)) {
            contador2++;
        }
        else {
            mensagemFinal(&J_2, pcontador1, pcontador2, 1);
            break;
        }
        
    } while (1);

    return 0;
}
