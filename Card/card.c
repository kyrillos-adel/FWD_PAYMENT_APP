/***********************************************************/
/***************** Author	: Kyrillos Adel	****************/
/***************** Date		: 17-8-2022    	****************/
/***************** Module	: Card        	****************/
/***************** Version	: v1.0      	****************/
/***********************************************************/

#include "../LIB/STD_TYPES.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    EN_cardError_t status = WRONG_NAME;
    uint8_t name[25] = "";

    printf("Please enter Card holder name (20-24 characters): ");
    gets(&name);
    if((name == NULL_STR) || (strlen(name)<20) || (strlen(name)>24))
    {
        //Do not store the name and the status error remains WRONG_NAME
    }

    else
    {
        status = OK_card;

        /* strcpy function in string.h library tackes the destination array to store string 
         * and the source array of string to copy to the destination including the null character
         */
        strcpy(cardData->cardHolderName, name);
    }

    return status;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t status = WRONG_EXP_DATE;
    uint8_t exp_date[6] = "";

    printf("Please enter the card expiry date in the format (MM/YY): ");
    gets(exp_date);

    if((strlen(exp_date)==5) 
        && ((exp_date[0]=='0' && exp_date[1]>'0' && exp_date[1]<='9') || (exp_date[0]=='1' && exp_date[1]>='0' && exp_date[1]<'3')) 
        && (exp_date[2]=='/')
        && (exp_date[3]>'1' && exp_date [3]<='9' && exp_date[4]>='0' && exp_date [4]<='9')
        )
    {
        status = OK_card;
        strcpy(cardData->cardExpirationDate, exp_date);
    }

    else
    {
        //Do not store the cardExpirationDate and the status error remains WRONG_EXP_DATE
    }

    return status;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{

    EN_cardError_t status = WRONG_PAN;
    uint8_t PAN[20] = "";

    printf("Please enter the PAN: ");
    gets(PAN);

    if(strlen(PAN)<16 || strlen(PAN)>19)
    {
        //Do not store the cardPAN and the status error remains WRONG_PAN
    }

    else
    {
        status = OK_card;
        strcpy(cardData->primaryAccountNumber, PAN);
    }

    return status;
}
