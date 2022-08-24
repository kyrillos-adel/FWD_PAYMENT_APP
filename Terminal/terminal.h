/***********************************************************/
/***************** Author	: Kyrillos Adel	****************/
/***************** Date		: 17-8-2022    	****************/
/***************** Module	: Terminal  	****************/
/***************** Version	: v1.0      	****************/
/***********************************************************/

#include "../LIB/STD_TYPES.h"
#include "../Card/card.h"

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    OK_term, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);


#endif
