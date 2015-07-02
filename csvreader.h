#ifndef CSVREADER_H
#define CSVREADER_H

#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>
#include "customer.h"

class CSVReader
{
    std::ifstream *file;
    std::vector<short> columns_index;
    std::vector<std::string> columns = {
        "U_CODIGO",
        "jan_11", "fev_11", "mar_11", "abr_11", "mai_11", "jun_11", "jul_11", "ago_11", "set_11", "out_11", "nov_11", "dez_11"
    };

public:
    CSVReader(std::string file_name);
    std::list<Customer>* readLines(unsigned short quantity = 100);
    bool atEnd();
    ~CSVReader();

private:
    std::list<std::string>* retrieveTokens(std::string line, char delimiter = ',');
};

#endif // CSVREADER_H
