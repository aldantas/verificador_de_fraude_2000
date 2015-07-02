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
#include "csvreader.h"
#include "customer.h"
#include <iostream>
#include <thread>
#include "csvwriter.h"

#define THREAD_COUNT 5
#define READ_LINE_INTERVAL 1000

std::list<Customer> *thread_lists[THREAD_COUNT];

void proccess(std::list<Customer>*, int);

int main(int argc, char *argv[])
{
	CSVReader reader(argv[1]);
	CSVWriter writer(argv[2]);
	std::thread threads[THREAD_COUNT];

	while(!reader.atEnd()) {
		for(int i = 0; i < THREAD_COUNT; i++) {
			threads[i] = std::thread(proccess, reader.readLines(READ_LINE_INTERVAL), i);
		}

		for(int i = 0; i < THREAD_COUNT; i++) {
			threads[i].join();
		}

		for(int i = 0; i < THREAD_COUNT; i++) {
			writer.writeBuffer(thread_lists[i]);
		}

	}
	return 0;
}

void teste(Customer &customer)
{
	customer.t.isFraudulent = false;
}

void proccess(std::list<Customer> *customer_list, int thread_index)
{
	for(std::list<Customer>::iterator it=customer_list->begin(); it != customer_list->end(); ++it) {
		/* check(*it); */
		teste(*it);
	}

	thread_lists[thread_index] = customer_list;
}
