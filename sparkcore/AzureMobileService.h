#include "application.h"

#define NAN 999999
class AzureMobileService {
    private:
        String _azureServiceName;
        String _azureKeyValue;
        char _azureKeyChar [100];
        String _domainString;
        TCPClient _client;
    
    public:
        void configure(String, String);
        uint8_t create(String, String);
        String read(String);
        uint8_t update(String, String, String);
        uint8_t destroy(String, String);
};