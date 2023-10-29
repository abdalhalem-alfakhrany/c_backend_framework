#include "response.h"
#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

response_t *create_response(char *version, int status_code,
                            char *response_phrase) {
  response_t *res = malloc(sizeof(response_t));

  res->version = strdup(version);
  res->status_code = status_code;
  res->response_phrase = strdup(response_phrase);

  return res;
}

void response_to_str(response_t *response, char **str, size_t *str_size) {
  int last = 0;
  last += sprintf((*str + last), "%s %d %s\r\n", response->version,
                  response->status_code, response->response_phrase);
  for (int i = 0; i < response->headers_size; i++)
    last += sprintf((*str + last), "%s: %s\r\n", response->headers[i]->name,
                    response->headers[i]->value);
  last += sprintf((*str + last), "\r\n");

  last += sprintf((*str + last), "%s\n", response->body);
}

void set_response_header(response_t *response, header_t *header) {
  // TODO: check if header is already set
  if (response->headers_size < 256)
    response->headers[response->headers_size++] = header;
  else
    ; // reallocate
}

void set_response_body(response_t *response, char *body, size_t length) {
  response->body = strdup(body);
  response->body_length = length;
}

void free_response(response_t *response) {
  free(response->version);
  free(response->response_phrase);
  for (int i = 0; i < response->headers_size; i++)
    free_header(response->headers[i]);
  free(response);
}

void print_response(response_t *response) {
  printf("RESPONSE\nversion :%s\nstatus code: %d\nresponse phrase: %s\n",
         response->version, response->status_code, response->response_phrase);
  for (int i = 0; i < response->headers_size; i++)
    print_header(response->headers[i]);
}