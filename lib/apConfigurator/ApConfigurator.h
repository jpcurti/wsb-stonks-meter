#ifndef APCONFIGURATOR_H
#define APCONFIGURATOR_H
#include <stdint.h>
#include <vector>


  class ApConfigurator
  {
  private:
    void heartBeatPrint(void);
    void loadConfigData(void);
    void saveConfigData(void);
    uint8_t connectMultiWiFi(void);
    void startConfigurationPortal(void);
    void setupApConfigurator(void);
    
  public:
    ApConfigurator();
    ~ApConfigurator();
    uint8_t check_WiFi(void);
    void check_status(void);
    bool checkRequestConfigurationPortal(void);
    void begin();
    const char* api_key();
    const char* ticker();
  };
  
 
  


#endif //ENDIF APCONFIGURATOR_H