#ifndef _TELLER_H
#define _TELLER_H

#include "bank.h"
#include "account.h"
#include "branch.h"

#include <pthread.h>


int Teller_DoDeposit(Bank* bank, AccountNumber accountNum, AccountAmount amount);


int Teller_DoWithdraw(Bank* bank, AccountNumber accountNum,
                      AccountAmount amount);


int Teller_DoTransfer(Bank* bank, AccountNumber srcAccountNum,
                      AccountNumber dstAccountNum,
                      AccountAmount amount);



#endif /* _Teller_H */
