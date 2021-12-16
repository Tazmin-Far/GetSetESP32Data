#include "JSONFile.h"

JSONFile::JSONFile(void)
{
}

void JSONFile::clear()
{
    if (SPIFFS.exists(FileName))
        SPIFFS.remove(FileName);
}

void JSONFile::begin(String FName)
{
    FileName = "/" + FName;
    makeSPIFFSReady();
}

void JSONFile::makeSPIFFSReady()
{
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
        return;
    }
}

void JSONFile::save(String VName, String VValue)
{
    String FileData = loadFromFile(FileName);
    DynamicJsonDocument doc(2048);
    deserializeJson(doc,FileData);
    JsonObject obj = doc.as<JsonObject>();
    if (obj.containsKey(VName))
    {
        FileData = editField(FileData,VName,VValue);
    }
    else
        FileData = addField(FileData,VName,VValue);
    

    
    saveToFile(FileName, FileData);
}

String JSONFile::load(String VName)
{
    String FileData = loadFromFile(FileName);
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, FileData);
    JsonObject obj = doc.as<JsonObject>();
    String ToSend = obj[VName].as<String>();
    return ToSend;
}

String JSONFile::loadFromFile(String FName)
{
    if (SPIFFS.exists(FName))
    {
        File f = SPIFFS.open(FName, FILE_READ);
        String ReturnV = f.readString();
        f.close();
        return ReturnV;
    }
    else
    {
        return "";
    }
}

void JSONFile::saveToFile(String FName, String Data)
{
    if (SPIFFS.exists(FName))
        SPIFFS.remove(FName);
    File f = SPIFFS.open(FName, FILE_WRITE);
    f.print(Data);
    f.close();
}

String JSONFile::addField(String Data, String VName, String VValue)
{
    String JString = "";

    if (Data == "")
    {
        JString = "{\""+VName+"\":\""+VValue+"\"}";
    }

    if (Data != "")
    {
        JString = Data.substring(0,Data.length()-1);
        JString += ",\""+VName+"\":\""+VValue+"\"}";
    }
    return JString;
}

String JSONFile::editField(String Data, String VName, String VValue)
{
    String JString = "";
    int keyStart = Data.indexOf("\""+VName+"\"");
    int KeyEnd = Data.indexOf("\":\"",keyStart) + 3;
    int ValueEnd = Data.indexOf("\"",KeyEnd + 1);

    JString = Data.substring(0,KeyEnd) + VValue + Data.substring(ValueEnd,Data.length());
    return JString;
}

void JSONFile::saveString(String Data)
{
    saveToFile(FileName, Data);
}