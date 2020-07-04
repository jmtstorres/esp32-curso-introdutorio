#include <Arduino.h>
#include <display_esp.h>
#include <Wire.h>
#include <TrivialKalmanFilter.h>

#define DT_COVARIANCE_RK 4.0 // Estimation of the noise covariances (process)
#define DT_COVARIANCE_QK 1.0   // Estimation of the noise covariances (observation)

const int sda_pin = GPIO_NUM_21; // definição do pino I2C SDA
const int scl_pin = GPIO_NUM_22; // definição do pino I2C SCL

const int MPU_ADDR =      0x68; // definição do endereço do sensor MPU6050 (0x68)
const int WHO_AM_I =      0x75; // registro de identificação do dispositivo
const int PWR_MGMT_1 =    0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG =   0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG =  0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT =    0x3B; // registro de leitura do eixo X do acelerômetro

const int LED_BUILTIN = GPIO_NUM_4; // registro de leitura do eixo X do acelerômetro

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; 

bool led_state = false;

TrivialKalmanFilter<float> filterX(DT_COVARIANCE_RK, DT_COVARIANCE_QK);
TrivialKalmanFilter<float> filterY(DT_COVARIANCE_RK, DT_COVARIANCE_QK);
TrivialKalmanFilter<float> filterZ(DT_COVARIANCE_RK, DT_COVARIANCE_QK);

/*
 * função que configura a I2C com os pinos desejados 
 * sda_pin -> D5
 * scl_pin -> D6
 */
void initI2C() 
{
  //Serial.println("---inside initI2C");
  Wire.begin(sda_pin, scl_pin);
}
 
/*
 * função que escreve um dado valor em um dado registro
 */
void writeRegMPU(int reg, int val)      //aceita um registro e um valor como parâmetro
{
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.write(val);                      // escreve o valor no registro
  Wire.endTransmission(true);           // termina a transmissão
}

void setSleepOff()
{
  writeRegMPU(PWR_MGMT_1, 0); // escreve 0 no registro de gerenciamento de energia(0x68), colocando o sensor em o modo ACTIVE
}

void setGyroScale()
{
  writeRegMPU(GYRO_CONFIG, 0);
}
 
void setAccelScale()
{
  writeRegMPU(ACCEL_CONFIG, 0);
}
 
uint8_t readRegMPU(uint8_t reg)        // aceita um registro como parâmetro
{
  uint8_t data;
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.endTransmission(false);          // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 1);        // configura para receber 1 byte do registro escolhido acima
  data = Wire.read();                   // lê o byte e guarda em 'data'
  return data;                          //retorna 'data'
}
 
void findMPU(int mpu_addr)
{
  Wire.beginTransmission(MPU_ADDR);
  int data = Wire.endTransmission(true);
 
  if(data == 0)
  {
    Serial.print("Dispositivo encontrado no endereço: 0x");
    Serial.println(MPU_ADDR, HEX);
  }
  else
  {
    Serial.println("Dispositivo não encontrado!");
  }
}
 
void checkMPU(int mpu_addr)
{
  findMPU(MPU_ADDR);
     
  int data = readRegMPU(WHO_AM_I); // Register 117 – Who Am I - 0x75
   
  if(data == 104) 
  {
    Serial.println("MPU6050 Dispositivo respondeu OK! (104)");
 
    data = readRegMPU(PWR_MGMT_1); // Register 107 – Power Management 1-0x6B
 
    if(data == 64) Serial.println("MPU6050 em modo SLEEP! (64)");
    else Serial.println("MPU6050 em modo ACTIVE!"); 
  }
  else Serial.println("Verifique dispositivo - MPU6050 NÃO disponível!");
}
 
void initMPU()
{
  setSleepOff();
  setGyroScale();
  setAccelScale();
}

int minVal=-32767;
int maxVal=32767;
 
void readRawMPU()
{  
  Wire.beginTransmission(MPU_ADDR);       // inicia comunicação com endereço do MPU6050
  Wire.write(ACCEL_XOUT);                       // envia o registro com o qual se deseja trabalhar, começando com registro 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);            // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 14);         // configura para receber 14 bytes começando do registro escolhido acima (0x3B)
 
  AcX = Wire.read() << 8;                 // lê primeiro o byte mais significativo
  AcX |= Wire.read();                     // depois lê o bit menos significativo
  AcY = Wire.read() << 8;
  AcY |= Wire.read();
  AcZ = Wire.read() << 8;
  AcZ |= Wire.read();
 
  Tmp = Wire.read() << 8;
  Tmp |= Wire.read();
 
  GyX = Wire.read() << 8;
  GyX |= Wire.read();
  GyY = Wire.read() << 8;
  GyY |= Wire.read();
  GyZ = Wire.read() << 8;
  GyZ |= Wire.read(); 

  float xAng = map(AcX,minVal,maxVal,-180.0,180.0);
  float yAng = map(AcY,minVal,maxVal,-180.0,180.0);
  float zAng = map(AcZ,minVal,maxVal,-180.0,180.0);

  yAng = filterY.update(yAng);
  xAng = filterX.update(xAng);
  zAng = filterZ.update(zAng);

  int range[4] = {0,0, 128, 64};

  int xp=64, yp=32;
  int ypOffset = yp*sin(xAng*DEG_TO_RAD);
  yp = yp + ypOffset;

  int t[4] = {0, 0, 0, 0};
  float rad = yAng*DEG_TO_RAD;
  t[0] = xp - (xp*cos(rad));
  t[1] = yp + (yp*sin(rad));
  t[2] = xp + (xp*cos(rad));
  t[3] = yp - (yp*sin(rad));

  drawline(t[0], t[1], t[2], t[3]);
}

void setup() {
  initialize_display();
  setFooterLeft("-");
  setFooterRight("-");
  updateDisplay();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
 
  Serial.println("nIniciando configuração WiFin");
 
  Serial.println("nIniciando configuração do MPU6050n");
  initI2C();
  initMPU();
  checkMPU(MPU_ADDR);
 
  Serial.println("Enviando localização ao servidorn");
 
  Serial.println("nConfiguração finalizada, iniciando loopn");  

  setBody("OK!");
  updateDisplay();
}
 
void loop() {
  readRawMPU();    // lê os dados do sensor
  delay(50);  
}