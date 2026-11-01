module;

#include <asio.hpp>
#include <string>
#include <iostream>
#include <memory>

module debug_server;

struct DebugServer::Impl {
    asio::io_context ioContext;
    asio::ip::tcp::acceptor acceptor;
    asio::ip::tcp::socket socket;

    Impl(int port)
        : acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
          socket(ioContext) {}
};

DebugServer::DebugServer() = default;

DebugServer::~DebugServer() = default;

void DebugServer::waitForConnection(int port) {
    pImpl = std::make_unique<Impl>(port);
    std::cout << "[DebugServer] Warte auf Verbindung vom JavaFX Debugger auf Port " << port << "...\n";

    pImpl->acceptor.accept(pImpl->socket);
    m_isConnected = true;

    std::cout << "[DebugServer] Verbindung erfolgreich hergestellt!\n";
}

void DebugServer::sendLine(const std::string& message) {
    if (!m_isConnected || !pImpl) return;
    std::string msg = message + "\n";
    asio::error_code ignored_error;
    asio::write(pImpl->socket, asio::buffer(msg), ignored_error);
}

std::string DebugServer::receiveLine() {
    if (!m_isConnected || !pImpl) return "";

    asio::streambuf buf;
    asio::error_code error;
    asio::read_until(pImpl->socket, buf, "\n", error);

    if (error) {
        m_isConnected = false;
        return "";
    }

    std::istream is(&buf);
    std::string line;
    std::getline(is, line);
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return line;
}

bool DebugServer::isConnected() const {
    return m_isConnected;
}