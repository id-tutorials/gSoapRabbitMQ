#include <iostream>
#include <sstream>
#include <amqpcpp.h>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include "wsdl2h/ns2.nsmap"
#include "wsdl2h/soapH.h"

int main() {
    AmqpClient::Channel::ptr_t connection = AmqpClient::Channel::Create(
            "localhost", 5672, "guest", "admin000"
    );
    std::string consume_tag = connection->BasicConsume("KEYWORDS_IN", "");
    struct soap *soap = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_IGNORENS);
    std::stringstream ss;

    while (true) {
        try {
            AmqpClient::Envelope::ptr_t envelope = connection->BasicConsumeMessage(consume_tag);

            std::cout << "Read message" << std::endl;

            _ns2__Envelope envelopeObj;
            ss.str(envelope->Message()->Body());
            soap->is = &ss;
            soap_read__ns2__Envelope(soap, &envelopeObj);
            ss.clear();
            soap_cleanup(soap);

            _ns4__ParseKeywords keywordsObj;
            ss.str(envelopeObj.Body);
            soap->is = &ss;
            soap_read__ns4__ParseKeywords(soap, &keywordsObj);
            std::cout << keywordsObj.Keyword.size() << " Keywords deteced." << std::endl;
            for (ns4__KeywordType *k : keywordsObj.Keyword) {
                std::cout << "Keyword: " << (std::string) k->__item << std::endl;
            }
            soap_cleanup(soap);
            ss.clear();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}