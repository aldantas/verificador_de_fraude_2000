#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "customer.h"
#include <string>

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

//Classe com os atributos Customer, os respectivos consumo maximo e minimo, e os métodos que realizam as verificações
class Checker {
    unsigned int consumer_max;
    unsigned int consumer_min;
	unsigned int *consumer_classification_months;
    unsigned int *risc_months;
	unsigned int *oscillation_months;

  public:
    Checker();
    void inline check(Costumer &costumer);
    void inline check_consumer_classification();
    void inline check_risc();
    void inline check_oscillation();
    void inline check_anomaly();
	void inline check_fraudulent();
    void inline check_consumer_max();
    void inline check_consumer_min();
};

#endif
