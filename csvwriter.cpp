#include "csvwriter.h"

CSVWriter::CSVWriter(std::string file_name)
{
    file = new std::ofstream(file_name, std::ios::trunc);
}

void CSVWriter::writeBuffer(std::list<Customer> *customers)
{
    mutex.lock();

    if(file->is_open()){
        for(std::list<Customer>::const_iterator i = customers->begin(); i != customers->end(); i++){
            std::string isFraudulent = i->t.isFraudulent ? "SIM" : "NAO";

            *file << i->code + ',' + isFraudulent + '\n';
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
