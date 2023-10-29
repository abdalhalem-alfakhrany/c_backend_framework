#include "website.h"
#include <stdlib.h>
#include <string.h>

website_t *create_website() {
  website_t *website = malloc(sizeof(website_t));

  return website;
}

route_t *create_route(char *path, handler_func handler) {
  route_t *route = malloc(sizeof(route_t));

  route->path = strdup(path);
  route->handler = handler;

  return route;
}

void set_route(website_t *website, route_t *route) {
  website->routes[website->routes_size++] = route;
}

handler_func get_handler(website_t *website, char *path) {
  for (size_t i = 0; i < website->routes_size; i++) {
    if (!strcmp(path, website->routes[i]->path)) {
      return website->routes[i]->handler;
    }
  }
  return NULL;
}