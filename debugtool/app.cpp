#include <iostream>
#include <csignal>
#include <unistd.h>

class SignalHandler final
{
private:
    bool m_isEnd{false};
    static SignalHandler* pInstance;

    SignalHandler(){}
    ~SignalHandler(){}

    void handle(int signalNo)
    {
        m_isEnd = true;
        std::cout << "signal catch:" << signalNo << std::endl;
    }

    bool isEndInstance() const
    {
        return m_isEnd;
    }

public:
    SignalHandler(const SignalHandler &) = delete;
    SignalHandler &operator=(const SignalHandler &) = delete;
    SignalHandler(SignalHandler &&) = delete;
    SignalHandler &operator=(SignalHandler &&) = delete;

    static void handleSignal(int signalNo)
    {
        if (pInstance){
            pInstance->handle(signalNo);
        }
    }

    static void create()
    {
        if ( ! pInstance){
            pInstance = new SignalHandler();
            std::signal(SIGINT, handleSignal);
            std::signal(SIGQUIT, handleSignal);
            std::signal(SIGTERM, handleSignal);
            std::signal(SIGSEGV, handleSignal);
        }
    }

    static void destroy()
    {
        if (pInstance){
            delete pInstance;
            pInstance = nullptr;
        }
    }

    static bool isEnd()
    {
        return pInstance->isEndInstance();
    }

};
SignalHandler *SignalHandler::pInstance = nullptr;

int main()
{
    SignalHandler::create();
    while( ! SignalHandler::isEnd()){
        sleep(1);
    }
    SignalHandler::destroy();
    return 0;
}
