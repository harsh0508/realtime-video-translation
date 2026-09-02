#include <iostream>

#include "stream_manager.hpp"

int main()
{
    std::cout << "=====================================\n";
    std::cout << " Real-Time Video Translation Engine\n";
    std::cout << "=====================================\n";

    media::StreamManager manager;

    auto stream_id = manager.create_stream();

    std::cout << "\nCreated stream ID: "
              << stream_id
              << '\n';

    std::cout << "\nMedia engine started successfully.\n";

    return 0;
}
