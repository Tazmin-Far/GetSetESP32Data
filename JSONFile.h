#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <FS.h>

#define FORMAT_SPIFFS_IF_FAILED true

class JSONFile
{
private:
    String FileName;

    String loadFromFile(String FName);
    void saveToFile(String FName, String Data);
    void makeSPIFFSReady();
    String addField(String Data, String VName, String VValue);
    String editField(String Data, String VName, String VValue);

public:
    JSONFile(void);
    void begin(String FName);
    //~JSONFile();
    void save(String VName, String VValue);
    String load(String VName);
    void saveString(String Data);
    void clear(void);
};