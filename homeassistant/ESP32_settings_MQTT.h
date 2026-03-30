#pragma once // защита от повторного включения файла

#include <Arduino.h> // базовые функции Arduino
#include <WiFi.h> // работа с Wi-Fi
#include <SPIFFS.h> // файловая система SPIFFS
#include <PubSubClient.h> // MQTT клиент
#include <ArduinoJson.h> // работа с JSON

#include "wifi_manager.h" // менеджер Wi-Fi
#include "fs_utils.h" // утилиты файловой системы

inline WiFiClient mqttWifiClient; // WiFi-клиент для MQTT
inline PubSubClient mqttClient(mqttWifiClient); // MQTT-клиент поверх WiFi

inline const char* mqttConfigPath = "/mqtt.json"; // путь к файлу настроек MQTT
inline String mqttHost = "192.168.0.100"; //"broker.emqx.io"; // адрес брокера
inline uint16_t mqttPort = 1883; // порт брокера
inline String mqttUsername = ""; // имя пользователя MQTT
inline String mqttPassword = ""; // пароль MQTT
inline bool mqttEnabled = true; // флаг включения MQTT
inline bool mqttIsConnected = false; // флаг подключения MQTT
inline unsigned long mqttPublishInterval = 10000; // интервал публикации
inline unsigned long mqttLastPublish = 0; // время последней публикации
inline const char* mqttAvailabilityTopic = "home/esp32/availability"; // топик доступности устройства

#if 1 // MQTT Discovery отключен (слишком много кода и не нужен)
inline const char* mqttDiscoveryPrefix = "homeassistant"; // префикс MQTT Discovery
inline bool mqttDiscoveryPending = false; // публикация после первого успешного MQTT loop

inline unsigned long mqttDiscoveryLastAttempt = 0; // время последней попытки discovery
inline const unsigned long mqttDiscoveryInterval = 250; // интервал между пакетами discovery
inline const uint8_t mqttDiscoveryBatchSize = 4; // максимум сущностей за loop
inline const uint8_t mqttDiscoveryMaxRetries = 3; // максимум попыток публикации на сущность
inline bool mqttDiscoveryFullDevicePublished = false; // полный device блок опубликован
inline size_t mqttDiscoveryLastMaxPayload = 0; // максимум payload discovery
inline size_t mqttDiscoveryRetryIndex = 0; // индекс повторной публикации
inline uint8_t mqttDiscoveryRetryCount = 0; // число повторов на сущность
inline bool mqttDiscoveryLegacyCleanupDone = false; // очистка удалённых legacy-сущностей
#endif

// inline void publishMqttAvailability(const char* payload, bool retain = true){ // публикация доступности
//   if(!mqttClient.connected()) return; // выход если нет подключения
//   mqttClient.publish(mqttAvailabilityTopic, payload, retain); // публикация статуса
// }

inline unsigned long mqttLastConnectAttempt = 0; // время последней попытки подключения
inline const unsigned long mqttConnectInterval = 5000; // интервал попыток подключения
inline unsigned long mqttLastResolveAttempt = 0; // время последней попытки DNS
inline const unsigned long mqttResolveInterval = 30000; // интервал резолва хоста
inline bool mqttHasResolvedIp = false; // флаг успешного резолва
inline IPAddress mqttResolvedIp; // резолвенный IP адрес
inline String mqttResolvedHostName; // хост для которого выполнен резолв


#if 1 // MQTT Discovery отключен (слишком много кода и не нужен)
enum DiscoveryStage {
  DISCOVERY_NONE,
  DISCOVERY_MAIN_ENTITIES,
  DISCOVERY_DONE
};

inline DiscoveryStage mqttDiscoveryStage = DISCOVERY_NONE; // этап discovery
inline size_t mqttDiscoveryIndex = 0; // индекс публикации сущностей

// mqttDiscovery публикуется один раз после успешного подключения и availability=online.
#endif

extern float DS1; // температура воды
extern float PH; // pH воды
extern float ppmCl; // уровень хлора
extern int corrected_ORP_Eh_mV; // ORP, мВ
extern String OverlayPoolTemp; // температура воды (оверлей)
extern String OverlayHeaterTemp; // температура после нагревателя (оверлей)
extern String OverlayLevelUpper; // верхний уровень (оверлей)
extern String OverlayLevelLower; // нижний уровень (оверлей)
extern String OverlayPh; // pH (оверлей)
extern String OverlayChlorine; // хлор (оверлей)
extern String OverlayFilterState; // состояние фильтрации (строка)
extern String InfoString2; // строка статуса лампы
extern String InfoStringDIN; // строка статуса DIN
extern String ThemeColor; // цвет темы
extern int MotorSpeedSetting; // скорость мотора
extern int RangeMin; // минимум диапазона
extern int RangeMax; // максимум диапазона
extern int IntInput; // целочисленный ввод
extern float FloatInput; // ввод float
extern String Timer1; // время таймера
extern String Comment; // комментарий
extern int RandomVal; // случайное значение
extern int button1; // кнопка 1
extern int button2; // кнопка 2
extern bool Power_H2O2; // состояние насоса NaOCl
extern bool Power_ACO; // состояние насоса ACO
extern bool Power_Heat; // состояние нагрева
extern bool Power_Topping_State; // состояние соленоида долива
extern bool Power_Topping; // ручной долив
extern bool Power_Drain_State; // состояние режима слива (насос включен)
extern bool Power_Drain; // ручной слив
extern bool Power_Filtr; // ручная фильтрация
extern bool Filtr_Time1; // таймер фильтрации №1
extern bool Filtr_Time2; // таймер фильтрации №2
extern bool Filtr_Time3; // таймер фильтрации №3
extern bool Power_Clean; // промывка фильтра
extern bool Clean_Time1; // таймер промывки
extern bool Pow_Ul_light; // ручное освещение
extern bool Ul_light_Time; // таймер уличного освещения
extern bool Activation_Heat; // управление нагревом
extern bool Activation_Water_Level; // контроль уровня воды
extern bool WaterLevelSensorUpper; // датчик верхнего уровня
extern bool WaterLevelSensorLower; // датчик нижнего уровня
extern bool WaterLevelSensorDrain; // датчик уровня для остановки слива
extern float PH_setting; // уставка pH
extern bool PH_Control_ACO; // контроль pH ACO
extern int ACO_Work; // период дозирования ACO
extern float PH1; // нижняя граница pH
extern float PH2; // верхняя граница pH
extern float PH1_CAL; // калибровка pH1
extern float PH2_CAL; // калибровка pH2
extern float Temper_Reference; // температура референса
extern float Temper_PH; // температура компенсации pH
extern int analogValuePH_Comp; // значение АЦП PH
extern bool NaOCl_H2O2_Control; // контроль хлора
extern int ORP_setting; // уставка ORP
extern int H2O2_Work; // период дозирования NaOCl
extern int CalRastvor256mV; // калибровочный раствор
extern int Calibration_ORP_mV; // калибровочный коэффициент ORP
extern int Lumen_Ul; // освещенность на улице
extern bool Pow_WS2815; // RGB лента (ручная)
extern bool WS2815_Time1; // таймер RGB
extern String LEDColor; // цвет RGB
extern String LedColorMode; // режим цвета
extern int LedBrightness; // яркость
extern String LedPattern; // режим подсветки
extern int LedAutoplayDuration; // период автосмены
extern bool LedAutoplay; // автосмена
extern String LedColorOrder; // порядок цветов
extern int LampTimerON; // таймер лампы ON
extern int LampTimerOFF; // таймер лампы OFF
extern int RgbTimerON; // таймер RGB ON
extern int RgbTimerOFF; // таймер RGB OFF
extern int UlLightTimerON; // таймер уличного освещения ON
extern int UlLightTimerOFF; // таймер уличного освещения OFF
extern int Sider_heat; // уставка нагрева
extern bool RoomTemper; // контроль температуры в помещении
extern float RoomTempOn; // граница включения отопления
extern float RoomTempOff; // граница выключения отопления
extern bool Power_Warm_floor_heating; // обогрев пола
extern String SetLamp; // режим лампы
extern String SetRGB; // режим RGB
extern bool Lamp; // состояние лампы
extern bool Lamp_autosvet; // авто-режим лампы
extern bool Power_Time1; // режим таймера лампы
extern bool Pow_WS2815_autosvet; // авто-режим RGB
extern String DaysSelect; // выбранные дни промывки
class UIRegistry; // forward declaration
extern UIRegistry ui; // доступ к UI-реестру таймеров
void syncCleanDaysFromSelection(); // синхронизация дней промывки
String uiValueForId(const String &id); // получение значения UI по id
bool uiApplyValueForId(const String &id, const String &value); // применение значения UI по id

String formatMinutesToTime(uint16_t minutes); // форматирование минут в HH:MM
bool mqttApplyTimerField(const String &fieldId, const String &value); // применить значение таймера
uint16_t mqttTimerOnMinutes(const String &id); // время включения таймера
uint16_t mqttTimerOffMinutes(const String &id); // время выключения таймера
void mqttApplyDaysSelect(const String &value); // применить выбор дней промывки
bool mqttDaysSelectContains(const char* dayToken); // проверить включен ли день в DaysSelect

// MQTT-помощники для таймеров/дней (перенесены сюда, чтобы MQTT-логика была в одном файле)
inline bool mqttApplyTimerField(const String &fieldId, const String &value){
  return ui.updateTimerField(fieldId, value);
}

inline uint16_t mqttTimerOnMinutes(const String &id){
  return ui.timer(id).on;
}

inline uint16_t mqttTimerOffMinutes(const String &id){
  return ui.timer(id).off;
}

inline void mqttApplyDaysSelect(const String &value){
  String next = value;
  next.trim();

  if(next.startsWith("toggle:") || next.startsWith("add:") || next.startsWith("remove:")){
    bool removeDay = next.startsWith("remove:");
    const int prefixLen = next.startsWith("toggle:") ? 7 : (removeDay ? 7 : 4);
    const String day = next.substring(prefixLen);
    String marked = "," + DaysSelect + ",";
    const String token = day + ",";
    const bool hasDay = marked.indexOf(token) >= 0;
    if((next.startsWith("toggle:") && hasDay) || (removeDay && hasDay)){
      marked.replace(token, ",");
    } else if((next.startsWith("toggle:") && !hasDay) || (!removeDay && !next.startsWith("toggle:") && !hasDay)){
      marked += day + ",";
    }
    while(marked.indexOf(",,") >= 0) marked.replace(",,", ",");
    if(marked.startsWith(",")) marked.remove(0, 1);
    if(marked.endsWith(",")) marked.remove(marked.length() - 1);
    next = marked;
  }

  DaysSelect = next;
  syncCleanDaysFromSelection();
  saveValue<String>("DaysSelect", DaysSelect);
}

inline bool mqttDaysSelectContains(const char* dayToken){
  if(dayToken == nullptr || dayToken[0] == '\0') return false;
  const String marked = "," + DaysSelect + ",";
  const String token = String(dayToken) + ",";
  return marked.indexOf(token) >= 0;
}

inline bool mqttApplyDualRangeInt(const String &payload, int &minRef, int &maxRef,
                                  const char* minKey, const char* maxKey){
  int sep = payload.indexOf('-');
  if(sep < 0) return false;
  int nextMin = payload.substring(0, sep).toInt();
  int nextMax = payload.substring(sep + 1).toInt();
  if(nextMin > nextMax){
    int temp = nextMin;
    nextMin = nextMax;
    nextMax = temp;
  }
  minRef = nextMin;
  maxRef = nextMax;
  saveValue<int>(minKey, minRef);
  saveValue<int>(maxKey, maxRef);
  return true;
}

inline bool mqttApplyDualRangeFloat(const String &payload, float &minRef, float &maxRef,
                                    const char* minKey, const char* maxKey){
  int sep = payload.indexOf('-');
  if(sep < 0) return false;
  float nextMin = payload.substring(0, sep).toFloat();
  float nextMax = payload.substring(sep + 1).toFloat();
  if(nextMin > nextMax){
    float temp = nextMin;
    nextMin = nextMax;
    nextMax = temp;
  }
  minRef = nextMin;
  maxRef = nextMax;
  saveValue<float>(minKey, minRef);
  saveValue<float>(maxKey, maxRef);
  return true;
}


inline void publishMqttStateString(const char* topic, const String &value); // forward declaration
inline void publishMqttStateBool(const char* topic, bool value); // forward declaration

inline bool mqttPayloadIsOn(String payload){ // проверка включения
  payload.trim(); // очистка
  payload.toLowerCase(); // нижний регистр
  return payload == "1" || payload == "on" || payload == "true"; // ON
}

inline bool mqttPayloadIsOff(String payload){ // проверка выключения
  payload.trim(); // очистка
  payload.toLowerCase(); // нижний регистр
  return payload == "0" || payload == "off" || payload == "false"; // OFF
}

inline bool mqttIsAllowedMode(String value){ // проверка режима
  value.trim();
  value.toLowerCase();
  return value == "off" || value == "on" || value == "auto" || value == "timer"; // допустимые режимы
}

inline String mqttNormalizedMode(String value){
  value.trim();
  value.toLowerCase();
  return value;
}

inline void mqttApplyLampMode(const String &rawMode){
  SetLamp = mqttNormalizedMode(rawMode);
  if(SetLamp == "on"){
    Lamp = true;
    Lamp_autosvet = false;
    Power_Time1 = false;
  } else if(SetLamp == "auto"){
    Lamp = false;
    Lamp_autosvet = true;
    Power_Time1 = false;
  } else if(SetLamp == "timer"){
    Lamp = false;
    Lamp_autosvet = false;
    Power_Time1 = true;
  } else {
    Lamp = false;
    Lamp_autosvet = false;
    Power_Time1 = false;
  }

  saveValue<String>("SetLamp", SetLamp);
  saveButtonState("button_Lamp", Lamp ? 1 : 0);
  saveValue<int>("Lamp_autosvet", Lamp_autosvet ? 1 : 0);
  saveValue<int>("Power_Time1", Power_Time1 ? 1 : 0);
}

inline void mqttApplyRgbMode(const String &rawMode){
  SetRGB = mqttNormalizedMode(rawMode);
  if(SetRGB == "on"){
    Pow_WS2815 = true;
    Pow_WS2815_autosvet = false;
    WS2815_Time1 = false;
  } else if(SetRGB == "auto"){
    Pow_WS2815 = false;
    Pow_WS2815_autosvet = true;
    WS2815_Time1 = false;
  } else if(SetRGB == "timer"){
    Pow_WS2815 = false;
    Pow_WS2815_autosvet = false;
    WS2815_Time1 = true;
  } else {
    Pow_WS2815 = false;
    Pow_WS2815_autosvet = false;
    WS2815_Time1 = false;
  }

  saveValue<String>("SetRGB", SetRGB);
  saveButtonState("button_WS2815", Pow_WS2815 ? 1 : 0);
  saveValue<int>("Pow_WS2815", Pow_WS2815 ? 1 : 0);
  saveValue<int>("Pow_WS2815_autosvet", Pow_WS2815_autosvet ? 1 : 0);
  saveValue<int>("WS2815_Time1", WS2815_Time1 ? 1 : 0);
}

inline String mqttLedAutoplayState(){
  return LedAutoplay ? "Автоматически" : "Вручную";
}

inline bool mqttParseLedAutoplay(const String &rawValue, bool &parsedValue){
  String value = rawValue;
  value.trim();
  value.toLowerCase();

  if(value == "1" || value == "true" || value == "on" || value == "auto" || value == "автоматически" || value == "автомат"){
    parsedValue = true;
    return true;
  }

  if(value == "0" || value == "false" || value == "off" || value == "manual" || value == "вручную" || value == "ручной"){
    parsedValue = false;
    return true;
  }

  return false;
}

inline void handleMqttCommandMessage(char* topic, byte* payload, unsigned int length){ // обработка MQTT команд
  String topicStr(topic); // топик
  String message; // payload строкой
  message.reserve(length); // резерв
  for(unsigned int i = 0; i < length; ++i){
    message += static_cast<char>(payload[i]); // сбор payload
  }
  message.trim(); // очистка

  if(topicStr == "home/esp32/Power_Filtr/set"){
    Power_Filtr = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Power_Filtr", Power_Filtr ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Power_Filtr", Power_Filtr); // публикация
    return;
  }

  if(topicStr == "home/esp32/Filtr_Time1/set"){
    Filtr_Time1 = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Filtr_Time1", Filtr_Time1 ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Filtr_Time1", Filtr_Time1); // публикация
    return;
  }

  if(topicStr == "home/esp32/Filtr_Time2/set"){
    Filtr_Time2 = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Filtr_Time2", Filtr_Time2 ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Filtr_Time2", Filtr_Time2); // публикация
    return;
  }

  if(topicStr == "home/esp32/Filtr_Time3/set"){
    Filtr_Time3 = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Filtr_Time3", Filtr_Time3 ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Filtr_Time3", Filtr_Time3); // публикация
    return;
  }

  if(topicStr == "home/esp32/Power_Clean/set"){
    Power_Clean = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Power_Clean", Power_Clean ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Power_Clean", Power_Clean); // публикация
    return;
  }

    if(topicStr == "home/esp32/Power_Drain/set"){
    Power_Drain = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Power_Drain", Power_Drain ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Power_Drain", Power_Drain); // публикация
    return;
  }


  if(topicStr == "home/esp32/Clean_Time1/set"){
    Clean_Time1 = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Clean_Time1", Clean_Time1 ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Clean_Time1", Clean_Time1); // публикация
    return;
  }

  if(topicStr == "home/esp32/DaysSelect/set"){
    mqttApplyDaysSelect(message); // обновление строки дней
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect); // публикация
     publishMqttStateBool("home/esp32/DaysMonToggle", mqttDaysSelectContains("Mon"));
    publishMqttStateBool("home/esp32/DaysTueToggle", mqttDaysSelectContains("Tue"));
    publishMqttStateBool("home/esp32/DaysWedToggle", mqttDaysSelectContains("Wed"));
    publishMqttStateBool("home/esp32/DaysThuToggle", mqttDaysSelectContains("Thu"));
    publishMqttStateBool("home/esp32/DaysFriToggle", mqttDaysSelectContains("Fri"));
    publishMqttStateBool("home/esp32/DaysSatToggle", mqttDaysSelectContains("Sat"));
    publishMqttStateBool("home/esp32/DaysSunToggle", mqttDaysSelectContains("Sun"));
    return;
  }

  if(topicStr == "home/esp32/DaysMonToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Mon" : "remove:Mon");
    publishMqttStateBool("home/esp32/DaysMonToggle", mqttDaysSelectContains("Mon"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysTueToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Tue" : "remove:Tue");
    publishMqttStateBool("home/esp32/DaysTueToggle", mqttDaysSelectContains("Tue"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysWedToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Wed" : "remove:Wed");
    publishMqttStateBool("home/esp32/DaysWedToggle", mqttDaysSelectContains("Wed"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysThuToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Thu" : "remove:Thu");
    publishMqttStateBool("home/esp32/DaysThuToggle", mqttDaysSelectContains("Thu"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysFriToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Fri" : "remove:Fri");
    publishMqttStateBool("home/esp32/DaysFriToggle", mqttDaysSelectContains("Fri"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysSatToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Sat" : "remove:Sat");
    publishMqttStateBool("home/esp32/DaysSatToggle", mqttDaysSelectContains("Sat"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }

  if(topicStr == "home/esp32/DaysSunToggle/set"){
    mqttApplyDaysSelect(mqttPayloadIsOn(message) ? "add:Sun" : "remove:Sun");
    publishMqttStateBool("home/esp32/DaysSunToggle", mqttDaysSelectContains("Sun"));
    publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
    return;
  }


  if(topicStr == "home/esp32/RoomTempRange/set"){
    if(mqttApplyDualRangeFloat(message, RoomTempOn, RoomTempOff, "RoomTempOn", "RoomTempOff")){
      publishMqttStateString("home/esp32/RoomTempRange", String(RoomTempOn, 1) + "-" + String(RoomTempOff, 1));
    }
    return;
  }

  if(topicStr == "home/esp32/Float_PH_Slider/set") {
    mqttApplyDualRangeFloat(message, PH1, PH2, "PH1_MIN", "PH2_MAX");
    return;
  }


  if(topicStr == "home/esp32/FiltrTimer1_ON/set"){
    if(mqttApplyTimerField("FiltrTimer1_ON", message)){
      publishMqttStateString("home/esp32/FiltrTimer1_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer1")));
    }
    return;
  }

  if(topicStr == "home/esp32/Float_PH_Slider/set") {
    mqttApplyDualRangeFloat(message, PH1, PH2, "PH1_MIN", "PH2_MAX");
    return;
  }

  if(topicStr == "home/esp32/FiltrTimer2_ON/set"){
    if(mqttApplyTimerField("FiltrTimer2_ON", message)){
      publishMqttStateString("home/esp32/FiltrTimer2_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer2")));
    }
    return;
  }

  if(topicStr == "home/esp32/FiltrTimer2_OFF/set"){
    if(mqttApplyTimerField("FiltrTimer2_OFF", message)){
      publishMqttStateString("home/esp32/FiltrTimer2_OFF", formatMinutesToTime(mqttTimerOffMinutes("FiltrTimer2")));
    }
    return;
  }

  if(topicStr == "home/esp32/FiltrTimer3_ON/set"){
    if(mqttApplyTimerField("FiltrTimer3_ON", message)){
      publishMqttStateString("home/esp32/FiltrTimer3_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer3")));
    }
    return;
  }

  if(topicStr == "home/esp32/FiltrTimer3_OFF/set"){
    if(mqttApplyTimerField("FiltrTimer3_OFF", message)){
      publishMqttStateString("home/esp32/FiltrTimer3_OFF", formatMinutesToTime(mqttTimerOffMinutes("FiltrTimer3")));
    }
    return;
  }

  if(topicStr == "home/esp32/CleanTimer1_ON/set"){
    if(mqttApplyTimerField("CleanTimer1_ON", message)){
      publishMqttStateString("home/esp32/CleanTimer1_ON", formatMinutesToTime(mqttTimerOnMinutes("CleanTimer1")));
    }
    return;
  }

  if(topicStr == "home/esp32/CleanTimer1_OFF/set"){
    if(mqttApplyTimerField("CleanTimer1_OFF", message)){
      publishMqttStateString("home/esp32/CleanTimer1_OFF", formatMinutesToTime(mqttTimerOffMinutes("CleanTimer1")));
    }
    return;
  }

 if(topicStr == "home/esp32/LampTimer_ON/set"){
    if(mqttApplyTimerField("LampTimer_ON", message)){
      publishMqttStateString("home/esp32/LampTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("LampTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/LampTimer_OFF/set"){
    if(mqttApplyTimerField("LampTimer_OFF", message)){
      publishMqttStateString("home/esp32/LampTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("LampTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/RgbTimer_ON/set"){
    if(mqttApplyTimerField("RgbTimer_ON", message)){
      publishMqttStateString("home/esp32/RgbTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("RgbTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/RgbTimer_OFF/set"){
    if(mqttApplyTimerField("RgbTimer_OFF", message)){
      publishMqttStateString("home/esp32/RgbTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("RgbTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/UlLightTimer_ON/set"){
    if(mqttApplyTimerField("UlLightTimer_ON", message)){
      publishMqttStateString("home/esp32/UlLightTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("UlLightTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/UlLightTimer_OFF/set"){
    if(mqttApplyTimerField("UlLightTimer_OFF", message)){
      publishMqttStateString("home/esp32/UlLightTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("UlLightTimer")));
    }
    return;
  }

  if(topicStr == "home/esp32/Pow_Ul_light/set"){
    Pow_Ul_light = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Pow_Ul_light", Pow_Ul_light ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Pow_Ul_light", Pow_Ul_light); // публикация
    return;
  }

  if(topicStr == "home/esp32/Activation_Heat/set"){
    Activation_Heat = mqttPayloadIsOn(message); // обновление состояния
    saveValue<int>("Activation_Heat", Activation_Heat ? 1 : 0); // сохранение
    publishMqttStateBool("home/esp32/Activation_Heat", Activation_Heat); // публикация
    return;
  }

  if(topicStr == "home/esp32/SetLamp/set"){
    if(mqttIsAllowedMode(message)){
      mqttApplyLampMode(message);
      publishMqttStateString("home/esp32/SetLamp", SetLamp); // публикация
    }
    return;
  }

  if(topicStr == "home/esp32/SetRGB/set"){
    if(mqttIsAllowedMode(message)){
      mqttApplyRgbMode(message);
      publishMqttStateString("home/esp32/SetRGB", SetRGB); // публикация
      publishMqttStateBool("home/esp32/Pow_WS2815", Pow_WS2815);
      publishMqttStateBool("home/esp32/WS2815_Time1", WS2815_Time1);
    }
    return;
  }

    if(topicStr == "home/esp32/LedAutoplay/set"){
    bool autoplayState = LedAutoplay;
    if(mqttParseLedAutoplay(message, autoplayState)){
      LedAutoplay = autoplayState;
      saveValue<int>("LedAutoplay", LedAutoplay ? 1 : 0);
      publishMqttStateString("home/esp32/LedAutoplay", mqttLedAutoplayState());
    }
    return;
  }

  if(topicStr == "home/esp32/button/restart/set"){
    ESP.restart(); // перезапуск
    return;
  }
  
  if(topicStr.startsWith("home/esp32/") && topicStr.endsWith("/set")){
    const String basePrefix = "home/esp32/";
    const size_t prefixLen = basePrefix.length();
    const size_t suffixLen = 4; // "/set"
    if(topicStr.length() > prefixLen + suffixLen){
      String id = topicStr.substring(prefixLen, topicStr.length() - suffixLen);
        if(id == "button1" || id == "button2" || id == "MotorSpeed" ||
         id == "IntInput" || id == "FloatInput" || id == "RangeSlider"){
        return;
      }

            if(id == "Temper_PH" || id == "Temper_Reference" ||
         id == "Float_PH_Slider" || id == "PH2_CAL" ||
         id == "Power_H2O2_Button" || id == "Calibration_ORP_mV" ||
         id == "CalRastvor256mV" || id == "Power_ACO_Button" ||
         id == "ORP_setting"){
        return;
      }

      if(uiApplyValueForId(id, message)){
        publishMqttStateString((basePrefix + id).c_str(), uiValueForId(id));
      }
    }
    return;
  }
}

#if 1 // MQTT Discovery отключен (слишком много кода и не нужен)
inline String mqttDiscoveryDeviceId(){ // идентификатор устройства для Discovery
  String id = WiFi.macAddress(); // MAC-адрес
  id.replace(":", ""); // удаление двоеточий
  id.toLowerCase(); // приведение к нижнему регистру
  return "espdash_" + id; // итоговый id
}

inline String mqttDiscoveryDeviceName(){ // имя устройства для Discovery
  return "ESP32 " + WiFi.macAddress(); // имя устройства
}

inline void publishMqttAvailability(const char* payload, bool retain = true){ // публикация доступности
  if(!mqttClient.connected()) return; // выход если нет подключения
  mqttClient.publish(mqttAvailabilityTopic, payload, retain); // публикация статуса
}

inline void publishDiscoveryDeviceBlock(JsonDocument &doc, const String &deviceId, const String &deviceName){ // блок device
  JsonObject device = doc["device"].to<JsonObject>(); // объект устройства
  JsonArray identifiers = device["identifiers"].to<JsonArray>(); // идентификаторы
  identifiers.add(deviceId); // добавление id
  device["name"] = deviceName; // имя устройства
  device["model"] = "ESP32-S3"; // модель
  device["manufacturer"] = "Espressif"; // производитель
}

inline void publishDiscoveryDeviceBlockMinimal(JsonDocument &doc, const String &deviceId){ // минимальный блок device
  JsonObject device = doc["device"].to<JsonObject>(); // объект устройства
  JsonArray identifiers = device["identifiers"].to<JsonArray>(); // идентификаторы
  identifiers.add(deviceId); // добавление id
}

struct MqttDiscoveryPublishResult {
  bool published;
  size_t payloadLength;
  String topic;
};

inline bool mqttDiscoveryPayloadFits(const String &topic, size_t payloadLength){ // проверка размера
  const size_t bufferSize = mqttClient.getBufferSize();
  const size_t reserved = 12; // запас на заголовки
  if(bufferSize <= reserved) return false;
  return (topic.length() + payloadLength + reserved) <= bufferSize;
}

struct MqttDiscoveryEntity {
  const char* component;
  const char* id;
  const char* name;
  const char* stateTopic;
  const char* commandTopic;
  const char* deviceClass;
  const char* unit;
  const char* stateClass;
  const char* valueTemplate;
  const char* payloadOn;
  const char* payloadOff;
  const char* payloadPress = nullptr;
  const char* minValue = nullptr;
  const char* maxValue = nullptr;
  const char* stepValue = nullptr;
};

enum MqttDiscoveryGroup {
  DISCOVERY_GROUP_OVERVIEW,
  DISCOVERY_GROUP_CONTROLS,
  DISCOVERY_GROUP_FILTRATION,
  DISCOVERY_GROUP_BACKWASH,
  DISCOVERY_GROUP_LAMP,
  DISCOVERY_GROUP_RGB,
  DISCOVERY_GROUP_WATER_LEVEL,
  DISCOVERY_GROUP_POOL_TEMPERATURE,
  DISCOVERY_GROUP_PH_NAOCL,
  DISCOVERY_GROUP_CHLORINE_ACO,
  DISCOVERY_GROUP_ROOM_TEMPERATURE,
  DISCOVERY_GROUP_OUTDOOR_LIGHTING
};

inline MqttDiscoveryGroup mqttDiscoveryGroupForEntityId(const char* id){
  String entityId = id ? String(id) : String();
  entityId.trim();

if(entityId == "OverlayPoolTemp" || entityId == "OverlayHeaterTemp" ||
     entityId == "OverlayLevelUpper" || entityId == "OverlayLevelLower" ||
     entityId == "OverlayPh" || entityId == "OverlayChlorine" ||
     entityId == "OverlayFilterState") return DISCOVERY_GROUP_OVERVIEW;

  if(entityId == "Power_Filtr" || entityId == "Filtr_Time1" ||
     entityId == "Filtr_Time2" || entityId == "Filtr_Time3" ||
     entityId == "FiltrTimer1_ON" || entityId == "FiltrTimer1_OFF" ||
     entityId == "FiltrTimer2_ON" || entityId == "FiltrTimer2_OFF" ||
     entityId == "FiltrTimer3_ON" || entityId == "FiltrTimer3_OFF") return DISCOVERY_GROUP_FILTRATION;

  if(entityId == "Power_Clean" || entityId == "Clean_Time1" ||
     entityId == "CleanTimer1_ON" || entityId == "CleanTimer1_OFF" ||
     entityId == "DaysMonToggle" || entityId == "DaysTueToggle" ||
     entityId == "DaysWedToggle" || entityId == "DaysThuToggle" ||
     entityId == "DaysFriToggle" || entityId == "DaysSatToggle" ||
     entityId == "DaysSunToggle") return DISCOVERY_GROUP_BACKWASH;

  if(entityId == "InfoString2" || entityId == "SetLamp" ||
     entityId == "Lumen_Ul" || entityId == "LampTimer_ON" ||
     entityId == "LampTimer_OFF") return DISCOVERY_GROUP_LAMP;

  if(entityId == "WS2815_Time1" || entityId == "Pow_WS2815" ||
     entityId == "SetRGB" || entityId == "LEDColor" || entityId == "LedBrightness" ||
    entityId == "LED Brightness" || entityId.equalsIgnoreCase("ledbrightness") ||
     entityId == "LedColorMode" || entityId == "LedPattern" ||
     entityId == "LedAutoplay" || entityId == "LedAutoplayDuration" ||
     entityId == "LedColorOrder" || entityId == "RgbTimer_ON" ||
     entityId == "RgbTimer_OFF") return DISCOVERY_GROUP_RGB;

  if(entityId == "Activation_Water_Level" || entityId == "WaterLevelSensorUpper" ||
     entityId == "WaterLevelSensorLower" || entityId == "WaterLevelSensorDrain" || entityId == "Power_Topping_State" ||
     entityId == "Power_Topping" || entityId == "Power_Drain_State" || entityId == "Power_Drain" || entityId == "InfoStringDIN") return DISCOVERY_GROUP_WATER_LEVEL;

  if(entityId == "DS1" || entityId == "Sider_heat" ||
     entityId == "Activation_Heat" || entityId == "Power_Heat") return DISCOVERY_GROUP_POOL_TEMPERATURE;

  if(entityId == "PH" || entityId == "PH_Control_ACO" ||
     entityId == "PH_setting" || entityId == "analogValuePH" ||
     entityId == "Float_PH_Slider" || entityId == "PH2_CAL" ||
     entityId == "Temper_Reference" || entityId == "Temper_PH" ||
     entityId == "Power_H2O2_Button" || entityId == "Power_ACO" ||
     entityId == "ACO_Work") return DISCOVERY_GROUP_PH_NAOCL;

  if(entityId == "ppmCl" || entityId == "corrected_ORP_Eh_mV" ||
     entityId == "Power_H2O2" ||
     entityId == "NaOCl_H2O2_Control" || entityId == "ORP_setting" ||
     entityId == "CalRastvor256mV" || entityId == "Calibration_ORP_mV" ||
     entityId == "Power_ACO_Button" ||
     entityId == "H2O2_Work") return DISCOVERY_GROUP_CHLORINE_ACO;

  if(entityId == "RoomTemp" || entityId == "RoomTempRange" ||
     entityId == "RoomTemper" || entityId == "Power_Warm_floor_heating") return DISCOVERY_GROUP_ROOM_TEMPERATURE;

  if(entityId == "Pow_Ul_light" || entityId == "Ul_light_Time" ||
     entityId == "UlLightTimer_ON" || entityId == "UlLightTimer_OFF") return DISCOVERY_GROUP_OUTDOOR_LIGHTING;

  return DISCOVERY_GROUP_OVERVIEW;
}

inline const char* mqttDiscoveryGroupSuffix(MqttDiscoveryGroup group){
  switch(group){
    case DISCOVERY_GROUP_CONTROLS: return "controls";
    case DISCOVERY_GROUP_FILTRATION: return "filtration";
    case DISCOVERY_GROUP_BACKWASH: return "backwash";
    case DISCOVERY_GROUP_LAMP: return "lamp";
    case DISCOVERY_GROUP_RGB: return "rgb";
    case DISCOVERY_GROUP_WATER_LEVEL: return "water_level";
    case DISCOVERY_GROUP_POOL_TEMPERATURE: return "pool_temperature";
    case DISCOVERY_GROUP_PH_NAOCL: return "ph_naocl";
    case DISCOVERY_GROUP_CHLORINE_ACO: return "chlorine_aco";
    case DISCOVERY_GROUP_ROOM_TEMPERATURE: return "room_temperature";
    case DISCOVERY_GROUP_OUTDOOR_LIGHTING: return "outdoor_lighting";
    case DISCOVERY_GROUP_OVERVIEW:
    default: return "overview";
  }
}

inline const char* mqttDiscoveryGroupName(MqttDiscoveryGroup group){
  switch(group){
    case DISCOVERY_GROUP_CONTROLS: return "Controls";
    case DISCOVERY_GROUP_FILTRATION: return "Настройка фильтрации";
    case DISCOVERY_GROUP_BACKWASH: return "Настройка промывки фильтра";
    case DISCOVERY_GROUP_LAMP: return "Управление лампой";
    case DISCOVERY_GROUP_RGB: return "Управление RGB подсветкой";
    case DISCOVERY_GROUP_WATER_LEVEL: return "Контроль уровня воды";
    case DISCOVERY_GROUP_POOL_TEMPERATURE: return "Контроль температуры";
    case DISCOVERY_GROUP_PH_NAOCL: return "Контроль PH (NaOCl)";
    case DISCOVERY_GROUP_CHLORINE_ACO: return "Контроль хлора CL (ACO)";
    case DISCOVERY_GROUP_ROOM_TEMPERATURE: return "Контроль температуры в помещении";
    case DISCOVERY_GROUP_OUTDOOR_LIGHTING: return "Уличное освещение";
    case DISCOVERY_GROUP_OVERVIEW:
    default: return "Общая информация по бассейну";
  }
}

inline void publishDiscoveryDeviceBlockGrouped(JsonDocument &doc,
                                               const String &rootDeviceId,
                                               const String &rootDeviceName,
                                               MqttDiscoveryGroup group){
  JsonObject device = doc["device"].to<JsonObject>();
  JsonArray identifiers = device["identifiers"].to<JsonArray>();
  const String groupDeviceId = rootDeviceId + "_" + mqttDiscoveryGroupSuffix(group);
  identifiers.add(groupDeviceId);
  String compactRootName = rootDeviceName;
  if(compactRootName.startsWith("ESP32 ") && compactRootName.length() > 5){
    compactRootName = "ESP32 " + compactRootName.substring(compactRootName.length() - 5);
  }
  device["name"] = compactRootName + " • " + mqttDiscoveryGroupName(group);
  device["model"] = "ESP32-S3";
  device["manufacturer"] = "Espressif";
  if(group != DISCOVERY_GROUP_OVERVIEW) device["via_device"] = rootDeviceId;
}

inline MqttDiscoveryPublishResult publishMqttDiscoveryEntity(const MqttDiscoveryEntity &entity,
                                       const String &deviceId,
                                       const String &deviceName,
                                       bool minimalDevice){ // публикация сущности
                                          (void)minimalDevice;
  JsonDocument doc; // JSON-документ
  const String uniqueId = deviceId + "_" + entity.id; // уникальный id
  const String topic = String(mqttDiscoveryPrefix) + "/" + entity.component + "/" + uniqueId + "/config"; // топик config

  doc["unique_id"] = uniqueId; // unique_id
  doc["name"] = entity.name; // name
  doc["availability_topic"] = mqttAvailabilityTopic; // availability_topic
  doc["payload_available"] = "online"; // payload available
  doc["payload_not_available"] = "offline"; // payload not available
  if(entity.stateTopic) doc["state_topic"] = entity.stateTopic; // state_topic
  if(entity.commandTopic) doc["command_topic"] = entity.commandTopic; // command_topic
  if(entity.deviceClass) doc["device_class"] = entity.deviceClass; // device_class
  if(entity.unit) doc["unit_of_measurement"] = entity.unit; // unit_of_measurement
  if(entity.stateClass) doc["state_class"] = entity.stateClass; // state_class
  if(entity.valueTemplate) doc["value_template"] = entity.valueTemplate; // value_template
  if(entity.payloadOn) doc["payload_on"] = entity.payloadOn; // payload_on
  if(entity.payloadOff) doc["payload_off"] = entity.payloadOff; // payload_off
  if(entity.payloadPress) doc["payload_press"] = entity.payloadPress; // payload_press
  if(entity.minValue) doc["min"] = atof(entity.minValue); // min (number entities)
  if(entity.maxValue) doc["max"] = atof(entity.maxValue); // max (number entities)
  if(entity.stepValue) doc["step"] = atof(entity.stepValue); // step (number entities)

    publishDiscoveryDeviceBlockGrouped(doc, deviceId, deviceName, mqttDiscoveryGroupForEntityId(entity.id));

  String payload; // строка JSON
  serializeJson(doc, payload); // сериализация JSON
  bool published = mqttClient.publish(topic.c_str(), payload.c_str(), true); // публикация config с retain
  return {published, payload.length(), topic};
}

inline MqttDiscoveryPublishResult publishMqttDiscoverySelect(const char* id,
                                       const char* name,
                                       const char* stateTopic,
                                       const char* commandTopic,
                                       const char* const* options,
                                       size_t optionsCount,
                                       const String &deviceId,
                                       const String &deviceName,
                                       bool minimalDevice,
                                       bool includeOptions){ // публикация select
                                          (void)minimalDevice;
  JsonDocument doc; // JSON-документ
  const String uniqueId = deviceId + "_" + id; // уникальный id
  const String topic = String(mqttDiscoveryPrefix) + "/select/" + uniqueId + "/config"; // топик config

  doc["unique_id"] = uniqueId; // unique_id
  doc["name"] = name; // name
  doc["availability_topic"] = mqttAvailabilityTopic; // availability_topic
  doc["payload_available"] = "online"; // payload available
  doc["payload_not_available"] = "offline"; // payload not available
  doc["state_topic"] = stateTopic; // state_topic
  doc["command_topic"] = commandTopic; // command_topic
  if(includeOptions){
    JsonArray optionsArray = doc["options"].to<JsonArray>(); // options
    for(size_t i = 0; i < optionsCount; ++i){
      optionsArray.add(options[i]);
    }
  }

  publishDiscoveryDeviceBlockGrouped(doc, deviceId, deviceName, mqttDiscoveryGroupForEntityId(id));

  String payload; // строка JSON
  serializeJson(doc, payload); // сериализация JSON
  bool published = mqttClient.publish(topic.c_str(), payload.c_str(), true); // публикация config с retain
  return {published, payload.length(), topic};
}

inline void publishHomeAssistantDiscovery(){ // публикация MQTT Discovery
  if(!mqttClient.connected()) return; // выход если нет подключения
  if(mqttDiscoveryStage == DISCOVERY_DONE){ // завершено
    mqttDiscoveryPending = false; // сброс ожидания
    return;
  }

  const unsigned long now = millis(); // текущее время
  if(now - mqttDiscoveryLastAttempt < mqttDiscoveryInterval) return; // интервал между пакетами
  mqttDiscoveryLastAttempt = now; // обновление таймера

  const String deviceId = mqttDiscoveryDeviceId(); // id устройства
  const String deviceName = mqttDiscoveryDeviceName(); // имя устройства
  
   if(!mqttDiscoveryLegacyCleanupDone){
    struct LegacyEntityConfig { const char* component; const char* id; };
    static const LegacyEntityConfig legacyEntities[] = {
      {"text", "DaysSelect"},
      {"button", "DaysMonToggle"},
      {"button", "DaysTueToggle"},
      {"button", "DaysWedToggle"},
      {"button", "DaysThuToggle"},
      {"button", "DaysFriToggle"},
      {"button", "DaysSatToggle"},
      {"button", "DaysSunToggle"},
      {"switch", "DaysMonToggle"},
      {"switch", "DaysTueToggle"},
      {"switch", "DaysWedToggle"},
      {"switch", "DaysThuToggle"},
      {"switch", "DaysFriToggle"},
      {"switch", "DaysSatToggle"},
      {"switch", "DaysSunToggle"},
      {"sensor", "LedBrightness"},
      {"number", "LedBrightness"},
      {"switch", "SetRGB"},
      {"switch", "SetLamp"},
      {"sensor", "status"},
      {"sensor", "alive"},
      {"text", "Comment"},
      {"text", "ThemeColor"},
      {"button", "restart"}
    };

    bool cleanupOk = true;
    for(const auto &legacy : legacyEntities){
      const String uniqueId = deviceId + "_" + legacy.id;
      const String topic = String(mqttDiscoveryPrefix) + "/" + legacy.component + "/" + uniqueId + "/config";
      if(!mqttClient.publish(topic.c_str(), "", true)){
        cleanupOk = false;
      }
    }

    if(!cleanupOk) return; // повторим очистку в следующем цикле
    mqttDiscoveryLegacyCleanupDone = true;
  }


  static const MqttDiscoveryEntity baseEntities[] = {
    {"sensor", "DS1", "Pool Water Temperature", "home/esp32/DS1", nullptr, "temperature", "°C", "measurement", nullptr, nullptr, nullptr},
    {"sensor", "RoomTemp", "Room Temperature", "home/esp32/RoomTemp", nullptr, "temperature", "°C", "measurement", nullptr, nullptr, nullptr},
    {"sensor", "PH", "Pool pH", "home/esp32/PH", nullptr, nullptr, "pH", "measurement", nullptr, nullptr, nullptr},
    {"sensor", "corrected_ORP_Eh_mV", "ORP", "home/esp32/corrected_ORP_Eh_mV", nullptr, nullptr, "mV", "measurement", nullptr, nullptr, nullptr},
    {"sensor", "ppmCl", "Free Chlorine", "home/esp32/ppmCl", nullptr, nullptr, "mg/L", "measurement", nullptr, nullptr, nullptr},
     {"sensor", "OverlayPoolTemp", "Overlay Pool Temp", "home/esp32/OverlayPoolTemp", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayHeaterTemp", "Overlay Heater Temp", "home/esp32/OverlayHeaterTemp", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayLevelUpper", "Overlay Level Upper", "home/esp32/OverlayLevelUpper", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayLevelLower", "Overlay Level Lower", "home/esp32/OverlayLevelLower", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayPh", "Overlay pH", "home/esp32/OverlayPh", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayChlorine", "Overlay Chlorine", "home/esp32/OverlayChlorine", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "OverlayFilterState", "Filter State", "home/esp32/OverlayFilterState", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "InfoString2", "Lamp Info", "home/esp32/InfoString2", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "InfoStringDIN", "DIN State", "home/esp32/InfoStringDIN", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"sensor", "Lumen_Ul", "Outdoor Luminance", "home/esp32/Lumen_Ul", nullptr, nullptr, "%", "measurement", nullptr, nullptr, nullptr},
    {"sensor", "analogValuePH", "PH ADC Value", "home/esp32/analogValuePH", nullptr, nullptr, nullptr, "measurement", nullptr, nullptr, nullptr},
    {"binary_sensor", "Power_H2O2", "NaOCl Pump State", "home/esp32/Power_H2O2", nullptr, "power", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "Power_ACO", "ACO Pump State", "home/esp32/Power_ACO", nullptr, "power", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "Power_Heat", "Heating State", "home/esp32/Power_Heat", nullptr, "power", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "Power_Topping_State", "Water Top Up State", "home/esp32/Power_Topping_State", nullptr, "power", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "WaterLevelSensorUpper", "Water Level Upper", "home/esp32/WaterLevelSensorUpper", nullptr, "moisture", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "WaterLevelSensorLower", "Water Level Lower", "home/esp32/WaterLevelSensorLower", nullptr, "moisture", nullptr, nullptr, nullptr, "1", "0"},
      {"binary_sensor", "WaterLevelSensorDrain", "Drain Pit Level (Input 3)", "home/esp32/WaterLevelSensorDrain", nullptr, "moisture", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "Power_Drain_State", "Water Drain Mode State", "home/esp32/Power_Drain_State", nullptr, "power", nullptr, nullptr, nullptr, "1", "0"},
    {"binary_sensor", "Power_Warm_floor_heating", "Floor Heating State", "home/esp32/Power_Warm_floor_heating", nullptr, "heat", nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Power_Filtr", "01 🧽 Фильтрация (вручную)", "home/esp32/Power_Filtr", "home/esp32/Power_Filtr/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Filtr_Time1", "02 ⏱️ Таймер включения №1", "home/esp32/Filtr_Time1", "home/esp32/Filtr_Time1/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "FiltrTimer1_ON", "03 🟢 Время вкл. по таймеру №1", "home/esp32/FiltrTimer1_ON", "home/esp32/FiltrTimer1_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "FiltrTimer1_OFF", "04 🔴 Время откл. по таймеру №1", "home/esp32/FiltrTimer1_OFF", "home/esp32/FiltrTimer1_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"switch", "Filtr_Time2", "05 ⏱️ Таймер включения №2", "home/esp32/Filtr_Time2", "home/esp32/Filtr_Time2/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "FiltrTimer2_ON", "06 🟢 Время вкл. по таймеру №2", "home/esp32/FiltrTimer2_ON", "home/esp32/FiltrTimer2_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "FiltrTimer2_OFF", "07 🔴 Время откл. по таймеру №2", "home/esp32/FiltrTimer2_OFF", "home/esp32/FiltrTimer2_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"switch", "Filtr_Time3", "08 ⏱️ Таймер включения №3", "home/esp32/Filtr_Time3", "home/esp32/Filtr_Time3/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "FiltrTimer3_ON", "09 🟢 Время вкл. по таймеру №3", "home/esp32/FiltrTimer3_ON", "home/esp32/FiltrTimer3_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "FiltrTimer3_OFF", "10 🔴 Время откл. по таймеру №3", "home/esp32/FiltrTimer3_OFF", "home/esp32/FiltrTimer3_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"switch", "Power_Clean", "🧼 Промывка (ручной)", "home/esp32/Power_Clean", "home/esp32/Power_Clean/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Clean_Time1", "🗓️ Промывка по времени", "home/esp32/Clean_Time1", "home/esp32/Clean_Time1/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysMonToggle", "01 ПН", "home/esp32/DaysMonToggle", "home/esp32/DaysMonToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysTueToggle", "02 ВТ", "home/esp32/DaysTueToggle", "home/esp32/DaysTueToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysWedToggle", "03 СР", "home/esp32/DaysWedToggle", "home/esp32/DaysWedToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysThuToggle", "04 ЧТ", "home/esp32/DaysThuToggle", "home/esp32/DaysThuToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysFriToggle", "05 ПТ", "home/esp32/DaysFriToggle", "home/esp32/DaysFriToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysSatToggle", "06 СБ", "home/esp32/DaysSatToggle", "home/esp32/DaysSatToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "DaysSunToggle", "07 ВС", "home/esp32/DaysSunToggle", "home/esp32/DaysSunToggle/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "Timer1", "⏰ Старт промывки", "home/esp32/Timer1", "home/esp32/Timer1/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "CleanTimer1_ON", "🟢 Промывка ВКЛ", "home/esp32/CleanTimer1_ON", "home/esp32/CleanTimer1_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "CleanTimer1_OFF", "🔴 Промывка ВЫКЛ", "home/esp32/CleanTimer1_OFF", "home/esp32/CleanTimer1_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {"text", "LampTimer_ON", "02 🟢 Время вкл. лампы по таймеру", "home/esp32/LampTimer_ON", "home/esp32/LampTimer_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "LampTimer_OFF", "03 🔴 Время откл. лампы по таймеру", "home/esp32/LampTimer_OFF", "home/esp32/LampTimer_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"switch", "WS2815_Time1", "01 ⏱️ Активация таймера RGB", "home/esp32/WS2815_Time1", "home/esp32/WS2815_Time1/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "RgbTimer_ON", "02 🟢 Время вкл. RGB по таймеру", "home/esp32/RgbTimer_ON", "home/esp32/RgbTimer_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "RgbTimer_OFF", "03 🔴 Время откл. RGB по таймеру", "home/esp32/RgbTimer_OFF", "home/esp32/RgbTimer_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"switch", "Pow_WS2815", "🌈 RGB лента", "home/esp32/Pow_WS2815", "home/esp32/Pow_WS2815/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Activation_Heat", "🔥 Контроль нагрева", "home/esp32/Activation_Heat", "home/esp32/Activation_Heat/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Activation_Water_Level", "✅ Контроль уровня воды", "home/esp32/Activation_Water_Level", "home/esp32/Activation_Water_Level/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Power_Topping", "🚰 Включить/Отключить соленоид долива воды", "home/esp32/Power_Topping", "home/esp32/Power_Topping/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
       {"switch", "Power_Drain", "🧯 СЛИВ ВОДЫ ИЗ БАССЕЙНИА", "home/esp32/Power_Drain", "home/esp32/Power_Drain/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Pow_Ul_light", "🚏 Свет улицы (ручной)", "home/esp32/Pow_Ul_light", "home/esp32/Pow_Ul_light/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "Ul_light_Time", "01 ⏱️ Активация таймера улицы", "home/esp32/Ul_light_Time", "home/esp32/Ul_light_Time/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"text", "UlLightTimer_ON", "02 🟢 Время вкл. улицы по таймеру", "home/esp32/UlLightTimer_ON", "home/esp32/UlLightTimer_ON/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"text", "UlLightTimer_OFF", "03 🔴 Время откл. улицы по таймеру", "home/esp32/UlLightTimer_OFF", "home/esp32/UlLightTimer_OFF/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {"switch", "PH_Control_ACO", "🧪 Контроль pH (ACO)", "home/esp32/PH_Control_ACO", "home/esp32/PH_Control_ACO/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "NaOCl_H2O2_Control", "🧪 Контроль хлора (NaOCl)", "home/esp32/NaOCl_H2O2_Control", "home/esp32/NaOCl_H2O2_Control/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
    {"switch", "RoomTemper", "Контроль температуры в помещении", "home/esp32/RoomTemper", "home/esp32/RoomTemper/set", nullptr, nullptr, nullptr, nullptr, "1", "0"},
     {"number", "Sider_heat", "🎯 Уставка нагрева", "home/esp32/Sider_heat", "home/esp32/Sider_heat/set", nullptr, "°C", nullptr, nullptr, nullptr, nullptr, nullptr, "5", "30", "1"},
    {"number", "PH_setting", "pH Upper Limit", "home/esp32/PH_setting", "home/esp32/PH_setting/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
      {"number", "LedBrightness", "🔆 Яркость", "home/esp32/LedBrightness", "home/esp32/LedBrightness/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "10", "255", "1"},
    {"number", "LedAutoplayDuration", "⏳ Смена режима (сек)", "home/esp32/LedAutoplayDuration", "home/esp32/LedAutoplayDuration/set", nullptr, "s", nullptr, nullptr, nullptr, nullptr, nullptr, "5", "180", "5"},
    {"text", "LEDColor", "LED Color", "home/esp32/LEDColor", "home/esp32/LEDColor/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
      {"text", "RoomTempRange", "🎚️ Включение/выключение обогрева, °C", "home/esp32/RoomTempRange", "home/esp32/RoomTempRange/set", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
  };

  static const char* const selectOptions[] = {"off", "on", "auto", "timer"}; // варианты для select
  static const char* const ledColorModeOptions[] = {"auto", "manual"};
  static const char* const ledAutoplayOptions[] = {"Автоматически", "Вручную"};
  static const char* const ledPatternOptions[] = {
    "rainbow", "pulse", "chase", "comet", "color_wipe", "theater_chase", "scanner", "sparkle",
    "twinkle", "confetti", "waves", "breathe", "firefly", "ripple", "dots", "gradient",
    "meteor", "juggle", "aurora", "candy", "twirl", "sparkle_trails", "neon_flow", "calm_sea"
  };
  static const char* const ledColorOrderOptions[] = {"GRB", "RGB", "GBR", "RBG", "BRG", "BGR"};
  static const char* const dosingOptions[] = {"1", "2", "3", "4", "5", "6", "8", "9", "10", "11", "12", "13", "7"};
  const size_t baseCount = sizeof(baseEntities) / sizeof(baseEntities[0]); // количество base сущностей
  const size_t totalCount = baseCount + 8; // количество select сущностей

  if(mqttDiscoveryStage == DISCOVERY_NONE){
    mqttDiscoveryStage = DISCOVERY_MAIN_ENTITIES; // старт этапа
  }

if(mqttDiscoveryStage == DISCOVERY_MAIN_ENTITIES){
    uint8_t publishedCount = 0; // опубликовано в этом loop
    while(publishedCount < mqttDiscoveryBatchSize && mqttDiscoveryIndex < totalCount){
      bool published = false;
      MqttDiscoveryPublishResult result = {false, 0, ""};
      if(mqttDiscoveryIndex < baseCount){
        result = publishMqttDiscoveryEntity(baseEntities[mqttDiscoveryIndex], deviceId, deviceName, true);
      } else if(mqttDiscoveryIndex == baseCount){
          result = publishMqttDiscoverySelect("SetLamp", "💡 Режим света", "home/esp32/SetLamp", "home/esp32/SetLamp/set", selectOptions, 4, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 1){
          result = publishMqttDiscoverySelect("SetRGB", "🎛️ Режим управления RGB подсветкой", "home/esp32/SetRGB", "home/esp32/SetRGB/set", selectOptions, 4, deviceId, deviceName, true, true);
        } else if(mqttDiscoveryIndex == baseCount + 2){
         result = publishMqttDiscoverySelect("LedColorMode", "🎨 Режим цвета", "home/esp32/LedColorMode", "home/esp32/LedColorMode/set", ledColorModeOptions, 2, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 3){
          result = publishMqttDiscoverySelect("LedPattern", "✨ Режим подсветки", "home/esp32/LedPattern", "home/esp32/LedPattern/set", ledPatternOptions, 24, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 4){
         result = publishMqttDiscoverySelect("LedAutoplay", "🔁 Автосмена", "home/esp32/LedAutoplay", "home/esp32/LedAutoplay/set", ledAutoplayOptions, 2, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 5){
          result = publishMqttDiscoverySelect("LedColorOrder", "🎚️ Порядок цветов ленты", "home/esp32/LedColorOrder", "home/esp32/LedColorOrder/set", ledColorOrderOptions, 6, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 6){
          result = publishMqttDiscoverySelect("ACO_Work", "⏳ Период дозирования ACO", "home/esp32/ACO_Work", "home/esp32/ACO_Work/set", dosingOptions, 13, deviceId, deviceName, true, true);
      } else if(mqttDiscoveryIndex == baseCount + 7){
         result = publishMqttDiscoverySelect("H2O2_Work", "⏳ Период дозирования NaOCl", "home/esp32/H2O2_Work", "home/esp32/H2O2_Work/set", dosingOptions, 13, deviceId, deviceName, true, true);
      }

 if(!result.published){
        if(mqttDiscoveryRetryIndex != mqttDiscoveryIndex){
          mqttDiscoveryRetryIndex = mqttDiscoveryIndex;
          mqttDiscoveryRetryCount = 0;
        }
        mqttDiscoveryRetryCount++;
        Serial.printf("[MQTT] Discovery publish failed idx=%u retries=%u topic=%s payload=%u buffer=%u\n",
                      static_cast<unsigned int>(mqttDiscoveryIndex),
                      mqttDiscoveryRetryCount,
                      result.topic.c_str(),
                      static_cast<unsigned int>(result.payloadLength),
                      static_cast<unsigned int>(mqttClient.getBufferSize()));
        if(!mqttDiscoveryPayloadFits(result.topic, result.payloadLength)){
          Serial.printf("[MQTT] Discovery payload oversized idx=%u topic=%s payload=%u buffer=%u\n",
                        static_cast<unsigned int>(mqttDiscoveryIndex),
                        result.topic.c_str(),
                        static_cast<unsigned int>(result.payloadLength),
                        static_cast<unsigned int>(mqttClient.getBufferSize()));
        }

        if(mqttDiscoveryRetryCount <= mqttDiscoveryMaxRetries){
          if(mqttDiscoveryIndex >= baseCount){
            const size_t selectIndex = mqttDiscoveryIndex - baseCount;
            if(selectIndex <= 7){
              const char* id = nullptr;
              const char* name = nullptr;
              const char* stateTopic = nullptr;
              const char* commandTopic = nullptr;
              const char* const* options = nullptr;
              size_t optionsCount = 0;
              if(selectIndex == 0){
                id = "SetLamp"; name = "💡 Режим света"; stateTopic = "home/esp32/SetLamp"; commandTopic = "home/esp32/SetLamp/set"; options = selectOptions; optionsCount = 4;
              } else if(selectIndex == 1){
                id = "SetRGB"; name = "🎛️ Режим RGB"; stateTopic = "home/esp32/SetRGB"; commandTopic = "home/esp32/SetRGB/set"; options = selectOptions; optionsCount = 4;
              } else if(selectIndex == 2){
                id = "LedColorMode"; name = "🎨 Режим цвета RGB"; stateTopic = "home/esp32/LedColorMode"; commandTopic = "home/esp32/LedColorMode/set"; options = ledColorModeOptions; optionsCount = 2;
              } else if(selectIndex == 3){
                id = "LedPattern"; name = "✨ Эффект RGB"; stateTopic = "home/esp32/LedPattern"; commandTopic = "home/esp32/LedPattern/set"; options = ledPatternOptions; optionsCount = 24;
              } else if(selectIndex == 4){
                id = "LedAutoplay"; name = "🔁 Автосмена RGB"; stateTopic = "home/esp32/LedAutoplay"; commandTopic = "home/esp32/LedAutoplay/set"; options = ledAutoplayOptions; optionsCount = 2;
              } else if(selectIndex == 5){
                 id = "LedColorOrder"; name = "🎚️ Порядок цветов"; stateTopic = "home/esp32/LedColorOrder"; commandTopic = "home/esp32/LedColorOrder/set"; options = ledColorOrderOptions; optionsCount = 6;
              } else if(selectIndex == 6){
                id = "ACO_Work"; name = "🧴 Период дозирования ACO"; stateTopic = "home/esp32/ACO_Work"; commandTopic = "home/esp32/ACO_Work/set"; options = dosingOptions; optionsCount = 13;
              } else if(selectIndex == 7){
                 id = "H2O2_Work"; name = "🧪 Период дозирования NaOCl"; stateTopic = "home/esp32/H2O2_Work"; commandTopic = "home/esp32/H2O2_Work/set"; options = dosingOptions; optionsCount = 13;
              }
              if(id){
                MqttDiscoveryPublishResult fallbackResult = publishMqttDiscoverySelect(id, name, stateTopic, commandTopic, options, optionsCount, deviceId, deviceName, true, false);
                if(fallbackResult.published){
                  Serial.printf("[MQTT] Discovery select fallback (no options) idx=%u topic=%s payload=%u\n",
                                static_cast<unsigned int>(mqttDiscoveryIndex),
                                fallbackResult.topic.c_str(),
                                static_cast<unsigned int>(fallbackResult.payloadLength));
                  mqttDiscoveryLastMaxPayload = max(mqttDiscoveryLastMaxPayload, fallbackResult.payloadLength);
                  mqttDiscoveryRetryCount = 0;
                  mqttDiscoveryIndex++;
                  publishedCount++;
                  continue;
                }
              }
            }
          }
          break; // повторим в следующем loop
        }
        Serial.printf("[MQTT] Discovery skip idx=%u topic=%s payload=%u\n",
                      static_cast<unsigned int>(mqttDiscoveryIndex),
                      result.topic.c_str(),
                      static_cast<unsigned int>(result.payloadLength));
        mqttDiscoveryRetryCount = 0;
        mqttDiscoveryIndex++;
        publishedCount++;
        continue;
      }

      mqttDiscoveryLastMaxPayload = max(mqttDiscoveryLastMaxPayload, result.payloadLength);
      mqttDiscoveryIndex++;
      publishedCount++;
    }

    if(mqttDiscoveryIndex >= totalCount){
      mqttDiscoveryStage = DISCOVERY_DONE; // завершено
      mqttDiscoveryPending = false; // сброс ожидания
            Serial.printf("[MQTT] Discovery done. Max payload=%u buffer=%u\n",
                    static_cast<unsigned int>(mqttDiscoveryLastMaxPayload),
                    static_cast<unsigned int>(mqttClient.getBufferSize()));
    }
  }
}
#endif

inline void publishMqttStateString(const char* topic, const String &value){ // публикация строкового состояния
  mqttClient.publish(topic, value.c_str()); // публикация значения (retain не используется)
}

inline void publishMqttStateBool(const char* topic, bool value){ // публикация bool состояния
  mqttClient.publish(topic, value ? "1" : "0"); // публикация 1/0
}

inline void publishMqttStateFloat(const char* topic, float value){ // публикация float состояния
  if(isnan(value)){
    mqttClient.publish(topic, "0"); // защита от NaN
    return;
  }
  String payload = String(value); // формирование строки
  mqttClient.publish(topic, payload.c_str()); // публикация значения
}

inline void publishMqttStateInt(const char* topic, int value){ // публикация int состояния
  String payload = String(value); // формирование строки
  mqttClient.publish(topic, payload.c_str()); // публикация значения
}


inline void persistMqttSettings(){ // сохранение настроек MQTT
  if(!spiffsMounted) return; // выход если SPIFFS не смонтирован
  JsonDocument doc; // JSON-документ
  doc["host"] = mqttHost; // адрес брокера
  doc["port"] = mqttPort; // порт брокера
  doc["user"] = mqttUsername; // пользователь
  doc["pass"] = mqttPassword; // пароль
  doc["interval"] = mqttPublishInterval; // интервал
  doc["enabled"] = mqttEnabled; // флаг включения

  File file = SPIFFS.open(mqttConfigPath, FILE_WRITE); // открытие файла
  if(!file) return; // выход если файл не открыт
  serializeJson(doc, file); // запись JSON в файл
  file.close(); // закрытие файла
}

inline void loadMqttSettings(){ // загрузка настроек MQTT
  if(spiffsMounted && SPIFFS.exists(mqttConfigPath)){ // если файл существует
    File file = SPIFFS.open(mqttConfigPath, FILE_READ); // открытие файла
    if(file){ // если файл открыт
      JsonDocument doc; // JSON-документ
      DeserializationError err = deserializeJson(doc, file); // парсинг JSON
      if(!err){ // если без ошибок
        mqttHost = doc["host"] | mqttHost; // адрес брокера
        mqttPort = static_cast<uint16_t>(doc["port"] | mqttPort); // порт
        mqttUsername = doc["user"] | mqttUsername; // пользователь
        mqttPassword = doc["pass"] | mqttPassword; // пароль
        mqttPublishInterval = doc["interval"] | mqttPublishInterval; // интервал
        mqttEnabled = doc["enabled"] | mqttEnabled; // флаг
      }
      file.close(); // закрытие файла
    }
  } else { // если файл отсутствует
    // fallback to legacy preferences if present
    mqttHost = loadValue<String>("mqttHost", mqttHost); // старый host
    mqttPort = static_cast<uint16_t>(loadValue<int>("mqttPort", mqttPort)); // старый порт
    mqttUsername = loadValue<String>("mqttUser", mqttUsername); // старый пользователь
    mqttPassword = loadValue<String>("mqttPass", mqttPassword); // старый пароль
    mqttEnabled = loadValue<int>("mqttEnabled", mqttEnabled ? 1 : 0) == 1; // старый флаг
    persistMqttSettings(); // сохранение в новом формате
  }
}

inline void saveMqttSettings(){ // сохранение настроек MQTT
  persistMqttSettings(); // запись в SPIFFS
}

inline void configureMqttServer(){ // настройка сервера MQTT
 if(mqttResolvedHostName != mqttHost){
    mqttResolvedHostName = mqttHost; // обновление хоста
    mqttHasResolvedIp = false; // сброс IP
    mqttLastResolveAttempt = 0; // сброс таймера резолва
  }
  if(!mqttHasResolvedIp){
    IPAddress ip;
    if(ip.fromString(mqttHost)){
      mqttResolvedIp = ip; // фиксируем IP
      mqttHasResolvedIp = true;
    }
  }
  if(mqttHasResolvedIp){
    mqttClient.setServer(mqttResolvedIp, mqttPort); // установка IP и port
  } else {
    mqttClient.setServer(mqttHost.c_str(), mqttPort); // установка host и port
  }
  mqttClient.setCallback(handleMqttCommandMessage); // обработчик входящих команд
  if(!mqttClient.setBufferSize(4096)){ // увеличиваем буфер для крупных MQTT Discovery payload
    mqttClient.setBufferSize(2048); // fallback, не ниже 2048
  }
  mqttClient.setSocketTimeout(2); // быстрый таймаут сетевых операций
  mqttClient.setKeepAlive(30); // keep-alive для снижения задержек
}

inline bool resolveMqttHost(){ // резолв MQTT хоста без блокировки
  if(mqttHost.length() == 0) return false; // пустой host
  if(mqttHasResolvedIp && mqttResolvedHostName == mqttHost) return true; // уже есть IP
  IPAddress ip;
  if(ip.fromString(mqttHost)){
    mqttResolvedIp = ip;
    mqttHasResolvedIp = true;
    mqttResolvedHostName = mqttHost;
    return true;
  }
  const unsigned long now = millis();
  if(now - mqttLastResolveAttempt < mqttResolveInterval){
    return mqttHasResolvedIp; // ждём следующего окна резолва
  }
  mqttLastResolveAttempt = now;
  if(WiFi.status() != WL_CONNECTED) return mqttHasResolvedIp; // нет Wi-Fi
  if(WiFi.hostByName(mqttHost.c_str(), ip)){
    mqttResolvedIp = ip;
    mqttHasResolvedIp = true;
    mqttResolvedHostName = mqttHost;
    return true;
  }
  return mqttHasResolvedIp; // используем предыдущий IP если был
}

inline void connectMqtt(){ // подключение к MQTT
  if(!mqttEnabled) return; // выход если MQTT выключен
  if(mqttHost.length() == 0) return; // выход если host пустой
  if(WiFi.status() != WL_CONNECTED) return; // выход если нет Wi-Fi
if(!resolveMqttHost()) return; // хост не резолвится
  const unsigned long now = millis(); // текущее время
  if(now - mqttLastConnectAttempt < mqttConnectInterval) return; // защита от частых попыток
  mqttLastConnectAttempt = now; // фиксация попытки подключения

  if(!mqttClient.connected()){ // если не подключены
    String clientId = "espdash-" + WiFi.macAddress(); // уникальный clientId
bool connected = mqttClient.connect( // подключение с логином и LWT
      clientId.c_str(),
      mqttUsername.c_str(),
      mqttPassword.c_str(),
      mqttAvailabilityTopic,
      0,
      true,
      "offline"
    );

    if(connected){ // если подключение успешно
      mqttIsConnected = true; // обновление флага
       publishMqttAvailability("online", true); // публикация доступности
 #if 1 // MQTT Discovery отключен
      mqttDiscoveryStage = DISCOVERY_NONE; // сброс этапа discovery
      mqttDiscoveryIndex = 0; // сброс индекса
      mqttDiscoveryLastAttempt = 0; // сброс таймера
      mqttDiscoveryPending = true; // публикация MQTT Discovery после первого loop
      mqttDiscoveryFullDevicePublished = false;
      mqttDiscoveryLastMaxPayload = 0;
      mqttDiscoveryRetryIndex = 0;
      mqttDiscoveryRetryCount = 0;
      mqttDiscoveryLegacyCleanupDone = false;
      publishHomeAssistantDiscovery(); // попытка публикации сразу после подключения
      #endif

      mqttClient.subscribe("home/esp32/tempSet", 0); // подписка на топик
      mqttClient.subscribe("home/esp32/Power_Filtr/set", 0); // команда фильтра
      mqttClient.subscribe("home/esp32/Filtr_Time1/set", 0); // таймер фильтрации №1
      mqttClient.subscribe("home/esp32/Filtr_Time2/set", 0); // таймер фильтрации №2
      mqttClient.subscribe("home/esp32/Filtr_Time3/set", 0); // таймер фильтрации №3
      mqttClient.subscribe("home/esp32/Power_Clean/set", 0); // промывка фильтра
            mqttClient.subscribe("home/esp32/Power_Drain/set", 0); // слив воды из бассейна
      mqttClient.subscribe("home/esp32/Clean_Time1/set", 0); // таймер промывки
      mqttClient.subscribe("home/esp32/DaysSelect/set", 0); // дни промывки
      mqttClient.subscribe("home/esp32/DaysMonToggle/set", 0); // понедельник промывки
      mqttClient.subscribe("home/esp32/DaysTueToggle/set", 0); // вторник промывки
      mqttClient.subscribe("home/esp32/DaysWedToggle/set", 0); // среда промывки
      mqttClient.subscribe("home/esp32/DaysThuToggle/set", 0); // четверг промывки
      mqttClient.subscribe("home/esp32/DaysFriToggle/set", 0); // пятница промывки
      mqttClient.subscribe("home/esp32/DaysSatToggle/set", 0); // суббота промывки
      mqttClient.subscribe("home/esp32/DaysSunToggle/set", 0); // воскресенье промывки
      mqttClient.subscribe("home/esp32/FiltrTimer1_ON/set", 0); // время фильтрации №1 ON
      mqttClient.subscribe("home/esp32/FiltrTimer1_OFF/set", 0); // время фильтрации №1 OFF
      mqttClient.subscribe("home/esp32/FiltrTimer2_ON/set", 0); // время фильтрации №2 ON
      mqttClient.subscribe("home/esp32/FiltrTimer2_OFF/set", 0); // время фильтрации №2 OFF
      mqttClient.subscribe("home/esp32/FiltrTimer3_ON/set", 0); // время фильтрации №3 ON
      mqttClient.subscribe("home/esp32/FiltrTimer3_OFF/set", 0); // время фильтрации №3 OFF
      mqttClient.subscribe("home/esp32/CleanTimer1_ON/set", 0); // время промывки ON
      mqttClient.subscribe("home/esp32/CleanTimer1_OFF/set", 0); // время промывки OFF
      mqttClient.subscribe("home/esp32/Pow_Ul_light/set", 0); // команда освещения
      mqttClient.subscribe("home/esp32/Activation_Heat/set", 0); // команда нагрева
      mqttClient.subscribe("home/esp32/SetLamp/set", 0); // команда режима лампы
      mqttClient.subscribe("home/esp32/SetRGB/set", 0); // команда режима RGB
      mqttClient.subscribe("home/esp32/+/set", 0); // универсальная подписка на команды
    
    } else { // если не удалось подключиться
      mqttIsConnected = false; // сброс флага
    }
  }
}

inline void stopMqttService(){ // остановка MQTT
    if(mqttClient.connected()) publishMqttAvailability("offline", true); // публикация offline
  mqttClient.disconnect(); // отключение от брокера
  mqttIsConnected = false; // сброс флага подключения
  mqttLastPublish = 0; // сброс таймера публикаций
  mqttLastConnectAttempt = 0; // сброс таймера подключений
  mqttLastResolveAttempt = 0; // сброс таймера резолва

  #if 1 // MQTT Discovery отключен
  mqttDiscoveryPending = false; // сброс discovery
  mqttDiscoveryStage = DISCOVERY_NONE; // сброс этапа
  mqttDiscoveryIndex = 0; // сброс индекса
  mqttDiscoveryLegacyCleanupDone = false;
  #endif
}

inline void applyMqttState(){ // применение состояния MQTT
  stopMqttService(); // остановка текущего подключения
  configureMqttServer(); // настройка сервера
  if(mqttEnabled){ // если MQTT включен
    mqttLastPublish = 0; // сброс таймера
    connectMqtt(); // подключение
  }
}

inline void handleMqttLoop(){ // основной цикл MQTT
  if(!mqttClient.connected()) connectMqtt(); // переподключение
  mqttIsConnected = mqttClient.connected(); // обновление флага

  if(!mqttEnabled || mqttHost.length() == 0){ // если MQTT выключен или host пустой
    if(mqttClient.connected()) stopMqttService(); // отключение
    return; // выход
  }

  mqttClient.loop(); // обработка MQTT

  #if 1 // MQTT Discovery отключен
    if(mqttDiscoveryPending) publishHomeAssistantDiscovery(); // публикация после первого loop
#endif

  unsigned long now = millis(); // текущее время
  if(now - mqttLastPublish >= mqttPublishInterval){ // проверка интервала
    mqttLastPublish = now; // обновление времени
    if(mqttClient.connected()){ // если подключены
      publishMqttStateString("home/esp32/test", "123");
      publishMqttStateFloat("home/esp32/DS1", DS1);
      publishMqttStateFloat("home/esp32/RoomTemp", DS1); // RoomTemp использует DS1 в UI
      publishMqttStateFloat("home/esp32/PH", PH);
      publishMqttStateInt("home/esp32/corrected_ORP_Eh_mV", corrected_ORP_Eh_mV);
      publishMqttStateFloat("home/esp32/ppmCl", ppmCl);
      publishMqttStateString("home/esp32/OverlayPoolTemp", OverlayPoolTemp);
      publishMqttStateString("home/esp32/OverlayHeaterTemp", OverlayHeaterTemp);
      publishMqttStateString("home/esp32/OverlayLevelUpper", OverlayLevelUpper);
      publishMqttStateString("home/esp32/OverlayLevelLower", OverlayLevelLower);
      publishMqttStateString("home/esp32/OverlayPh", OverlayPh);
      publishMqttStateString("home/esp32/OverlayChlorine", OverlayChlorine);
      publishMqttStateString("home/esp32/OverlayFilterState", OverlayFilterState);
      publishMqttStateString("home/esp32/InfoString2", InfoString2);
      publishMqttStateString("home/esp32/InfoStringDIN", InfoStringDIN);
      publishMqttStateInt("home/esp32/Lumen_Ul", Lumen_Ul);
      publishMqttStateInt("home/esp32/analogValuePH", analogValuePH_Comp);

      publishMqttStateBool("home/esp32/Power_H2O2", Power_H2O2);
      publishMqttStateBool("home/esp32/Power_ACO", Power_ACO);
      publishMqttStateBool("home/esp32/Power_Heat", Power_Heat);
      publishMqttStateBool("home/esp32/Power_Topping_State", Power_Topping_State);
      publishMqttStateBool("home/esp32/WaterLevelSensorUpper", WaterLevelSensorUpper);
      publishMqttStateBool("home/esp32/WaterLevelSensorLower", WaterLevelSensorLower);
            publishMqttStateBool("home/esp32/WaterLevelSensorDrain", WaterLevelSensorDrain);
      publishMqttStateBool("home/esp32/Power_Drain_State", Power_Drain_State);
      publishMqttStateBool("home/esp32/Power_Warm_floor_heating", Power_Warm_floor_heating);

      publishMqttStateBool("home/esp32/Power_Filtr", Power_Filtr);
      publishMqttStateBool("home/esp32/Filtr_Time1", Filtr_Time1);
      publishMqttStateBool("home/esp32/Filtr_Time2", Filtr_Time2);
      publishMqttStateBool("home/esp32/Filtr_Time3", Filtr_Time3);
      publishMqttStateBool("home/esp32/Power_Clean", Power_Clean);
      publishMqttStateBool("home/esp32/Clean_Time1", Clean_Time1);
       publishMqttStateBool("home/esp32/Pow_WS2815", Pow_WS2815);
      publishMqttStateBool("home/esp32/WS2815_Time1", WS2815_Time1);
      publishMqttStateBool("home/esp32/Activation_Water_Level", Activation_Water_Level);
      publishMqttStateBool("home/esp32/Power_Topping", Power_Topping);
           publishMqttStateBool("home/esp32/Power_Drain", Power_Drain);
      publishMqttStateBool("home/esp32/PH_Control_ACO", PH_Control_ACO);
      publishMqttStateBool("home/esp32/NaOCl_H2O2_Control", NaOCl_H2O2_Control);
      publishMqttStateBool("home/esp32/RoomTemper", RoomTemper);
      publishMqttStateBool("home/esp32/Ul_light_Time", Ul_light_Time);
      publishMqttStateString("home/esp32/RoomTempRange", String(RoomTempOn, 1) + "-" + String(RoomTempOff, 1));
      publishMqttStateString("home/esp32/Timer1", Timer1);
      publishMqttStateString("home/esp32/LEDColor", LEDColor);
      publishMqttStateString("home/esp32/LedColorMode", LedColorMode);
      publishMqttStateInt("home/esp32/LedBrightness", LedBrightness);
      publishMqttStateString("home/esp32/LedPattern", LedPattern);
      publishMqttStateInt("home/esp32/LedAutoplayDuration", LedAutoplayDuration);
      publishMqttStateString("home/esp32/LedAutoplay", mqttLedAutoplayState());
      publishMqttStateString("home/esp32/LedColorOrder", LedColorOrder);
      publishMqttStateInt("home/esp32/Sider_heat", Sider_heat);
      publishMqttStateFloat("home/esp32/PH_setting", PH_setting);
      publishMqttStateInt("home/esp32/ACO_Work", ACO_Work);
      publishMqttStateInt("home/esp32/H2O2_Work", H2O2_Work);
      publishMqttStateString("home/esp32/DaysSelect", DaysSelect);
      publishMqttStateBool("home/esp32/DaysMonToggle", mqttDaysSelectContains("Mon"));
      publishMqttStateBool("home/esp32/DaysTueToggle", mqttDaysSelectContains("Tue"));
      publishMqttStateBool("home/esp32/DaysWedToggle", mqttDaysSelectContains("Wed"));
      publishMqttStateBool("home/esp32/DaysThuToggle", mqttDaysSelectContains("Thu"));
      publishMqttStateBool("home/esp32/DaysFriToggle", mqttDaysSelectContains("Fri"));
      publishMqttStateBool("home/esp32/DaysSatToggle", mqttDaysSelectContains("Sat"));
      publishMqttStateBool("home/esp32/DaysSunToggle", mqttDaysSelectContains("Sun"));
      publishMqttStateString("home/esp32/FiltrTimer1_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer1")));
      publishMqttStateString("home/esp32/FiltrTimer1_OFF", formatMinutesToTime(mqttTimerOffMinutes("FiltrTimer1")));
      publishMqttStateString("home/esp32/FiltrTimer2_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer2")));
      publishMqttStateString("home/esp32/FiltrTimer2_OFF", formatMinutesToTime(mqttTimerOffMinutes("FiltrTimer2")));
      publishMqttStateString("home/esp32/FiltrTimer3_ON", formatMinutesToTime(mqttTimerOnMinutes("FiltrTimer3")));
      publishMqttStateString("home/esp32/FiltrTimer3_OFF", formatMinutesToTime(mqttTimerOffMinutes("FiltrTimer3")));
      publishMqttStateString("home/esp32/CleanTimer1_ON", formatMinutesToTime(mqttTimerOnMinutes("CleanTimer1")));
      publishMqttStateString("home/esp32/CleanTimer1_OFF", formatMinutesToTime(mqttTimerOffMinutes("CleanTimer1")));
      publishMqttStateString("home/esp32/LampTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("LampTimer")));
      publishMqttStateString("home/esp32/LampTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("LampTimer")));
      publishMqttStateString("home/esp32/RgbTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("RgbTimer")));
      publishMqttStateString("home/esp32/RgbTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("RgbTimer")));
      publishMqttStateString("home/esp32/UlLightTimer_ON", formatMinutesToTime(mqttTimerOnMinutes("UlLightTimer")));
      publishMqttStateString("home/esp32/UlLightTimer_OFF", formatMinutesToTime(mqttTimerOffMinutes("UlLightTimer")));
      publishMqttStateBool("home/esp32/Pow_Ul_light", Pow_Ul_light);
      publishMqttStateBool("home/esp32/Activation_Heat", Activation_Heat);

      publishMqttStateString("home/esp32/SetLamp", SetLamp);
      publishMqttStateString("home/esp32/SetRGB", SetRGB);
    
    }
  }
}
