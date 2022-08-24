/***********************************************************/
/***************** Author	: Kyrillos Adel	****************/
/***************** Date		: 17-8-2022    	****************/
/***************** Module	: Terminal  	****************/
/***************** Version	: v1.0      	****************/
/***********************************************************/

#include "../LIB/STD_TYPES.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t status = WRONG_DATE;
    uint8_t trans_date[11]="";

    printf("Please enter transaction date in the format(DD/MM/YYYY): ");
    gets(trans_date);

    if((strlen(trans_date) == 10)
        && (trans_date[2] == '/') 
        && (trans_date[5] == '/'))
        {
            status = OK_term;
            strcpy(termData->transactionDate , trans_date);
        }
        
        else
        {
            //Don't store date in the termData.transaction and error status remains WRONG_DATE
        }

    return status;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    EN_terminalError_t status = EXPIRED_CARD;

    uint16_t exp_year, trans_year;
    uint8_t exp_month, trans_month;

    /* Calculate the expiration year from the string MM/YY
     * Note add 2000 to the year as the expireation year on the car is written the the last 2 numbers of the year
     */
    exp_year = (((cardData.cardExpirationDate[3] - '0' ) * 10) + (cardData.cardExpirationDate[4] - '0' ))+ 2000;
    
    /*Calculate the expirtion month from the string MM/YY*/
    exp_month = (cardData.cardExpirationDate[0] - '0') * 10 + ( cardData.cardExpirationDate[1] - '0');

    /*Calculate the transaction year from the string DD/MM/YYYY */
    trans_year = (((termData.transactionDate[6] - '0' ) * 1000) + ((termData.transactionDate[7] - '0' ) * 100)
                  + ((termData.transactionDate[8] - '0' ) * 10) + (termData.transactionDate[9] - '0' ));

    /*Calculate the transaction month from the string DD/MM/YYYY */
    trans_month = (((termData.transactionDate[3] - '0') * 10) + (termData.transactionDate[4] - '0'));

    if((exp_year>=trans_year))
    {
        if((exp_year==trans_year) && (exp_month<trans_month))
        {
            //Error ststus remains Expired card
        }

        else
        {
            status = OK_term;
        }
    }

    else
    {
        //Error ststus remains Expired card
    }

    return status;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    
    return OK_term;

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t status = INVALID_AMOUNT;
    f32 trans_ammount = 0;

    printf("Please Enter transaction ammount: ");
    scanf(" %f", &trans_ammount);

    if (trans_ammount<=0)
    {
        //Error status remains INVALID_AMMOUNT
    }

    else
    {
        status = OK_term;
        termData->transAmount = trans_ammount;
    }

    return status;

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t status = EXCEED_MAX_AMOUNT;

    if(termData->transAmount<=termData->maxTransAmount)
    {
        status = OK_term;
    }

    else
    {
        //Error status remains EXCEED_MAX_AMOUNT
    }
    
    return status;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t status = INVALID_MAX_AMOUNT;
    f32 max_ammount = 0;

    printf("Please enter max transition ammount: ");
    scanf(" %f", &max_ammount);

    if (max_ammount>0)
    {
        status = OK_term;
        termData->maxTransAmount = max_ammount;
    }
    
    else
    {
        //Error status remains INVALID_MAX_AMOUNT and don't set max ammount
    }

    return status;
}

