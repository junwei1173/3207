/*.........................................................................*/
/*                  TSHLIB.C ------> TSH Library for Scripting             */
/*                                                                         */
/*                  Derived from TSHTEST.C by Junwei Chen [April '25]         */
/*.........................................................................*/
#include "tshlib.h"
#include "tshtest.h"
int status;

// Connect to the TSH
int tshlib_connect(u_short port) {
    return connectTsh(port);
}

// Send a tuple to the TSH
int tshlib_put(int sock, const char *name, u_short priority, const char *tuple, int length) {
    tsh_put_it out;
    tsh_put_ot in;

    strncpy(out.name, name, sizeof(out.name));
    out.priority = htons(priority);
    out.length = htonl(length);

    if (!writen(sock, (char *)&out, sizeof(out))) return -1;
    if (!writen(sock, tuple, length)) return -1;
    if (!readn(sock, (char *)&in, sizeof(in))) return -1;

    return ntohs(in.status);
}

// Get a tuple from the TSH
int tshlib_get(int sock, const char *expr, char *recv_buf, int *out_length) {
    tsh_get_it out;
    tsh_get_ot1 in1;
    tsh_get_ot2 in2;
    struct in_addr addr;
    int sd, sock2;

    strncpy(out.expr, expr, sizeof(out.expr));
    out.host = inet_addr("127.0.0.1");

    if ((sd = get_socket()) == -1) return -1;
    if (!(out.port = bind_socket(sd, 0))) return -1;

    if (!writen(sock, (char *)&out, sizeof(out))) return -1;
    if (!readn(sock, (char *)&in1, sizeof(in1))) return -1;

    sock2 = (ntohs(in1.status) == SUCCESS) ? sock : get_connection(sd, NULL);

    if (!readn(sock2, (char *)&in2, sizeof(in2))) return -1;
    if (!readn(sock2, recv_buf, ntohl(in2.length))) return -1;

    *out_length = ntohl(in2.length);

    close(sd);
    if (sock2 != sock) close(sock2);

    return ntohs(in1.status);
}

// Run shell command via TSH
int tshlib_shell(int sock, const char *command, char *output_buf, int buf_size) {
    tsh_shell_it out;
    tsh_shell_ot in;

    out.length = htonl(strlen(command) + 1);
    if (!writen(sock, (char *)&out, sizeof(out))) return -1;
    if (!writen(sock, command, strlen(command) + 1)) return -1;
    if (!readn(sock, (char *)&in, sizeof(in))) return -1;

    snprintf(output_buf, buf_size, "PID: %d\nUsername: %sCWD: %sStatus: %d\nError: %d\nOutput:\n%s\n",
             getpid(), in.username, in.cwd_loc,
             ntohs(in.status), ntohs(in.error), in.out_buffer);

    return ntohs(in.status);
}

// Send exit request to TSH
int tshlib_exit(int sock) {
    tsh_exit_ot in;
    if (!readn(sock, (char *)&in, sizeof(in))) return -1;
    return ntohs(in.status);
}

// Internal helper function for connection
int connectTsh(u_short port) {
    short tsh_port = htons(port);
    u_long tsh_host = inet_addr("127.0.0.1");
    int sock;

    if ((sock = get_socket()) == -1) return -1;
    if (!do_connect(sock, tsh_host, tsh_port)) return -1;
    return sock;
}
