#include "httpserver.h"


int main() {

    HttpServer server(8080, 8);
    server.work();
    return 0;
}
