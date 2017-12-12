#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

#include "teller.h"
#include "error.h"
#include "debug.h"

/*
 * deposit money into an account
 */
int Teller_DoDeposit(Bank* bank, AccountNumber accountNum, AccountAmount amount)
{
	assert(amount >= 0);

	DPRINTF('t', ("Teller_DoDeposit(account 0x%" PRIx64 " amount %" PRId64 ")\n",
				  accountNum, amount));

	Account* account = Account_LookupByNumber(bank, accountNum);

	if (account == NULL)
	{
		return ERROR_ACCOUNT_NOT_FOUND;
	}

	BranchID curBranch = AccountNum_GetBranchID(accountNum);
	
	pthread_mutex_lock(account->lock);
	pthread_mutex_lock(bank->branches[curBranch].lock);
	
	Account_Adjust(bank, account, amount, 1);

	pthread_mutex_unlock(account->lock);
	pthread_mutex_unlock(bank->branches[curBranch].lock);
	return ERROR_SUCCESS;
}

/*
 * withdraw money from an account
 */
int Teller_DoWithdraw(Bank* bank, AccountNumber accountNum, AccountAmount amount)
{
	assert(amount >= 0);

	DPRINTF('t', ("Teller_DoWithdraw(account 0x%" PRIx64 " amount %" PRId64 ")\n",
				  accountNum, amount));

	Account* account = Account_LookupByNumber(bank, accountNum);

	if (account == NULL)
	{
		return ERROR_ACCOUNT_NOT_FOUND;
	}

	BranchID curBranch = AccountNum_GetBranchID(accountNum);
	
	pthread_mutex_lock(account->lock);
	pthread_mutex_lock(bank->branches[curBranch].lock);
	
	if (amount > Account_Balance(account))
	{
		pthread_mutex_unlock(account->lock);
		pthread_mutex_unlock(bank->branches[curBranch].lock);
		return ERROR_INSUFFICIENT_FUNDS;
	}
	
	Account_Adjust(bank, account, -amount, 1);
	
	pthread_mutex_unlock(account->lock);
	pthread_mutex_unlock(bank->branches[curBranch].lock);
	return ERROR_SUCCESS;
}

/*
 * do a tranfer from one account to another account
 */
int Teller_DoTransfer(Bank* bank, AccountNumber srcAccountNum,
					  AccountNumber dstAccountNum,
					  AccountAmount amount)
{
	assert(amount >= 0);

	DPRINTF('t', ("Teller_DoTransfer(src 0x%" PRIx64 ", dst 0x%" PRIx64
				  ", amount %" PRId64 ")\n",
				  srcAccountNum, dstAccountNum, amount));

	Account* srcAccount = Account_LookupByNumber(bank, srcAccountNum);
	BranchID srcBranch = AccountNum_GetBranchID(srcAccountNum);
	if (srcAccount == NULL)
	{
		return ERROR_ACCOUNT_NOT_FOUND;
	}

	Account* dstAccount = Account_LookupByNumber(bank, dstAccountNum);
	BranchID dstBranch = AccountNum_GetBranchID(dstAccountNum);
	if (dstAccount == NULL)
	{
		return ERROR_ACCOUNT_NOT_FOUND;
	}

	if (srcAccountNum == dstAccountNum) {
		return ERROR_SUCCESS;
	}

	if (srcAccountNum < dstAccountNum) {
		pthread_mutex_lock(srcAccount->lock);
		pthread_mutex_lock(dstAccount->lock);
	} else {
		pthread_mutex_lock(dstAccount->lock);
		pthread_mutex_lock(srcAccount->lock);
	}

	if (amount > Account_Balance(srcAccount))
	{
		pthread_mutex_unlock(srcAccount->lock);
		pthread_mutex_unlock(dstAccount->lock);
		return ERROR_INSUFFICIENT_FUNDS;
	}

	/*
   * If we are doing a transfer within the branch, we tell the Account module to
   * not bother updating the branch balance since the net change for the
   * branch return ERROR_INSUFFICIENT_FUNDS;
   * If we are doing a transfer within the branch, we tell the Account module to
   * not bother updating the branch balance since the net change for the
   * branch is 0.
   */
	int updateBranch = !Account_IsSameBranch(srcAccountNum, dstAccountNum);		

	if (updateBranch) {
		if (srcBranch < dstBranch) {
			pthread_mutex_lock(bank->branches[srcBranch].lock);
			pthread_mutex_lock(bank->branches[dstBranch].lock);
		} else {
			pthread_mutex_lock(bank->branches[dstBranch].lock);
			pthread_mutex_lock(bank->branches[srcBranch].lock);
		}
	}else{
		pthread_mutex_lock(bank->branches[srcBranch].lock);
	}

	Account_Adjust(bank, srcAccount, -amount, updateBranch);
	Account_Adjust(bank, dstAccount, amount, updateBranch);

	pthread_mutex_unlock(srcAccount->lock);
	pthread_mutex_unlock(dstAccount->lock);
	if (updateBranch) {
		pthread_mutex_unlock(bank->branches[srcBranch].lock);
		pthread_mutex_unlock(bank->branches[dstBranch].lock);
	}else{
		pthread_mutex_unlock(bank->branches[srcBranch].lock);
	}

	return ERROR_SUCCESS;
}
