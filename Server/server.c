/***********************************************************/
/***************** Author	: Kyrillos Adel	****************/
/***************** Date		: 17-8-2022    	****************/
/***************** Module	: Server      	****************/
/***************** Version	: v1.0      	****************/
/***********************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "../LIB/STD_TYPES.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"

ST_transaction_t transactions[255] = {0};

ST_accountsDB_t accountsDB[255] = {
    {25000, "3248793249874234"},
    {7000, "3294987372647832"},
    {11500, "827634873264873284"},
    {100000, "986239463294693243"},
    {12350, "724823764873268732"},
    {12500, "832764873264987632"}
};

uint16_t counter = 0;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{

    EN_transState_t status = DECLINED_INSUFFECIENT_FUND;

    if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
    {
        status = DECLINED_STOLEN_CARD;
		return status;
    }

    if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
    {
		status = DECLINED_INSUFFECIENT_FUND;
    }
    
	else
	{
        if(saveTransaction(&transData) == OK_serv)
        {
            status = APPROVED;
            accountsDB[counter].balance -= transData->terminalData.transAmount;
		    printf("transaction done successfully :)\n");
            printf("New balance: %f\n", accountsDB[counter].balance);
        }
        
        else
        {
            status = INTERNAL_SERVER_ERROR;
        }
	}

    return status;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    EN_serverError_t status = DECLINED_STOLEN_CARD;

	for (counter=0; counter<255 ; counter++)
	{
		if (!(strcmp(accountsDB[counter].primaryAccountNumber, cardData->primaryAccountNumber)))
		{
			status = OK_serv;
            break;
		}

        else
        {
            //Error status remains DECLINED_STOLEN_CARD
        }
	}
	return status;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    EN_serverError_t status = LOW_BALANCE;
    if ((termData->transAmount) <= accountsDB[counter].balance)
    {
		status = OK_serv;
    }

    else
    {
		//Error status remains LOW_BALANCE
    }

    return status;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t status = SAVING_FAILED;
    static uint16_t counter = 0;

    if(counter < 255)
    {
        strcpy(transactions[counter].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
	    strcpy(transactions[counter].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
	    strcpy(transactions[counter].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
	    strcpy(transactions[counter].terminalData.transactionDate, transData->terminalData.transactionDate);
    
        transactions[counter].terminalData.transAmount = transData->terminalData.transAmount;
        transactions[counter].transState = transData->transState;
	    transactions[counter].transactionSequenceNumber = ++counter;
        status = OK_serv;
    }

    else
    {
        //Error status remains SAVING_FAILED
    }

    return status;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    EN_serverError_t status = TRANSACTION_NOT_FOUND;
	for (int i=0; i<255 ; i++)
	{
		if (transactionSequenceNumber == transactions[i].transactionSequenceNumber)
		{
			status = OK_serv;
            *transData = transactions[i];
		}

		else
		{
			//Error status remains TRANSACTION_NOT_FOUND
		}
	}
	return status;
}

