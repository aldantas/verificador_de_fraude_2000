#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <fstream>
#include <mutex>
#include <list>
#include "customer.h"

class CSVWriter
{
    std::ofstream *file;
    std::mutex mutex;

public:
    CSVWriter(std::string file_name = "output.csv");
    void writeBuffer(std::list<Customer> *customers);
    ~CSVWriter();
};

#endif // CSVWRITER_H
