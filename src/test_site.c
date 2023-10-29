#include "test_site.h"
#include <string.h>
#include <stdio.h>

void home_page(request_t *request, response_t **response) {
  (*response) = create_response("HTTP/1.1", 200, "OK");
  char *body = "<html>\n"
               "\t<head>\n"
               "\t</head>\n"
               "\t<body>\n"
               "\t\t<h1>home page</h1>\n"
               "\t</body>\n"
               "</html>\n";
  set_response_header(*response, create_header("Content-Type", "text/html"));
  char len[10];
  sprintf(len, "%d", strlen(body));
  set_response_header(*response, create_header("Content-Length", len));
  set_response_body(*response, body, strlen(body));
}

void hello_world_page(request_t *request, response_t **response) {
  (*response) = create_response("HTTP/1.1", 200, "OK");
  char *body = "<html>\n"
               "\t<head>\n"
               "\t</head>\n"
               "\t<body>\n"
               "\t\t<h1>hi world :)</h1>\n"
               "\t</body>\n"
               "</html>\n";
  set_response_header(*response, create_header("Content-Type", "text/html"));
  char len[10];
  sprintf(len, "%d", strlen(body));
  set_response_header(*response, create_header("Content-Length", len));
  set_response_body(*response, body, strlen(body));
}