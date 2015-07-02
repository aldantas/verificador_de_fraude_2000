#ifndef CUSTOMER
#define CUSTOMER

typedef struct customer{
    std::string code;
    union type{
        unsigned int *months;
        bool isFraudulent;
    } t;
} Customer;

#endif // CUSTOMER
