#include "csvwriter.h"
#include <iostream>

CSVWriter::CSVWriter(std::string file1_name)
{
    file1 = new std::ofstream(file1_name, std::ios::trunc);
    if(file1->is_open()) {
        *file1 << "U_CODIGO, jan, fev, mar, abr, mai, jun, jul, ago, set, out, nov, dez, resultado\n";
    }
}

CSVWriter::CSVWriter(std::string file1_name, std::string file2_name)
{
    file1 = new std::ofstream(file1_name, std::ios::trunc);
    if(file1->is_open()) {
        *file1 << "U_CODIGO, jan, fev, mar, abr, mai, jun, jul, ago, set, out, nov, dez, resultado\n";
    }
    file2 = new std::ofstream(file2_name, std::ios::trunc);
    if(file2->is_open()) {
        *file2 << "U_CODIGO, jan, fev, mar, abr, mai, jun, jul, ago, set, out, nov, dez, resultado\n";
    }
}

void CSVWriter::writeBuffer(std::list<Customer> *customers)
{
    mutex.lock();

    if(file1->is_open()){

        for(std::list<Customer>::const_iterator i = customers->begin(); i != customers->end(); i++){
            std::string isFraudulent = i->isFraudulent ? "SIM" : "NAO";
            std::string months;

            for(short x = 0; x < 12; x++){
                months += i->months_result[x] == TEM_ANOMALIA  ? "SIM," : "NAO,";
            }

            *file1 << i->code + ',' + months + isFraudulent + '\n';
        }
    }

	if(file2->is_open()){

		for(std::list<Customer>::const_iterator i = customers->begin(); i != customers->end(); i++){
			std::string isFraudulent = i->isFraudulent ? "SIM" : "NAO";
			std::string months;

			for(short x = 0; x < 12; x++){
				*file2 << i->months[x] << ',';
			}
			*file2 << isFraudulent + '\n';
		}

	}

	mutex.unlock();
}

CSVWriter::~CSVWriter()
{
	if(this->file1 != NULL){
		file1->close();
		delete file1;
	}
	if(this->file2 != NULL){
		file2->close();
		delete file2;
	}
}
