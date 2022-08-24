/***********************************************************/
/***************** Author	: Kyrillos Adel	****************/
/***************** Date		: 17-8-2022    	****************/
/***************** Module	: Application  	****************/
/***************** Version	: v1.0      	****************/
/***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LIB/STD_TYPES.h"
#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"



void appStart(void)
{
    uint8_t repeat = 'e';
    // uint8_t end = 'c';
    // ST_cardData_t card_data;
	// ST_terminalData_t term_data;
    EN_transState_t trans_status;
	ST_transaction_t trans_data;
	while(setMaxAmount(&trans_data.terminalData) == INVALID_MAX_AMOUNT)
    {
    	printf("Maximum amount should be > 0!\n");
    }

	do
    {
    	while(getCardHolderName(&trans_data.cardHolderData) == WRONG_NAME)
    	{
    		printf("Wrong name!\n");
    	}

    	while(getCardExpiryDate(&trans_data.cardHolderData) == WRONG_EXP_DATE)
    	{
    		printf("Wrong date!\n");
    	}

    	while(getCardPAN(&trans_data.cardHolderData) == WRONG_PAN)
    	{
    		printf("Wrong PAN!\n");
    	}

    	while(getTransactionDate(&trans_data.terminalData) == WRONG_DATE)
    	{
    		printf("Wrong Date\n");
    	}

    	if(isCardExpired(trans_data.cardHolderData, trans_data.terminalData) == EXPIRED_CARD)
    	{
    		printf("Declined, expired Card!\n");
    		break;
    	}

    	if(getTransactionAmount(&trans_data.terminalData) == INVALID_AMOUNT)
    	{
    		printf("Invalid amount!\n");
    		break;
    	}

    	if(isBelowMaxAmount(&trans_data.terminalData) == EXCEED_MAX_AMOUNT)
    	{
    		printf("Declined, amount exceeding limit!\n");
    		break;
    	}

        trans_status = recieveTransactionData(&trans_data);

        switch (trans_status)
        {
            case DECLINED_STOLEN_CARD:
                printf("Declined, invalid account\n");
                break;

            case DECLINED_INSUFFECIENT_FUND:
                printf("Declined, invalid account\n");
                break;

            case INTERNAL_SERVER_ERROR:
                printf("Declined, insufficient funds\n");
                break;
        
            case APPROVED:
                printf("DONE\n");
                break;
        }
    
    	printf("Enter e to end, any other key to make a new transaction: ");
        scanf(" %c", &repeat);

    } while (repeat != 'e');

}
