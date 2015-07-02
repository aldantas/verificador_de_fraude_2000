#include "checker.hpp"
/* #include "customer.h" */
#include<iostream>


//Implementação do construtor da classe
Checker::Checker( Customer customer ) {
    this->customer = customer;
}

void Checker::check_consumer_max() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] > consumer_max ) {
            consumer_max= this->customer.months[i];
        }
    }
}

void Checker::check_consumer_min() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] < consumer_min ) {
            consumer_m= this->customer.months[i];
        }
    }
}

void Checker::check() {

}

void Checker::check_consumer_classification() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] != null ) {
            if ((this->consumer_min <= this->customer.months[i])
                && (this->customer.months[i] <= ((this->consumer_max - this->consumer_min)/3) ) {

            } else if ((((this->consumer_max - this->consumer_min)/3) < this->customer.months[i] )
                && ( this->customer.months[i] <= (2 * ((this->consumer_max - this->consumer_min)/3)))) {

            } else if ((( 2 * ((this->consumer_max - this->consumer_min)/3) ) < this->customer.months[i] )
                && (this->customer.months[i] <= this->consumer_max ) ) {

            }
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_risc() {
    float risk_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] != null ) {
            if ( i > 3 ) {
                int aux = ((this->customer.months[i-3] + this->customer.months[i-2] + this->customer.months[i-1]) / 3);
                risk_index= ((this->customer.months[i] - aux) / aux) * 1;
            } else {
                risk_index = 0;
            }
            if ( risk_index < -0.2) {

            } else if ( (-0.2 <= risk_index) && (risk_index <= 0) ){

            } else if ( (0 <= risk_index) && (risk_index < 0.2)){

            } else if ( 0.2 <= risk_index) {

            }
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_oscillation() {
    float oscillation_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] != null ) {
            if ( i > 1 ) {
                oscillation_index= ((this->customer.months[i] - this->customer.months[i-1]) / this->customer.months[i-1]) * 1;
            } else {
                oscillation_index = 0;
            }
            if ( oscillation_index < -0.15) {

            } else if ( (-0.15 <= oscillation_index) && (oscillation_index <= 0.20) ){

            } else if (0.20 <= oscillation_index){

            }
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_anomaly() {

}
