/*.........................................................................*/
/*                  TSHTEST.H ------> TSH test program                     */
/*                  February '13, Oct '18 updated by Justin Y. Shi         */
/*.........................................................................*/

#include "synergy.h"

char login[NAME_LEN];

void OpPut(/*void*/) ;
void OpGet(/*void*/) ;
void OpExit(/*void*/) ;
void OpShell(/*void*/) ;
void OpRetrieve(/*void*/) ;





int tshsock ;

int connectTsh(u_short) ;
u_short drawMenu(/*void*/) ;

