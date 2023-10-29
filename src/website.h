#ifndef WEBSITE_
#define WEBSITE_

#include "request.h"
#include "response.h"

typedef void (*handler_func)(request_t *, response_t **);

typedef struct route route_t;
struct route {
  char *path;
  handler_func handler;
};

typedef struct website website_t;
struct website {
  size_t routes_size;
  route_t *routes[256];
};

website_t *create_website();
void set_route(website_t *website, route_t *route);
handler_func get_handler(website_t *website, char *path);
route_t *create_route(char *path, handler_func handler);
#endif