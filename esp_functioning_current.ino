#include <MPU9250_asukiaaa.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SERVICE_UUID1        "301298a5-1654-4dff-b2dc-d68d8da3c039"
#define SERVICE_UUID2        "b9d2ea7c-ff14-4f1b-bf8c-bf1ecfcff278"
#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID1 "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define CHARACTERISTIC_UUID2 "df027df5-8081-4dd1-9fcc-52e5e499e04f"
#define CHARACTERISTIC_UUID3 "574930b3-6535-49da-af0b-65999dfa77f4"
#define CHARACTERISTIC_UUID4 "811311c3-687f-40c9-b397-63b9509c37fb"
#define CHARACTERISTIC_UUID5 "29bd7795-07db-4b67-95d1-b04fa142f4f5"
#define CHARACTERISTIC_UUID6 "9eb76ac6-1154-4696-b140-46d7669805c2"
#define CHARACTERISTIC_UUID7 "0a29cf6e-7c68-41e0-a05e-50fe09f6dd18"
int LEDOUT=2;


BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic1 = NULL;
BLECharacteristic* pCharacteristic2 = NULL;
BLECharacteristic* pCharacteristic3 = NULL;
BLECharacteristic* pCharacteristic4 = NULL;
BLECharacteristic* pCharacteristic5 = NULL;
BLECharacteristic* pCharacteristic6 = NULL;
BLECharacteristic* pCharacteristic7 = NULL;



bool deviceConnected=false;
bool oldDeviceConnected=false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string value = pCharacteristic->getValue();
    //ESP.restart();
    if(value.length() > 0){

      Serial.println("**********");
      Serial.print("New value: ");
      if(value == "true"){
      //for(int i=0; i < value.length(); i++){
        digitalWrite(LEDOUT,HIGH);
      //}
      Serial.println("Is set to high");
      }else{
        digitalWrite(LEDOUT,LOW);
        ("Is set to low");
      }
      

      Serial.println();
      Serial.println("**********");
      
    }
  }
};


class MyCallbacks1: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string value = pCharacteristic->getValue();
    //ESP.restart();
    if(value.length() > 0){

      Serial.println("**********");
      Serial.print("New value: ");
      if(value == "true"){
      //for(int i=0; i < value.length(); i++){
        //digitalWrite(LEDOUT,HIGH);
        ESP.restart();
      //}
      Serial.println("Is set to high");
      }else{
        //digitalWrite(LEDOUT,LOW);
        ESP.restart();
        ("Is set to low");
      }
      

      Serial.println();
      Serial.println("**********");
      
    }
  }
};

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setup() {
  pinMode(LEDOUT,OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");
#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  BLEDevice::init("ESP_Gyro");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLEService *pService1 = pServer->createService(SERVICE_UUID1);
  BLEService *pService2 = pServer->createService(SERVICE_UUID2);

  
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
  pCharacteristic1 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID1,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
  pCharacteristic2 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID2,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
  pCharacteristic3 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID3,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
                                       
                                         
  pCharacteristic4 = pService1->createCharacteristic(
                                         CHARACTERISTIC_UUID4,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
   pCharacteristic5 = pService1->createCharacteristic(
                                         CHARACTERISTIC_UUID5,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
                                       
   pCharacteristic6 = pService2->createCharacteristic(
                                         CHARACTERISTIC_UUID6,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );
                                       
   pCharacteristic7 = pService2->createCharacteristic(
                                         CHARACTERISTIC_UUID7,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE | 
                                         BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                                         
                                       );


  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic1->addDescriptor(new BLE2902());
  pCharacteristic2->addDescriptor(new BLE2902());
  pCharacteristic3->addDescriptor(new BLE2902());
  pCharacteristic4->addDescriptor(new BLE2902());
  pCharacteristic5->addDescriptor(new BLE2902());
  pCharacteristic6->addDescriptor(new BLE2902());
  pCharacteristic7->addDescriptor(new BLE2902());


  pCharacteristic6->setCallbacks(new MyCallbacks());
  pCharacteristic7->setCallbacks(new MyCallbacks1());

  
  
 pService->start();
 pService1->start();
 pService2->start(); 
  //BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_UUID1);
  pAdvertising->addServiceUUID(SERVICE_UUID2);

  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
}

void loop() {

   if (deviceConnected) {
        String str = "";
        String str1 = "";
        String str2 = "";
        String str3 = "";
        String str4 = "";
        String str5 = "";

        
        str  += mySensor.accelX();
        str1 += mySensor.accelY();        
        str2 += mySensor.accelZ();
        str3 += mySensor.gyroX();
        str4 += mySensor.gyroY();
        str5 += mySensor.gyroZ();
        
        pCharacteristic->setValue((char*)str.c_str());
        pCharacteristic->notify();
        pCharacteristic1->setValue((char*)str1.c_str());
        pCharacteristic1->notify();
        pCharacteristic2->setValue((char*)str2.c_str());
        pCharacteristic2->notify();
        pCharacteristic3->setValue((char*)str3.c_str());
        pCharacteristic3->notify();
        pCharacteristic4->setValue((char*)str4.c_str());
        pCharacteristic4->notify();
        pCharacteristic5->setValue((char*)str5.c_str());
        pCharacteristic5->notify();          
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
  
  delay(200);



  
  uint8_t sensorId;
  if (mySensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }

  if (mySensor.accelUpdate() == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.println("accelX: " + String(aX));
    //Serial.println("accelY: " + String(aY));
    //Serial.println("accelZ: " + String(aZ));
    Serial.println("accelSqrt: " + String(aSqrt));
  } else {
    Serial.println("Cannod read accel values");
  }

  if (mySensor.gyroUpdate() == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
    Serial.println("gyroX: " + String(gX));
    Serial.println("gyroY: " + String(gY));
    Serial.println("gyroZ: " + String(gZ));
  } else {
    Serial.println("Cannot read gyro values");
  }

  if (mySensor.magUpdate() == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
    Serial.println("magX: " + String(mX));
    Serial.println("maxY: " + String(mY));
    Serial.println("magZ: " + String(mZ));
    Serial.println("horizontal direction: " + String(mDirection));
  } else {
    Serial.println("Cannot read mag values");
  }

  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line
  delay(500);
}
