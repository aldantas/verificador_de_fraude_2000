/* *************************************************************************
 * Copyright (C) 2015
 *
 * Augusto Lopez Dantas - augustold42@gmail.com
 * Cristiano Antonio de Souza -
 * Gabriel Custódio Martins - gcmartins93@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ************************************************************************* */

#include "checker.hpp"
#include <iostream>
#include <thread>
#include "csvreader.h"
#include "csvwriter.h"

using namespace std;

void teste(int i) {
    cout << i;
}

int main(void) {
    /*thread threads[5];

    for(int i = 0; i < 5; i++) {
        threads[i] = thread(teste, i);
    }

    for(int i = 0; i < 5; i++) {
        threads[i].join();
    }

    cout << endl;*/

    CSVReader *reader = new CSVReader("test.csv");
    std::list<Customer> *customers = reader->readLines();

    for(std::list<Customer>::iterator i = customers->begin(); i != customers->end(); i++){
        std::cout << i->code << std::endl;
    }

    delete customers;

    /*Customer c;
    c.code = "0000111";
    c.t.isFraudulent = false;

    std::list<Customer> *l = new std::list<Customer>();
    l->push_back(c);

    CSVWriter *writer = new CSVWriter();
    writer->writeBuffer(l);
    delete writer;*/

    return 0;
}
