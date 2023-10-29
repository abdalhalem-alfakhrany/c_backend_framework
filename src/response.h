#ifndef RESPONSE_
#define RESPONSE_
#include "common.h"
#include <stddef.h>

typedef struct response response_t;
struct response {
  char *version;
  int status_code;
  char *response_phrase;
  header_t *headers[256];
  int headers_size;
  char *body;
  size_t body_length;
};

response_t *create_response(char *version, int status_code,
                            char *response_phrase);
void set_response_header(response_t *response, header_t *header);
void set_response_body(response_t *response, char *body, size_t length);
void response_to_str(response_t *response, char **str, size_t *str_size);
void free_response(response_t *response);
void print_response(response_t *response);

#endif