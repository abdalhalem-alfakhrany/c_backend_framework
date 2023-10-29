#ifndef REQUEST_
#define REQUEST_

#include "common.h"

typedef struct request request_t;
struct request {
  method_t method;
  char *path;
  char *version;
  header_t **headers;
  int headers_size;
};

request_t *create_request(char *request);
void free_request(request_t *request);
void print_request(request_t *request);

#endif