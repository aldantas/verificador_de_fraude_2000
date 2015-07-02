#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "customer.h"
#include <string>

//Classe com os atributos Customer, os respectivos consumo maximo e minimo, e os métodos que realizam as verificações
class Checker {
    Customer *customer;
    unsigned int max_consumption;
    unsigned int min_consumption;
	unsigned int *consumption_classification_months;
    unsigned int *risc_months;
	unsigned int *oscillation_months;

  public:
    Checker();
    void inline check(Customer &customer);
    void inline check_consumption_classification();
    void inline check_risc();
    void inline check_oscillation();
    void inline check_anomaly();
	void inline check_fraudulent();
    void inline check_max_consumption();
    void inline check_min_consumption();
};

#endif
