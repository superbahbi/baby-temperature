#ifndef __HTTP_CLIENT_H_
#define __HTTP_CLIENT_H_
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"
/**
 * Defines for the HTTP methods.
 */
static const char* HTTP_METHOD_GET    = "GET";
static const char* HTTP_METHOD_POST   = "POST";
static const char* HTTP_METHOD_PUT    = "PUT";
static const char* HTTP_METHOD_DELETE = "DELETE";
static const char* HTTP_METHOD_PATCH = "PATCH";
/**
 * This struct is used to pass additional HTTP headers such as API-keys.
 * Normally you pass this as an array. The last entry must have NULL as key.
 */
typedef struct
{
  const char* header;
  const char* value;
} http_header_t;
/**
 * HTTP Request struct.
 * hostname request host
 * path  request path
 * port     request port
 * body  request body
 */
typedef struct
{
  String hostname;
  IPAddress ip;
  String path;
  // TODO: Look at setting the port by default.
  //int port = 80;
  int port;
  String body;
} http_request_t;
/**
 * HTTP Response struct.
 * status  response status code.
 * body response body
Ready.