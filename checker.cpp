#include "checker.hpp"
#include<iostream>

//Implementação do construtor da classe
Checker::Checker( Customer customer ) {
    this->customer = customer;
}

void Checker::check_consumer_max() {
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.t.months[i] > consumer_max ) {
            consumer_max= this->customer.t.months[i];
        }
    }
}

void Checker::check_consumer_min() {
    consumer_min = 0;

    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.t.months[i] < consumer_min ) {
            consumer_min = this->customer.t.months[i];
        }
    }
}

void Checker::check() {
	check_consumer_max();
	check_consumer_min();
	check_consumer_classification();
	check_risc();
	check_oscillation();
	check_anomaly();
	check_fraudulent();
}

void Checker::check_consumer_classification() {

    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.t.months[i] != NULL ) {
            if ((this->consumer_min <= this->customer.t.months[i])
                && (this->customer.t.months[i] <= ((this->consumer_max - this->consumer_min)/3))){
				this->consumer_classification_months[i]= CONSUMO_BAIXO;  
            } else if ((((this->consumer_max - this->consumer_min)/3) < this->customer.t.months[i] )
                && ( this->customer.t.months[i] <= (2 * ((this->consumer_max - this->consumer_min)/3)))) {
				this->consumer_classification_months[i]= CONSUMO_MEDIO;  
            } else if ((( 2 * ((this->consumer_max - this->consumer_min)/3) ) < this->customer.t.months[i] )
                && (this->customer.t.months[i] <= this->consumer_max ) ) {
				this->consumer_classification_months[i]= CONSUMO_ALTO;  
            }
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_risc() {
    float risk_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.t.months[i] != NULL) {
            if ( i > 3 ) {
                int aux = ((this->customer.t.months[i-3] + this->customer.t.months[i-2] + this->customer.t.months[i-1]) / 3);
                risk_index= ((this->customer.t.months[i] - aux) / aux) * 1;
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
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_oscillation() {
    float oscillation_index= 0;
    for ( int i = 0; i < 12; i++ ) {
        if ( this->customer.t.months[i] != NULL ) {
            if ( i > 1 ) {
                oscillation_index= ((this->customer.t.months[i] - this->customer.t.months[i-1]) / this->customer.t.months[i-1]) * 1;
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
        } else {
            std::cout << "Mes com valor de consumo null!" << std::endl;
        }
    }
}

void Checker::check_anomaly() {
	for ( int i = 0; i < 12; i++ ) {
        if (((this->consumer_classification_months[i] == CONSUMO_BAIXO) && (this->risc_months[i] == ALTO_RISCO) && (this->oscillation_months[i] == OSCILACAO_DESCENDENTE)) || ((this->consumer_classification_months[i] == CONSUMO_BAIXO) &&  (this->risc_months[i] == MEDIO_RISCO) && (this->oscillation_months[i] == OSCILACAO_DESCENDENTE))) {
            this->customer.t.months[i]= 1;
        } else {
			this->customer.t.months[i]= 0;
        }
    }
}

void Checker::check_fraudulent() {
	for ( int i = 0; i < 12; i++ ) {
        if (this->customer.t.months[i] == 1){
			this->customer.t.isFraudulent= true;
        } else {
			this->customer.t.isFraudulent= false;	
			break;		
        }
    }
}
