#ifndef TSHLIB_H
#define TSHLIB_H

#include <stdint.h>

// Return status codes
#define TSH_SUCCESS 0
#define TSH_FAILURE -1

// Function declarations for TSH library
#ifdef __cplusplus
extern "C" {
#endif

int tsh_put(const char *host_ip, uint16_t port, const char *name, uint16_t priority, const char *tuple, uint32_t length);
int tsh_get(const char *host_ip, uint16_t port, const char *expr, char **tuple_out, char *name_out, uint16_t *priority_out, uint32_t *length_out);
int tsh_shell(const char *host_ip, uint16_t port, const char *command, char **result_out, char *username_out, char *cwd_out, uint16_t *status_out, uint16_t *error_out);
int tsh_exit(const char *host_ip, uint16_t port, uint16_t *status_out, uint16_t *error_out);

#ifdef __cplusplus
}
#endif

#endif // TSHLIB_H
