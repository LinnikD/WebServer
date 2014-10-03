#include "connectionpull.h"


ConnectionPull::ConnectionPull() {
    clientsCount = 0;
}

unsigned long ConnectionPull::getClientsNumber() {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return clientsCount;
}

void ConnectionPull::setClient(int client) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    clients.push(client);
    clientsCount++;
}

int ConnectionPull::getClient() {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    int client = clients.front();
    clients.pop();
    clientsCount--;
    return client;
}
