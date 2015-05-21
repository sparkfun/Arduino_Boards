
#include "Common.hpp"
#include "TcpServerSource.hpp"


using namespace update;




extern "C" void user_init(void)
{
    Sink dummySink;
    AuthChecker dummyAuth;
    Args args("");

    TcpServerSource server(dummySink, dummyAuth);
    server.begin(args);
}


