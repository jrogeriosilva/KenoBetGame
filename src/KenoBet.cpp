//
// Created by joser on 03/07/2021.
//

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "../include/KenoBet.h"

#include <random>


void KenoBet::randomizeBalls() {
    std::random_device r;
    balls.clear();

    for (int i = 0; i < LIMIT;i++) {
        balls.push_back(i+1);
    }

    std::shuffle(balls.begin(),balls.end(),std::default_random_engine(r()));
    balls.resize(20);
    std::sort(balls.begin(),balls.end());

    this->computeHits();
}

std::vector<int> KenoBet::getBalls() {
    return this->balls;
}

std::size_t KenoBet::getNumChosen() const {
    return this->spots.size();
}

void KenoBet::setSpots(int _spot) {
    this->spots.push_back(_spot);
}

void KenoBet::addNumber(int _spot) {
    if (!(std::find(spots.begin(), spots.end(), _spot) != spots.end()) &&
        this->spots.size() < MAX_SPOTS && _spot > 0 && _spot < 80) {
        setSpots(_spot);
        std::sort(this->spots.begin(), this->spots.end());
    }else if (this->spots.size()+1 > MAX_SPOTS) {
        std::cerr << ">>> Foram inseridos " << this->spots.size()+1 << ". Só é permitido no Máximo 15 Números\n";
        exit(1);
    }else if (_spot > 80) {
        std::cerr << ">>> Foi inserido -> " << _spot << ". Só é permitido números com Valor máximo de 80\n";
        exit(1);
    }else if(_spot <= 0){
        std::cerr << ">>> -> " << _spot << " Não é um Número da sorte válido\n";
        exit(1);
    }else{
        std::cerr << _spot << " <- É um valor repetido no seu Cartao de Aposta\n";
        std::cerr << "Não são permitidos números da sorte repetidos";
        exit(1);
    }

}

std::vector<int> KenoBet::getSpots() {
    return this->spots;
}

float KenoBet::getMoney() const {
    return this->money;
}

void KenoBet::setMoney(float _money) {
    this->money = _money;
}

int KenoBet::getPlayerRounds() const {
    return this->playerRounds;
}

void KenoBet::setPlayerRounds(int _playerRounds) {
    this->playerRounds = _playerRounds;
}

std::vector<int> KenoBet::getHits() const {
    return this->hits;
}

void KenoBet::computeHits() {
    std::vector<int>::iterator it, st;
    std::vector<int> v(balls.size() + spots.size());
    it = std::set_intersection(balls.begin(),
                               balls.end(),
                               spots.begin(),
                               spots.end(),
                               v.begin()
    );

    for (st = v.begin(); st != it; ++st) {
        hits.push_back(*st);
    }


}

std::size_t KenoBet::getNumHits() {
    return this->hits.size();
}


float KenoBet::getRewardMultiplier(int _hits) {
    return this->payoutsTable[this->getNumChosen() - 1][_hits];
}

void KenoBet::reset() {
    spots.clear();
    hits.clear();
}

float KenoBet::getMoneyBet() const {
    return this->moneyBet;
}

void KenoBet::setMoneyBet(float _moneyBet) {
    this->moneyBet = _moneyBet;
}

void KenoBet::incrementMoney(float _money) {
    this->money += _money;
}


