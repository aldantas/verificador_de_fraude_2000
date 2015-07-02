#ifndef CUSTOMER
#define CUSTOMER

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
#define TEM_ANOMALIA 1
#define NAO_TEM_ANOMALIA 0

typedef struct customer{
    std::string code;
    int *months;
    bool isFraudulent;
} Customer;

#endif // CUSTOMER
