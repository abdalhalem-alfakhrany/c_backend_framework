#ifndef COMMON_T
#define COMMON_T

typedef enum method method_t;
enum method { GET, POST, PUT, DELETE };

typedef struct header header_t;
struct header {
  char *name;
  char *value;
};

header_t *header_from_str(char *header_str);
void print_header(header_t *header);
void free_header(header_t *header);
header_t *create_header(char *name, char *value);
method_t method_enum(char *method_str);
char *method_str(method_t method);

#endif