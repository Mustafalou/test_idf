#include <Arduino.h>
#include <ETHClass.h>
#include <PubSubClient.h>
#include <SPI.h>
#include "utilities.h"
#include "AccelStepper.h"
#include "driver/gpio.h"
#include "string.h"
/*
#define PUL_PIN 33
#define DIR_PIN  4

AccelStepper stepper;
int last_position = 0;
bool motor_stop = false;
bool eth_connected = false;

WiFiClient ethClient;
PubSubClient client(ethClient);



unsigned long lastMillis = 0;

void WiFiEvent(WiFiEvent_t event)
{
    switch (event) {
    case ARDUINO_EVENT_ETH_START:
        Serial.println("ETH Started");
        //set eth hostname here
        ETH.setHostname("esp32-ethernet");
        break;
    case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ETH Connected");
        break;
    case ARDUINO_EVENT_ETH_GOT_IP:
        Serial.print("ETH MAC: ");
        Serial.print(ETH.macAddress());
        Serial.print(", IPv4: ");
        Serial.print(ETH.localIP());
        if (ETH.fullDuplex()) {
            Serial.print(", FULL_DUPLEX");
        }
        Serial.print(", ");
        Serial.print(ETH.linkSpeed());
        Serial.println("Mbps");
        eth_connected = true;
        break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        eth_connected = false;
        break;
    case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        eth_connected = false;
        break;
    default:
        break;
    }
}

void callback(char *topic, byte *payload, uint32_t length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    char * charPointer = (char *)payload;
    int pld = atoi(charPointer);
    if (strcmp(topic, "esp32eth/DriverStop")==0){
        if(pld == 0){
            Serial.println("Step Sart : Stepper should be started");
            motor_stop=false;
            stepper.moveTo(0);
        }
        else{
            Serial.println("Step Stop : Stepper should be stopped");
            motor_stop=true;
        }
        Serial.print(motor_stop);
    }
    else if(strcmp(topic, "esp32eth/DriverMoveTo")==0){
        if (!motor_stop){
            Serial.print( pld);
            stepper.moveTo(pld);
        }
    }
    Serial.println();
}

void setup()
{
    Serial.begin(115200);
    WiFi.onEvent(WiFiEvent);
    if (!ETH.begin(ETH_ADDR, ETH_RESET_PIN, ETH_MDC_PIN,
                   ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE)) {
        Serial.println("ETH start Failed!");
    }

    // Note - the default maximum packet size is 128 bytes. If the
    // combined length of clientId, username and password exceed this use the
    // following to increase the buffer size:
    // client.setBufferSize(255);
    while (!eth_connected) {
        Serial.println("Wait eth connect..."); delay(2000);
    }

    //set server and port
    client.setServer("192.168.0.5", 1883);


    //set callback
    client.setCallback(callback);


    const char *client_id = "esp32eth";
    const char *username = "empty";
    const char *password = "empty";

    while (!client.connect(client_id, username, password)) {
        delay(200);
        Serial.println("Connecting....");
    }

    client.subscribe("esp32eth/DriverMoveTo");
    client.subscribe("esp32eth/DriverStop");
    
    Serial.println("MQTT Connected!");

    stepper = AccelStepper(1,PUL_PIN,DIR_PIN);
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(400);
    Serial.println("Step Init : Stepper created");

}

void loop()
{
    client.loop();
    if (motor_stop){
        stepper.stop();
    }else{
        stepper.run();
    }
    if( millis() -  lastMillis >= 1000){
        client.publish("esp32/driverposition",String(stepper.currentPosition()).c_str());
        lastMillis = millis();
    }
}
*/