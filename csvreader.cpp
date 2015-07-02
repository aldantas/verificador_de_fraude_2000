#include "csvreader.h"
#include <iostream>

CSVReader::CSVReader(std::string file_name)
{
    this->file = new std::ifstream(file_name);
    std::string line;

    //busca o indice das colunas a serem lidas do arquivo
    if(this->file->is_open()){
        if(std::getline(*file, line)){
            std::list<std::string> *tokens = this->retrieveTokens(line);
            unsigned short count = 0;

            for(std::list<std::string>::const_iterator token = tokens->begin(); token != tokens->end(); token++){
                if(std::find(columns.begin(), columns.end(), *token) != columns.end()){
                    this->columns_index.push_back(count);
                }

                count++;
            }

            delete tokens;
        }
    } else {
        std::cout << "Arquivo não encontrado!" << std::endl;
    }
}

std::list<Customer>* CSVReader::readLines(unsigned short quantity)
{
    unsigned short retrieved = 0;
    std::list<Customer> *list = new std::list<Customer>();
    std::string line;

    if(this->file->is_open()){
        while(retrieved < quantity && std::getline(*file, line)){
            Customer customer;
            customer.months = new unsigned int[12];

            std::list<std::string> *tokens = this->retrieveTokens(line);
            unsigned short count = 0, i = 0;

            for(std::list<std::string>::const_iterator token = tokens->begin(); token != tokens->end(); token++){
                //verifica se e uma coluna a ser lida
                if(std::find(columns_index.begin(), columns_index.end(), count) != columns_index.end()){
                    if(count != columns_index[0]){
                        customer.months[i++] = std::stoi(*token);
                    } else {
                        customer.code = *token;
                    }
                }

                count++;
            }

            delete tokens;
            list->push_back(customer);
            retrieved++;
        }
    }

    return list;
}

bool CSVReader::atEnd()
{
   return file->eof();
}

CSVReader::~CSVReader()
{
    if(this->file != NULL){
        this->file->close();
        delete this->file;
    }
}

std::list<std::string>* CSVReader::retrieveTokens(std::string line, char delimiter)
{
   std::stringstream ss(line);
   std::string token;
   std::list<std::string> *tokens = new std::list<std::string>();

   while(std::getline(ss, token, delimiter)){
       tokens->push_back(token);
   }

   return tokens;
}
