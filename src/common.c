#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

method_t method_enum(char *method_str) {
  method_t method = -1;
  if (!strcmp(method_str, "GET")) {
    method = GET;
  } else if (!strcmp(method_str, "POST")) {
    method = POST;
  } else if (!strcmp(method_str, "PUT")) {
    method = PUT;
  } else if (!strcmp(method_str, "DELETE")) {
    method = DELETE;
  }
  return method;
}

char *method_str(method_t method) {
  switch (method) {
  case GET:
    return "GET";

  case POST:
    return "POST";

  case PUT:
    return "PUT";

  case DELETE:
    return "DELETE";

  default:
    return "un implemented";
  }
}

header_t *create_header(char *name, char *value) {
  header_t *header = malloc(sizeof(header_t));

  header->name = strdup(name);
  header->value = strdup(value);

  return header;
}

header_t *header_from_str(char *header_str) {

  header_t *header = malloc(sizeof(header_t));

  header->name = strdup(strtok(header_str, ": "));
  header->value = strdup(strtok(NULL, "\r\n"));

  return header;
}

void print_header(header_t *header) {
  printf("header (name: %s, value: %s)\n", header->name, header->value);
}

void free_header(header_t *header) {
  free(header->name);
  free(header->value);
  free(header);
}