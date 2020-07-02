#ifdef __CROSS__
#include <string.h>
#include "rxmvsext.h"
#include "rxtso.h"

int rac_user_auth(char *userName, char *password)
{
    int rc = 0;
    if ( (strcmp(userName, "user1") == 0) && (strcmp(password, "pass1") == 0) )
        rc = 1;

    return rc;
}

/* dummy implementations for cross development */
int call_rxinit(RX_INIT_PARAMS_PTR params)
{
    int rc = 0;

    RX_ENVIRONMENT_CTX_PTR env;

#ifdef __DEBUG__
    printf("DBG> DUMMY RXINIT ...\n");
#endif

    if (params != NULL) {
        if (params->rxctxadr != NULL) {
            env = (RX_ENVIRONMENT_CTX_PTR)params->rxctxadr;
            env->flags1 = 0x0F;
            env->flags2 = 0x00;
            env->flags3 = 0x00;

            strncpy(env->SYSENV,  "DEVEL",   5);
            strncpy(env->SYSPREF, "MIG",     3);
            strncpy(env->SYSUID,  "FIX0MIG", 7);

        } else {
            rc = -42;
        }
    } else {
        rc = -43;
    }
    return rc;
}

unsigned int call_rxikj441 (RX_IKJCT441_PARAMS_PTR params)
{
    printf("DBG> DUMMY RXIKJ441 ...\n");

    return 0;
}

int call_rxtso(RX_TSO_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXTSO ...\n");

#endif
    return 0;
}

void call_rxsvc (RX_SVC_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL) {
        printf("DBG> DUMMY RXSVC for svc %d .\n", params->SVC);
        if(params->SVC == 93) {
            if((params->R1 & 0x81000000) == 0x81000000) {
                printf("DBG> TGET ASIS\n");
                printf("DBG> PRESS ENTER KEY\n");
                getchar();

                params->R1 = 42;
            } else if ((params->R1 & 0x03000000) == 0x03000000) {
                printf("DBG> TPUT FSS\n");
            }
        } else if (params->SVC == 94) {
            RX_GTTERM_PARAMS_PTR paramsPtr = params->R1;
            memcpy((void *)*paramsPtr->primadr,0x1850,2);
        } else if (params->SVC == 18) {
            RX_GTTERM_PARAMS_PTR paramsPtr = params->R1;
            params->R15 = 4;
        }
    }
    printf("DBG> DUMMY RXSVC for svc %d .\n", params->SVC);
#endif
}

int call_rxvsam (RX_VSAM_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL) {
        printf("\n");
        printf("DBG> DUMMY RXVSAM ...\n");
        printf("DBG>  VSAMFUNC : %s\n",params->VSAMFUNC);
        printf("DBG>  VSAMTYPE : %c\n",params->VSAMTYPE);
        printf("DBG>  VSAMDDN  : %s\n",params->VSAMDDN);
        printf("DBG>  VSAMKEY  : %s\n",params->VSAMKEY);
        printf("DBG>  VSAMKEYL : %d\n",params->VSAMKEYL);

        if (strcasecmp(params->VSAMFUNC, "READK") == 0) {
            char * record = MALLOC(13, "CROSS VSAM READK");
            memset(record,0,13);
            strcpy(record,"123456789ABC");
            params->VSAMREC = (void *)record;
            params->VSAMRECL=12;
        }

        if (strcasecmp(params->VSAMFUNC, "READN") == 0) {
            char * record = MALLOC(13,"CROSS VSAM READN");

            strcpy(record,"ABC123456789");
            params->VSAMREC = (void *)record;
            params->VSAMRECL=12;
        }

        if (strcasecmp(params->VSAMFUNC, "WRITE") == 0) {
            printf("DBG>  VSAMREC  : %s\n",params->VSAMREC);
        }
    }

#endif
    return 0;
}

int call_rxptime (RX_PTIME_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXPTIME ...\n");

#endif
    return 0;
}

int call_rxstime (RX_STIME_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXSTIME ...\n");
#endif
    return 0;
}

int call_rxwto (RX_WTO_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXWTO tell %s\n", params->msgadr);
#endif
    return 0;
}

int call_rxwait (RX_WAIT_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXWAIT for %d seconds.\n", (*params->timeadr)/100);
#endif
    return 0;
}

unsigned int call_rxabend (RX_ABEND_PARAMS_PTR params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXABEND with ucc %d\n", params->ucc);
#endif
    return 0;
}

int call_rxdynalc (RX_DYNALC_PARAMS_PTR  params)
{
#ifdef __DEBUG__
    if (params != NULL)
        printf("DBG> DUMMY RXDYNALC ...\n");
#endif
    return 0;
}

#endif