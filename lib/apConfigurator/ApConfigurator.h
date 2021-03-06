#ifndef APCONFIGURATOR_H
#define APCONFIGURATOR_H
#include <stdint.h>
  struct CustomParameter
  {
    char *label;
    char *placeholder;
    char *defaultValue;
    int length;
  };
  class ApConfigurator
  {
  private:
    
    static void heartBeatPrint(void);
    
    static void loadConfigData(void);
    static void saveConfigData(void);
    static uint8_t connectMultiWiFi(void);
    static void startConfigurationPortal(void);
  public:
    ApConfigurator(/* args */);
    ~ApConfigurator();
    static uint8_t check_WiFi(void);
    static void check_status(void);
    static void setupApConfigurator(void);
    static void checkRequestConfigurationPortal(void);

  };
  
 
  


#endif //ENDIF APCONFIGURATOR_H