#include "SmartPotEndpoint.hpp"

// Not needed since they are included in the header above.
// #include <pistache/net.h>
// #include <pistache/http.h>
// #include <pistache/peer.h>
// #include <pistache/http_headers.h>
// #include <pistache/cookie.h>
// #include <pistache/router.h>
// #include <pistache/endpoint.h>
// #include <pistache/common.h>
#include <mosquitto.h>
// #include <signal.h>
#include <omp.h>
// using namespace std;
// using namespace Pistache;

using namespace std;
using namespace pot;


int main(int argc, char *argv[])
{

 // This code is needed for gracefull shutdown of the server when no longer needed.
    sigset_t signals;
    if (sigemptyset(&signals) != 0
            || sigaddset(&signals, SIGTERM) != 0
            || sigaddset(&signals, SIGINT) != 0
            || sigaddset(&signals, SIGHUP) != 0
            || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) {
        perror("install signal handler failed");
        return 1;
    }

    // Set a port on which your server to communicate
    Port port(9080);

    // Number of threads used by the server
    int thr = 2;
    omp_set_num_threads(thr);

    if (argc >= 2) {
        port = static_cast<uint16_t>(std::stol(argv[1]));

        if (argc == 3)
            thr = std::stoi(argv[2]);
    }

    Address addr(Ipv4::any(), port);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    // Instance of the class that defines what the server can do.
    SmartPotEndpoint server(addr);

    // Initialize and start the server
    server.init();
    server.start();


    // Code that waits for the shutdown sinal for the server
    int signal = 0;

    int status = sigwait(&signals, &signal);
    if (status == 0)
    {
        std::cout << "received signal " << signal << std::endl;
    }
    else
    {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    server.stop();
    
    return 0;
}