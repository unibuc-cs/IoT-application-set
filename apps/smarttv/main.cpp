#include <boost/program_options.hpp>
#include "server.h"

using namespace ServerN;
using namespace boost::program_options;

int main(int argc, char *argv[])
{
    int port_number = 9080;

    // Parse command line arguments
    options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("port,p", value<int>(&port_number)->default_value(9080), "set port number");

    variables_map vm{};
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    if(vm.count("port")) cout << "The port is set to " << port_number << endl;

    Server server = Server();
    server.init(port_number);
}