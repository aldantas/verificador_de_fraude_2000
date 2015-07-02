#include "csvreader.h"

CSVReader::CSVReader(std::string file_name)
{
    this->file = new std::ifstream(file_name);
    std::string line;

    //busca o indice das colunas a serem lidas do arquivo
    if(this->file->is_open()){
        if(std::getline(*file, line)){
            std::stringstream ss(line);
            std::string token;
            unsigned short count = 0;

            while(std::getline(ss, token, ',')){
                if(std::find(columns.begin(), columns.end(), token) != columns.end()){
                    this->columns_index.push_back(count);
                }

                count++;
            }
        }
    } else {
        std::cout << "O arquivo nao pode ser aberto\n";
    }
}

std::list<Customer> CSVReader::readLines(unsigned short quantity)
{
    unsigned short retrieved = 0;
    std::list<Customer> list;
    std::string line;

    if(this->file->is_open()){
       while(retrieved < quantity && std::getline(*file, line)){
          Customer customer;
          customer.t.months = new unsigned int[12];

          std::stringstream ss(line);
          std::string token;
          unsigned short count = 0, i = 0;

          while(std::getline(ss, token, ',')){
              //verifica se e uma coluna a ser lida
              if(std::find(columns_index.begin(), columns_index.end(), count) != columns_index.end()){
                  if(count != columns_index[0]){
                      customer.t.months[i++] = std::stoi(token);
                  } else {
                      customer.code = token;
                  }
              }

              count++;
          }

          list.push_back(customer);
          retrieved++;
      }
    }

    return list;
}

CSVReader::~CSVReader()
{
    if(this->file != NULL){
        this->file->close();
        delete this->file;
    }
}
