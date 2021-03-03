#ifndef APCONFIGURATOR_H
#define APCONFIGURATOR_H
#include <stdint.h>
  class ApConfigurator
  {
  private:
    
    static void heartBeatPrint(void);
    static void check_WiFi(void);
    static void loadConfigData(void);
    static void saveConfigData(void);
    static uint8_t connectMultiWiFi(void);
  public:
    ApConfigurator(/* args */);
    ~ApConfigurator();
    static void check_status(void);
    static void setupApConfigurator(void);
    static void checkRequestConfigurationPortal(void);
  };
  
 
  


#endif //ENDIF APCONFIGURATOR_H