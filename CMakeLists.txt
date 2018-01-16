cmake_minimum_required(VERSION 3.9)
project(gSoapTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wsdl2h/soapC.cpp wsdl2h/soapH.h wsdl2h/ns2.nsmap wsdl2h/soapStub.h wsdl2h/xsd.h)

add_executable(gSoapTest ${SOURCE_FILES})

target_link_libraries(gSoapTest SimpleAmqpClient amqp-cpp gsoap++ gsoapssl++)