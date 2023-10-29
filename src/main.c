#include "request.h"
#include "response.h"
#include "test_site.h"
#include "website.h"
#include <ctype.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address = {.sin_family = AF_INET,
                                .sin_addr.s_addr = INADDR_ANY,
                                .sin_port = htons(8080)};
  socklen_t addrlen = sizeof(address);

  if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  website_t *website = create_website();
  set_route(website, create_route("/", home_page));
  set_route(website, create_route("/hi", hello_world_page));

  while (1) {
    int connection_fd =
        accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (connection_fd < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size * sizeof(char));
    size_t read_size = read(connection_fd, buffer, 1024 - 1);

    request_t *request = create_request(buffer);
    response_t *response;

    // if (!strcmp(request->path, "/")) {
    //   home_page(request, &response);
    // } else if (!strcmp(request->path, "/hi")) {
    //   hello_world_page(request, &response);
    // }

    handler_func handler = get_handler(website, request->path);
    handler(request, &response);

    response_to_str(response, &buffer, &buffer_size);
    send(connection_fd, buffer, buffer_size, 0);

    close(connection_fd);
  }

  close(server_fd);
  return 0;
}
