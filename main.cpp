#include "httpserver.h"


int main() {

    HttpServer server(8080, 6);
    server.work();
    return 0;
}
