#include <WiFi.h>
#include <DHTesp.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

DHTesp dhtSensor;

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

const String url = "https://643cf2436afd66da6ae7fca7.mockapi.io/api/v1/";
String response_success = "Success";
String response_error = "Error";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dhtSensor.setup(15, DHTesp::DHT22);
  WiFi.begin(ssid,pass, 6);
  Serial.println("Menghubungkan ke WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.print("koneksi WiFi IP :");
  Serial.println(WiFi.localIP());
}

void loop() {
  control();
  monitoring();
}

void control(){
  HTTPClient http;
  http.begin(url+"control");
  int httpResCode = http.GET();
  if(httpResCode > 0){
    Serial.println(httpResCode);
    String payload = http.getString();
    Serial.println(response_success);
    // Serial.println(payload);
    JSONVar control_object = JSON.parse(payload);
    for(int i = 0; i < control_object.length(); i++){
      JSONVar control_name = control_object[i]["control_name"];
      JSONVar control_pin = control_object[i]["control_pin"];
      JSONVar control_value = control_object[i]["control_value"];
      pinMode(control_pin, OUTPUT);
      digitalWrite(control_pin, control_value);
    }
  }else {
    Serial.println(response_error);
  }
  http.end();
}

void monitoring(){
  HTTPClient http;

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp :"+ String(data.temperature));
  Serial.println("Humi :"+ String(data.humidity));

  String temp_value = String(data.temperature);
  String humi_value = String(data.humidity);

  JSONVar valueTemp;
  valueTemp["monitoring_value"] = temp_value;
  JSONVar valueHumi;
  valueHumi["monitoring_value"] = humi_value;

  String monitotingTemp = JSON.stringify(valueTemp);
  String monitotingHumi = JSON.stringify(valueHumi);

  Serial.println("Temp :"+ monitotingTemp);
  Serial.println("Humi :"+ monitotingHumi);

  http.begin(url+"monitoring/1");
  http.addHeader("Content-Type", "application/json");
  int httpRespCode1 = http.PUT(monitotingTemp);
  if(httpRespCode1 > 0) {
    Serial.println(httpRespCode1);
    Serial.println(response_success);
  } else {
    Serial.println(response_error);
  }
  http.end();

  http.begin(url+"monitoring/2");
  http.addHeader("Content-Type", "application/json");
  int httpRespCode2 = http.PUT(monitotingHumi);
  if(httpRespCode2 > 0) {
    Serial.println(httpRespCode2);
    Serial.println(response_success);
  } else {
    Serial.println(response_error);
  }
  http.end();
}