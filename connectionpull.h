#ifndef CONNECTIONPULL_H
#define CONNECTIONPULL_H

#include <mutex>
#include <queue>

class ConnectionPull {
public:
    ConnectionPull();
    void setClient(int client);
    int getClient();
    unsigned long getClientsNumber();
private:
    std::recursive_mutex _lock;
    std::queue<int> clients;
    unsigned long clientsCount;
};

#endif // CONNECTIONPULL_H
