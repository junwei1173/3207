#include "launch.h"
int status;
int connectTsh(u_short port)
{
   struct hostent *host ;
   short tsh_port ;
   u_long tsh_host ;
   int sock ;

   // use local host 
   tsh_host = inet_addr("127.0.0.1");
   /*
   if ((host = gethostbyname("localhost")) == NULL)
	{
	   perror("connectTsh::gethostbyname\n") ;
	   exit(1) ;
	}
   tsh_host = *((long *)host->h_addr_list[0]) ;
   */
   tsh_port = htons(port);
				/* get socket and connect to TSH */
   if ((sock = get_socket()) == -1)
    {
       perror("connectTsh::get_socket\n") ;
       exit(1) ;
    }
   if (!do_connect(sock, tsh_host, tsh_port))
    {
       perror("connectTsh::do_connect\n") ;
       exit(1) ;
    }      
   return sock ;
}


void OpShell(char* buff){
	
   tsh_shell_it out ;
   tsh_shell_ot in ;
   int tmp ;
   char *st ;
   

   printf("TSH_OP_SHELL\n") ;
   out.length = (strlen(buff)+1);
   out.length = htonl(out.length) ;
   printf("\n Entered Shell Command: %s\n", buff) ;
 
				/* send data to TSH */
   if (!writen(tshsock, (char *)&out, sizeof(out)))
    {
       perror("\nOpShell::writen\n") ;
       getchar() ;
       free(buff) ;
       return ;
    }
				/* send tuple to TSH */
   if (!writen(tshsock, buff, ntohl(out.length)))
    {
       perror("\nOpShell::writen\n") ;
       getchar() ;
       free(buff) ;
       return ;
    }
				//* read result 
   if (!readn(tshsock, (char *)&in, sizeof(in)))
    {
       perror("\nOpShell::readn error\n") ;
       getchar() ;
       return ;
    }
	
				/* print result from TSH */
				
    printf("\n\nFrom TSH :\n") ;
   printf("Process PID(%d) \n",getpid());
   printf("Username :%s", in.username);
   printf("CWD :%s", in.cwd_loc);
   printf("status : %d \n", ntohs(in.status)) ;
   printf("error : %d\n", ntohs(in.error)) ;
   printf("\n%s\n", in.out_buffer);
}



int main(int argc, char **argv){

	
     if(argc < 2){
        printf("Usage : %s port\n", argv[0]) ;
        return 0;
    }
	
	
   tsh_shell_it out ;
   tsh_shell_ot in ;
   char *buff,*st ;
   char* cmd;
   
   status=system("clear") ;
   printf("TSH_OP_Shell") ;
   printf("\n----------\n") ;
   
 // cmd comamnd 
   

   size_t bufsize = 1024;
   size_t characters;

    buff = (char *)malloc(bufsize * sizeof(char));
 
   if( buff == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
   
  printf("\n Enter the shell command : ") ; /* shell command */  
  characters = getline(&buff,&bufsize,stdin);
 
    u_short this_op = TSH_OP_SHELL;
    this_op = htons(this_op) ;
    tshsock = connectTsh(atoi(argv[1])) ;
	
	if (!writen(tshsock, (char *)&this_op, sizeof(this_op)))
			{
			   perror("main::writen\n") ;
			   exit(1) ;
			}
	
    // Response processing
    OpShell(buff);
    close(tshsock) ;
    printf("\n");
	
}





