#include "esp_log.h"
#include "fmt/core.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT " AT " __FILE__ ":" TOSTRING(__LINE__) ": "
