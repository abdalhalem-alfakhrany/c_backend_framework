#include "request.h"
#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

request_t *create_request(char *request) {
  request_t *req = malloc(sizeof(request_t));

  req->method = method_enum(strtok(request, " "));
  req->path = strtok(NULL, " ");
  req->version = strtok(NULL, "\r\n");

  int headers_size = 0;
  char *headers[256];

  while (1) {
    headers[headers_size] = strtok(NULL, "\r\n");
    if (headers[headers_size] == NULL)
      break;
    headers_size++;
  }

  req->headers = malloc(sizeof(header_t *) * headers_size);
  for (int i = 0; i < headers_size; i++) {
    req->headers[i] = header_from_str(headers[i]);
  }
  req->headers_size = headers_size;

  return req;
}

void free_request(request_t *request) {
  free(request->path);
  free(request->version);
  for (int i = 0; i < request->headers_size; i++)
    free_header(request->headers[i]);
  free(request);
}

void print_request(request_t *request) {
  printf("REQUEST\nmethod: %s\npath: %s\nversion: %s\n\n",
         method_str(request->method), request->path, request->version);
  for (int i = 0; i < request->headers_size; i++)
    print_header(request->headers[i]);
}