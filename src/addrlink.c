#include "addrlink.h"
#include "rxmvsext.h"

char *hcmdargvp[128];

int
handleLinkCommands(PLstr cmd, PLstr env)
{
    int rc = 0;

    char sCmd[1025];

    char *loadModule;
    char *args;

    RX_SVC_PARAMS svcParams;

    struct S_LINK_PARMS {
        void* moduleName;
        void* dcbAddress
    };

    struct S_LINK_PARMS sLinkParms;

    bzero(sCmd,1025);
    strncpy(sCmd, (const char *) LSTR(*cmd), 1024);

    loadModule = strtok(sCmd," (),");
    args       = strtok(NULL,"");

    if (strcasecmp((const char *)LSTR(*env), "LINK") == 0) {
        if (findLoadModule(loadModule)) {
            sLinkParms.moduleName = loadModule;
            sLinkParms.dcbAddress = 0;

            svcParams.SVC = 6;
            svcParams.R0  = 0;
            svcParams.R1  = (unsigned int) &args;
            svcParams.R15 = &sLinkParms;

            call_rxsvc(&svcParams);

            printf("FOO> RXSVC RC(%d)\n", svcParams.R15);
            if (svcParams.R15 == 0) {
                rc = 1;
            }
        }

    } else if (strcasecmp((const char *)LSTR(*env), "LINKMVS") == 0) {

    } else if (strcasecmp((const char *)LSTR(*env), "LINKPGM") == 0) {

    }

    return 0;

}