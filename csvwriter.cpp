#include "csvwriter.h"

CSVWriter::CSVWriter(std::string file_name)
{
    file = new std::ofstream(file_name, std::ios::trunc);
}

void CSVWriter::writeBuffer(std::list<Customer> *customers)
{
    mutex.lock();

    if(file->is_open()){
        file << "U_CODIGO, jan, fev, mar, abr, mai, jun, jul, ago, set, out, nov, dez, resultado\n";

        for(std::list<Customer>::const_iterator i = customers->begin(); i != customers->end(); i++){
            std::string isFraudulent = i->isFraudulent ? "SIM" : "NAO";
            std::string months;

            for(short x = 0; x < 12; x++){
                months += i->months[x] == TEM_ANOMALIA  ? "SIM," : "NAO,";
            }

            *file << i->code + ',' + months + isFraudulent + '\n';
        }
    }

    delete customers;

    mutex.unlock();
}

CSVWriter::~CSVWriter()
{
   if(this->file != NULL){
       file->close();
       delete file;
   }
}
