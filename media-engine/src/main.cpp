#include <iostream>
#include "Server.hpp"


/* 
    understanding how is it working
*/



int main()
{   
     socketServer::Server server("0.0.0.0", 8080);
     server.start();

    return 0;
}
