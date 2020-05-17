#include <Arduino.h>

void setup() {        
  //Inicializando GPIO4 como saída      
  Serial.begin(9600);  
}       
   
void loop() {      
  //Verificando se há dados na porta para leitura  
  if(Serial.available() > 0){  
    //iterando sobre todos os dados disponíveis na porta  
    for(int i = 0; i < Serial.available(); i++){  
      //Para cada byte lido  
      int lido = Serial.read();  
      //o mesmo byte será escrito de volta  
      Serial.println("Lido: " + String(lido));  
    }  
  }  
} 
