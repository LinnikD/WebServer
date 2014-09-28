#include "httpserver.h"


int main() {

    HttpServer server(8086, 2);
    server.work();
    return 0;
}
