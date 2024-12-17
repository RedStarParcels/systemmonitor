#include <ArduinoJson.h>


#define CPU_PIN 3
#define RAM_PIN 5
#define SWAP_PIN 6
#define GPU_PIN 9
#define VRAM_PIN 10

int cpu_per = 0, ram_per = 0, swap_per = 0, gpu_per = 0, vram_per = 0;

void setup()
{
  pinMode(CPU_PIN, OUTPUT);
  pinMode(RAM_PIN, OUTPUT);
  pinMode(SWAP_PIN, OUTPUT);
  pinMode(GPU_PIN, OUTPUT);
  pinMode(VRAM_PIN, OUTPUT);

  Serial.begin(9600);

  delay(2000);
}

String payload;

void loop()
{
  int value;

  if (Serial.available()){
    delay(5);
    payload = Serial.readStringUntil('\n');
  } 
  StaticJsonDocument<256> rec_data;

  DeserializationError error = deserializeJson(rec_data, payload);
  if (error) {
  
  }
  else {
    
    value = rec_data["CPU"];
    cpu_per = int((value * 255) / 100);
    analogWrite(CPU_PIN, cpu_per);
    
    value = rec_data["MEM"];
    ram_per = int((value * 255) / 100);
    analogWrite(RAM_PIN, ram_per);

    value = rec_data["SWP"]; 
    swap_per = int((value * 255) / 100);
    analogWrite(SWAP_PIN, swap_per);
    
    value = rec_data["GPU"];
    gpu_per = int((value * 255) / 100);
    analogWrite(GPU_PIN, gpu_per);

    value = rec_data["VRAM"];
    vram_per = int((value * 255) / 100);
    analogWrite(VRAM_PIN, vram_per);

  }
  delay(20);
}

