#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"

#include "bank.h"
#include "branch.h"
#include "account.h"
#include "report.h"
#include "debug.h"

/*
 * allocate the bank structure and initialize the branches.
 */
Bank* Bank_Init(int numBranches, int numAccounts, AccountAmount initalAmount,
		  AccountAmount reportingAmount,
		  int numWorkers)
{
	Bank* bank = malloc(sizeof(Bank));

	if (bank == NULL)
	{
		return bank;
	}

	Branch_Init(bank, numBranches, numAccounts, initalAmount);
	Report_Init(bank, reportingAmount, numWorkers);

	bank->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(bank->lock, NULL);

	bank->leftWorkerCheck = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(bank->leftWorkerCheck, NULL);

	bank->workerLocks = malloc(numWorkers * sizeof(sem_t*));
	for (int i = 0; i < numWorkers; i++) {
		bank->workerLocks[i] = malloc(sizeof(sem_t));
		sem_init(bank->workerLocks[i], 0, 0);
	}
	bank->leftWorker = bank->allWorkers = numWorkers;
	
	return bank;
}

void Bank_Dispoce(Bank* bank) {
	for (int i = 0; i < bank->allWorkers; i++) {
		free(bank->workerLocks[i]);
	}
	for (unsigned int i = 0; i < bank->numberBranches; i++) {
		Branch_Dispoce(&bank->branches[i]);
	}
	free(bank->report);
	free(bank->branches);
	free(bank->workerLocks);
	free(bank->lock);
	free(bank->leftWorkerCheck);
	free(bank);
}

/*
 * get the balance of the entire bank by adding up all the balances in
 * each branch.
 */
int Bank_Balance(Bank *bank, AccountAmount *balance)
{
	assert(bank->branches);

	AccountAmount bankTotal = 0;
	for (unsigned int branch = 0; branch < bank->numberBranches; branch++)
	{
		AccountAmount branchBalance;
		pthread_mutex_lock(bank->branches[branch].lock);
		int err = Branch_Balance(bank, bank->branches[branch].branchID, &branchBalance);
		if (err < 0)
		{
			for (unsigned int i = 0; i <= branch; i++) {
				pthread_mutex_unlock(bank->branches[i].lock);
			}
			return err;
		}
		bankTotal += branchBalance;
	}

	for (unsigned int branch = 0; branch < bank->numberBranches; branch++) {
		pthread_mutex_unlock(bank->branches[branch].lock);
	}

	*balance = bankTotal;

	return 0;
}

/*
 * tranverse and validate each branch.
 */
int Bank_Validate(Bank* bank)
{
	assert(bank->branches);
	int err = 0;

	for (unsigned int branch = 0; branch < bank->numberBranches; branch++)
	{
		int berr = Branch_Validate(bank, bank->branches[branch].branchID);
		if (berr < 0)
		{
			err = berr;
		}
	}
	return err;
}

/*
 * compare the data inside two banks and see they are exactly the same;
 * it is called in BankTest.
 */
int Bank_Compare(Bank* bank1, Bank* bank2)
{
	int err = 0;
	if (bank1->numberBranches != bank2->numberBranches)
	{
		fprintf(stderr, "Bank num branches mismatch\n");
		return -1;
	}

	for (unsigned int branch = 0; branch < bank1->numberBranches; branch++)
	{
		int berr = Branch_Compare(&bank1->branches[branch],
								  &bank2->branches[branch]);
		if (berr < 0)
		{
			err = berr;
		}
	}

	int cerr = Report_Compare(bank1, bank2);
	if (cerr < 0)
		err = cerr;

	return err;
}

