/*
   Rares Cristea, 12.03.2021
   Example of a REST endpoint with routing
   using Mathieu Stefani's example, 07 février 2016
*/
#include <algorithm>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <signal.h>
#include <boost/program_options.hpp>

#include "WindowEndpoint.cpp"

using namespace std;
using namespace Pistache;
using namespace boost::program_options;

// General advice: pay atetntion to the namespaces that you use in various contexts. Could prevent headaches.

// Some generic namespace, with a simple function we could use to test the creation of the endpoints.


int main(int argc, char *argv[]) {
    int port_number = 9080;
    int thr = 2; // Number of threads used by the server

    // Parse command line arguments
    options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("port,p", value<int>(&port_number)->default_value(9080), "set port number")
        ("threads,t", value<int>(&thr)->default_value(2), "number of threads used by the server");

    variables_map vm{};
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    if(vm.count("port")) cout << "The port is set to " << port_number << endl;
    if(vm.count("threads")) cout << "Number of threads used by the server are " << thr << endl;

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
    Port port(port_number);

    Address addr(Ipv4::any(), port);

    cout << "Window server is open" << endl;
    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    // Instance of the class that defines what the server can do.
    WindowEndpoint stats(addr);
    // Initialize and start the server
    stats.init(thr);
    stats.start();


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

    stats.stop();
}
