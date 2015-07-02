#include<stdio.h>
#include<iostream>

#define CONSUMO_BAIXO 1
#define CONSUMO_MEDIO 2
#define CONSUMO_ALTO 3
#define ALTO_RISCO 5
#define MEDIO_RISCO 6
#define BAIXO_RISCO 7
#define SEM_RISCO 8
#define OSCILACAO_DESCENDENTE 10
#define OSCILACAO_NORMAL 11
#define OSCILACAO_ASCENDENTE 12

typedef struct customer{
    std::string code;
    unsigned int *months;
} Customer;

//Classe com os atributos Customer, os respectivos consumo maximo e minimo, e os métodos que realizam as verificações
class Checker {
    Customer customer;
    unsigned int consumer_max;
    unsigned int consumer_min;
  public:
    Checker();
    void inline check();
    void inline check_consumer_classification();
    void inline check_risc();
    void inline check_oscillation();
    void inline check_anomaly();
    void inline check_consumer_max();
    void inline check_consumer_min();
}


//Implementação do construtor da classe
void Checker::Checker( Customer customer ) {
    this->customer = customer;
}

void Checker::checke_consumer_max() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] > consumer_max ) {
            consumer_max= this->customer.months[i];
        }
    }
}

void Checker::checke_consumer_min() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.months[i] < consumer_min ) {
            consumer_m= this->customer.months[i];
        }
    }
}

void Checker::checke() {

}

void Checker::checke_consumer_classification() {
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
            println("Mes com valor de consumo null!");
        }
    }
}

void Checker::checke_risc() {
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
            println("Mes com valor de consumo null!");
        }
    }
}

void Checker::checke_oscillation() {
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
            println("Mes com valor de consumo null!");
        }
    }
}

void Checker::checke_anomaly() {

}
