#include "AzureMobileService.h"
#include "HttpClient.h"

void AzureMobileService::configure(String serviceName, String serviceKey){
    _azureServiceName = serviceName;
    _azureKeyValue = serviceKey;
    _domainString = _azureServiceName + ".azure-mobile.net";
    _azureKeyValue.toCharArray(_azureKeyChar, 100);
}

uint8_t AzureMobileService::create(String table, String values){
    
    HttpClient http;
    
    http_header_t headers[] = {
        { "X-ZUMO-APPLICATION", _azureKeyChar },
        { "Content-Type", "application/json" },
        { NULL, NULL } // NOTE: Always terminate headers with NULL
    };
    
    http_request_t request;
    http_response_t response;
    
    request.hostname = _domainString;
    request.port = 80;
    request.path = "/tables/" + table;
    request.body = values;

    http.post(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    return response.status;
}

String AzureMobileService::read(String table) {
    
    HttpClient http;
    
    http_header_t headers[] = {
        { "X-ZUMO-APPLICATION", _azureKeyChar },
        { "Content-Type", "application/json" },
        { NULL, NULL } // NOTE: Always terminate headers with NULL
    };
    
    http_request_t request;
    http_response_t response;
    
    request.hostname = _domainString;
    request.port = 80;
    request.path = "/tables/" + table;

    http.get(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    return response.body;
}

uint8_t AzureMobileService::update(String table, String itemId, String values) {
    
    HttpClient http;
    
    http_header_t headers[] = {
        { "X-ZUMO-APPLICATION", _azureKeyChar },
        { "Content-Type", "application/json" },
        { NULL, NULL } // NOTE: Always terminate headers with NULL
    };
    
    http_request_t request;
    http_response_t response;
    
    request.hostname = _domainString;
    request.port = 80;
    request.path = "/tables/" + table + "/" + itemId;
    request.body = values;

    http.patch(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    return response.status;
}

uint8_t AzureMobileService::destroy(String table, String itemId) {
        
    HttpClient http;
    
    http_header_t headers[] = {
        { "X-ZUMO-APPLICATION", _azureKeyChar },
        { "Content-Type", "application/json" },
        { NULL, NULL } // NOTE: Always terminate headers with NULL
    };
    
    http_request_t request;
    http_response_t response;
    
    request.hostname = _domainString;
    request.port = 80;
    request.path = "/tables/" + table + "/" + itemId;

    http.del(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    return response.status;
}

