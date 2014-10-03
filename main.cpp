#include "httpserver.h"

#include <signal.h>

int main() {
    signal(SIGPIPE, SIG_IGN);
    HttpServer server(8081, 8);
    server.work();
    return 0;
}
