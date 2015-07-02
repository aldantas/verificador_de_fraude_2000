#include "checker.hpp"
#include<iostream>

//Implementação do construtor da classe
Checker::Checker() {
}

void Checker::check_max_consumption() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer->months[i] > max_consumption ) {
            max_consumption= this->customer->months[i];
        }
    }
}

void Checker::check_min_consumption() {
    min_consumption = 0;

    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer->months[i] < min_consumption ) {
            min_consumption = this->customer->months[i];
        }
    }
}

void Checker::check(Customer &customer) {
    this->customer = &customer;
    check_max_consumption();
    check_min_consumption();
    check_consumption_classification();
    check_risc();
    check_oscillation();
    check_anomaly();
    check_fraudulent();
}

void Checker::check_consumption_classification() {

    for ( int i = 0; i < 12; i++ ) {
        if ((this->min_consumption <= this->customer->months[i])
                && (this->customer->months[i] <= ((this->max_consumption - this->min_consumption)/3))){
            this->consumption_classification_months[i]= CONSUMO_BAIXO;
        } else if ((((this->max_consumption - this->min_consumption)/3) < this->customer->months[i] )
                && ( this->customer->months[i] <= (2 * ((this->max_consumption - this->min_consumption)/3)))) {
            this->consumption_classification_months[i]= CONSUMO_MEDIO;
        } else if ((( 2 * ((this->max_consumption - this->min_consumption)/3) ) < this->customer->months[i] )
                && (this->customer->months[i] <= this->max_consumption ) ) {
            this->consumption_classification_months[i]= CONSUMO_ALTO;
        }
    }
}

void Checker::check_risc() {
    float risk_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( i > 2 ) {
            float aux = (float)((this->customer->months[i-3] + this->customer->months[i-2] + this->customer->months[i-1]) / 3);
            risk_index= ((this->customer->months[i] - aux) / aux);
        } else {
            risk_index = 0;
        }
        if ( risk_index < -0.2) {
            this->risc_months[i]= ALTO_RISCO;
        } else if ( (-0.2 <= risk_index) && (risk_index <= 0) ){
            this->risc_months[i]= MEDIO_RISCO;
        } else if ( (0 <= risk_index) && (risk_index < 0.2)){
            this->risc_months[i]= BAIXO_RISCO;
        } else if ( 0.2 <= risk_index) {
            this->risc_months[i]= SEM_RISCO;
        }
    }
}

void Checker::check_oscillation() {
    double oscillation_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( i > 0 ) {
            oscillation_index= ((double)this->customer->months[i] - (double)this->customer->months[i-1]) / (double)this->customer->months[i-1];
        } else {
            oscillation_index = 0;
        }
        if ( oscillation_index < -0.15) {
            this->oscillation_months[i]= OSCILACAO_DESCENDENTE;
        } else if ( (-0.15 <= oscillation_index) && (oscillation_index <= 0.20) ){
            this->oscillation_months[i]= OSCILACAO_NORMAL;
        } else if (0.20 <= oscillation_index){
            this->oscillation_months[i]= OSCILACAO_ASCENDENTE;
        }
    }
}

void Checker::check_anomaly() {
    for ( int i = 0; i < 12; i++ ) {
        if ( ((this->risc_months[i] == ALTO_RISCO) || (this->risc_months[i] == MEDIO_RISCO)) &&
             (this->consumption_classification_months[i] == CONSUMO_BAIXO) && (this->oscillation_months[i] == OSCILACAO_DESCENDENTE) ) {
            this->customer->months[i]= TEM_ANOMALIA;
        } else {
            this->customer->months[i]= NAO_TEM_ANOMALIA;
        }
    }
}

void Checker::check_fraudulent() {
    this->customer->isFraudulent = false;
    for ( int i = 0; i < 12; i++ ) {
        if (this->customer->months[i] == TEM_ANOMALIA){
            this->customer->isFraudulent = true;
            break;
        }
    }
}
