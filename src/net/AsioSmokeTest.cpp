#include "AsioSmokeTest.hpp"

#include <asio.hpp>
#include <chrono>
#include <iostream>

void runAsioSmokeTest()
{
    std::cout << "Standalone Asio version: "
              << ASIO_VERSION / 100000 << "."
              << ASIO_VERSION / 100 % 1000 << "."
              << ASIO_VERSION % 100 << '\n';

    asio::io_context context;

    asio::steady_timer timer{
        context,
        std::chrono::milliseconds{500}
    };

    timer.async_wait([](const asio::error_code& error) {
        if (error) {
            std::cerr << "Timer error: " << error.message() << '\n';
            return;
        }

        std::cout << "Asio funktioniert!\n";
    });

    context.run();
}
