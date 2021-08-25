#include "include/Functions.h"
#include "include/KenoBet.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>
#include <string>
#include <iomanip>
#include <algorithm>


using std::cout;
using std::endl;


int main(int argc, char *argv[]) {

    setlocale(LC_ALL,"");
    welcome();
    std::string fileName = argv[1];
    std::ifstream ifs(fileName);
    cout << line() << ">>> Carregando " << fileName << ", por favor aguarde...";

    if (!ifs) {
        std::cerr << ">>> Não foi possível Ler o Arquivo  \n";
        ifs.close();
        exit(1);
    }

    //String contendo os dados da Aposta
    std::string player_data(
            (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
    ifs.close();

    std::stringstream stringStream_player(player_data);

    KenoBet kb;
    float initialMoney = 0;
    int playerRounds = 0;

    stringStream_player >> initialMoney;
    stringStream_player >> playerRounds;

    kb.setMoney(initialMoney);
    kb.setPlayerRounds(playerRounds);
    kb.setMoneyBet(kb.getMoney()/kb.getPlayerRounds());

    // Carregando Numeros da Sorte
    int number;
    while (stringStream_player >> number) {
        kb.addNumber(number);
    }

    // Verificações de Erros Adicionais

    if (initialMoney <= 0){
        std::cerr << "Não é Possível apostar R$ 0\n";
        exit(1);
    }

    if (kb.getSpots().size() == 0) {
        std::cerr << ">>> VocÊ deve apostar ao menos um número\n";
        exit(1);
    }

    if (playerRounds <= 0){
        std::cerr << ">>> VocÊ deve apostar um número de vezes maior que 0";
        exit(1);
    }





    cout << line() << ">>> Arquivo de Apostas Lido Com sucesso"
         << line() <<
         "Você Apostará um Total de: R$ " << kb.getMoney() << endl;

    cout << "Jogará um Total de " << kb.getPlayerRounds() << " rodadas "
         << "apostando R$ " << kb.getMoneyBet() << " por rodada" << line();

    cout << "Seus Numeros da Sorte sao: " ;
    for (int & it : kb.getSpots()){
        cout  << '[' << it << ']';
    }
    cout << "\n#===========================INICIANDO RODADAS==================================\n";
    for (int i = 0; i < kb.getPlayerRounds(); ++i) {
        cout << "\n===============================================================================\n"
                "Rodada #" << i + 1 << " de " << kb.getPlayerRounds() << endl <<
             "Saldo: R$ " << kb.getMoney() << endl;

        cout << "Nessa rodada você apostará R$" << kb.getMoneyBet();

        //Reduzir Dinheiro
        kb.incrementMoney(-kb.getMoneyBet());

        //Sorteando
        kb.randomizeBalls();
        cout << line();
        cout << "Os Numeros sorteados foram:" << endl;
        for (int & it : kb.getBalls()){
            cout  << '[' << it << ']';
        }
        cout << line();

        //Calculando Acertos

        if (kb.getNumHits() > 0){
            cout << "Você Acertou os Número(s): ";
            for (int & it : kb.getHits()){
                cout  << '[' << it << ']';
            }

            cout << endl;
            float earn_rate = kb.getRewardMultiplier(kb.getNumHits());
            kb.incrementMoney(
                    earn_rate * (kb.getMoneyBet())
            );
            cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                    "Nessa rodada você acertou um total de " << kb.getNumHits() << " números" << endl
                 << "Sua taxa de retorno é " << earn_rate
                 << ", ganhando assim um total de R$" << earn_rate * kb.getMoneyBet()
                 << endl
                 << "Seu novo saldo agora é: R$" << kb.getMoney() <<
                  "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

        }else{
            cout << "Que Pena você não ganhou :(" << endl;
        }

        if (kb.getMoney() < 0.01){
            cout << "Seu Saldo final é de R$ 0" << endl;
        }else{
            cout << "Seu Saldo final é de R$ " << kb.getMoney() << endl;
        }
        kb.reset();
    }
    cout << endl << line();

    cout << "<<< Fim das rodadas ";
    cout << line();
    cout << "Você apostou um total de R$ " << initialMoney << endl;
    if (kb.getMoney() < 0.01){
        cout << "Seu Saldo final é de R$ 0" << endl;
    }else{
    cout << "Seu Saldo final é de R$ " << kb.getMoney() << endl;
    }
    if(kb.getMoney() < initialMoney){
        cout << "Que pena :( Você perdeu R$ " << (-1)*(kb.getMoney() - initialMoney) << endl;
    }else{
        cout << "IRRUUU!! :( Você Ganhou R$ " << (kb.getMoney() - initialMoney) << endl;
    }


    cout << "Você está saindo do Jogo com R$ " << (kb.getMoney() - initialMoney);

    cout << "\n============================== Volte Sempre ===================================\n";


    return 0;
}
