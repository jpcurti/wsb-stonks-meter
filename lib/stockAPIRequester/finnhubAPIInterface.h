#ifndef FINNHUBAPIINTERFACE_H
#define FINNHUBAPIINTERFACE_H

#include <ArduinoJson.h>

class finnhubAPIInterface
{
private:
    /* data */
   
    float previousClosePrice;
    float currentPrice;
    float differenceInPrice;
    String  httpRequestAddress; 
 

public:
    finnhubAPIInterface();
    ~finnhubAPIInterface();
    float getPreviousClosePrice();
    float getCurrentPrice();
    float getDifferenceInPrice();
    void requestStockCurrentPrice(String tickerSymbol, String apiKey);
};

#endif