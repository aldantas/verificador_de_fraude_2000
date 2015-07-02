#ifndef CUSTOMER
#define CUSTOMER

#include <string>

typedef struct customer{
    std::string code;
    unsigned int *months;
    bool isFraudulent;
} Customer;

#endif // CUSTOMER
