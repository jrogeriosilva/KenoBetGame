//
// Created by joser on 03/07/2021.
//

#ifndef GAMEKENOBET_KENOBET_H
#define GAMEKENOBET_KENOBET_H


#include <vector>

constexpr auto MAX_SPOTS(15);
constexpr auto LIMIT(80);

class KenoBet {
private:
    float money; // Dinheiro Inicial do Jogador

    int playerRounds; // Quantidade de Rounds que o jogador ira participar

    float moneyBet; // Dinheiro que o jogador ira apostar por rodada

    std::vector<int> balls; // Bolas sorteadas

    std::vector<int> spots; // Numeros que o Jogador Escolheu

    std::vector<int> hits; // Numeros que o Jogador acertou

    std::vector<std::vector<float>> payoutsTable = {
            {0, 3},
            {0, 1, 9},
            {0, 1, 2, 16},
            {0, 0.5, 2, 6, 12},
            {0, 0.5, 1, 3, 15, 50},
            {0, 0.5, 1, 2, 3, 30, 75},
            {0, 0.5, 0.5, 1, 6, 12, 36, 100},
            {0, 0.5, 0.5, 1, 3, 6, 19, 90, 720},
            {0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200},
            {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800},
            {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000},
            {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000},
            {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000},
            {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500},
            {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}
    };
    
public:
    // ----------------------Getters and Getters-----------------------

    /*!
     * @brief Incrementa ou decrementa o dinheiro do jogador
     * @param _money
     */
    void incrementMoney(float _money);

    /*!
     *
     * @return moneyBet Dinheiro que o jogador possui no momento
     */
    float getMoneyBet() const;

    /*!
     *
     * @param _moneyBet
     */
    void setMoneyBet(float _moneyBet);


    /*!
     *
     * @return vetor contendo o estado atual dos números dá maquina de sorteio
     */
    std::vector<int> getBalls();

    /**
     *
     * @return vetor de números que o usuário apostou
     */
    std::vector<int> getSpots();

    /*!
     * @param _spot elemento apara ser inserido no vetor de apostas do jogador.
     */
    void setSpots(int _spot);

    /*!
     *
     * @return Vetor contendo acetos do jogador
     */
    std::vector<int> getHits() const;

    /*!
     *
     * @return Dinheiro atual do jogador
     */
    float getMoney() const;

    /*!
     *
     * @param _money Dinheiro
     */
    void setMoney(float _money);

    /*!
     *
     * @return Quantidade rodadas que o jogador ira jogar.
     */
    int getPlayerRounds() const;

    /*!
     *
     * @param playerRounds Quantidade de rounds que o jogador ira jogar.
     */
    void setPlayerRounds(int playerRounds);

    /*!
     *
     * @return Tamanho do vetor dos elementos escolhidos pelo jogador
     */
    std::size_t getNumChosen() const;

    /*!
     *
     * @return Tamanho do vetor dos elementos que o jogador acertou
     */
    std::size_t getNumHits();

    /*!
     *
     * @param _hits
     * @return inteiro fator de multiplicação para o premio do jogador
     */
    float getRewardMultiplier(int _hits);


    // ----------------------Methods------------------------------------

    /**
     * @brief Adiciona números a aposta do jogador
     * @param _spot Número que será inserido na aposta do jogador;
     */
    void addNumber(int _spot);


    /**
     * @brief Sorteia 20 Números dentre 80 Números.
     * E salva no vetor balls do objeto.
     */
    void randomizeBalls();

    /**
     * Calcula os números que o jogador a certou e salva no Vetor hits do objeto.
     */
    void computeHits();

    /**
     * Restaura os Vetores de Acertos e numeros sorteadas.
     */
    void reset();
};


#endif //GAMEKENOBET_KENOBET_H
