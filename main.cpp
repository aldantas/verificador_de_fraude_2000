/* *************************************************************************
 * Copyright (C) 2015
 *
 * Augusto Lopez Dantas - augustold42@gmail.com
 * Cristiano Antonio de Souza - cristianoantonio.souza10@gmail.com
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

#include <iostream>
#include <thread>
#include "checker.hpp"
#include "csvreader.h"
#include "customer.h"
#include "csvwriter.h"

#define THREAD_COUNT 5 // quantidade de execuções paralelas
#define READ_LINE_INTERVAL 1000 // quantidade de linhas lidas por thread

/* array global com listas de clientes que serão concatenados
 * parcialmente no arquivo de saída */
std::list<Customer> *thread_lists[THREAD_COUNT];

/* declaração da função */
void proccess(std::list<Customer>*, int);

/* Para executar: ./programa arquivo_entrada.csv arquivo_saída.csv */
int main(int argc, char *argv[])
{
    /* abra o arquivo de entrada */
	CSVReader reader(argv[1]);
    /* inicialize o arquivo de saída */
	CSVWriter writer(argv[2]);

	std::thread threads[THREAD_COUNT];
    std::cout << "Aguarde..." << std::endl;

    /* percorre pelo arquivo de entrada */
	while(!reader.atEnd()) {
        /* para cada thread, leia N linhas e as processe */
		for(int i = 0; i < THREAD_COUNT; i++) {
			threads[i] = std::thread(proccess, reader.readLines(READ_LINE_INTERVAL), i);
		}

        /* aguarde a finalização das threads */
		for(int i = 0; i < THREAD_COUNT; i++) {
			threads[i].join();
		}

        /* concatene no arquivo de saída os resultados de cada thread */
		for(int i = 0; i < THREAD_COUNT; i++) {
			writer.writeBuffer(thread_lists[0]);
		}

	}

	return 0;
}

void proccess(std::list<Customer> *customer_list, int thread_index)
{
    /* inicializa o objeto checker */
    Checker *checker = new Checker();
    /* para cada cliente na lista, execute as funções de checagem */
	for(std::list<Customer>::iterator it=customer_list->begin(); it != customer_list->end(); ++it) {
		checker->check(*it);
	}

    /* armaze os resultado obtidos no array global para concatenar
     * no arquivo de saída quandos as N thread finalizarem */
	thread_lists[thread_index] = customer_list;
}
