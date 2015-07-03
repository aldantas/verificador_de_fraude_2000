#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <fstream>
#include <mutex>
#include <list>
#include "customer.h"

class CSVWriter
{
    std::ofstream *file1;
    std::ofstream *file2;
    std::mutex mutex;

public:
    CSVWriter(std::string file1_name);
    CSVWriter(std::string file1_name = "output1.csv", std::string file2_name = "output2.csv");
    void writeBuffer(std::list<Customer> *customers);
    ~CSVWriter();
};

#endif // CSVWRITER_H
