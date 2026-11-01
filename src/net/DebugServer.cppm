module;

#include <string>
#include <memory>
#include <set>
#include <map>

export module debug_server;

export class DebugServer {
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    bool m_stepOver = false;
    bool m_isConnected = false;
    std::set<std::size_t> m_breakpoints;
    void processCommand(const std::string& cmd, bool& paused);

public:
    DebugServer();
    ~DebugServer();

    void waitForConnection(int port = 5005);
    void sendLine(const std::string& message);
    std::string receiveLine();

    [[nodiscard]] bool isConnected() const;
    void waitAtStart();
    void checkBreakpointOrPause(std::size_t lineNumber,
                                const std::map<std::string, std::string>& globals,
                                const std::map<std::string, std::string>& locals);
};