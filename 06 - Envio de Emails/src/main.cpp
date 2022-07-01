#include <Arduino.h>
#include "ESP32_MailClient.h"

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

// To send Email using Gmail use port 465 (SSL) and SMTP Server smtp.gmail.com
// YOU MUST ENABLE less secure app option https://myaccount.google.com/lesssecureapps?pli=1
#define emailSenderAccount    "jmtstorres@hotmail.com"    
#define emailSenderPassword   "jaomartelo123"
#define emailRecipient        "jmtstorres@gmail.com"
#define smtpServer            "smtp.live.com"
#define smtpServerPort        587
#define emailSubject          "ESP32 Test"

// The Email Sending data object contains config and data to send
SMTPData smtpData;

// Callback function to get the Email sending status
void sendCallback(SendStatus info);

void initWifi(){
  
  Serial.print("Connecting");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println();
  Serial.println("Preparing to send email");
  Serial.println();
}

void setup(){
  pinMode(GPIO_NUM_32, INPUT);
  Serial.begin(9600);
  Serial.println("comecou");
  initWifi();
}

void sendEmail(){
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

  // For library version 1.2.0 and later which STARTTLS protocol was supported,the STARTTLS will be 
  // enabled automatically when port 587 was used, or enable it manually using setSTARTTLS function.
  //smtpData.setSTARTTLS(true);
// Set the sender name and Email
  smtpData.setSender("ESP32", emailSenderAccount);

  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");

  // Set the subject
  smtpData.setSubject(emailSubject);

  // Set the message with HTML format
  smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board</p></div>", true);
  // Set the email message in text format (raw)
  //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);

  // Add recipients, you can add more than one recipient
  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient("YOUR_OTHER_RECIPIENT_EMAIL_ADDRESS@EXAMPLE.com");

  smtpData.setSendCallback(sendCallback);

  //Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  //Clear all data from Email object to free memory
  smtpData.empty();
}

void loop() {
  int read = digitalRead(GPIO_NUM_32);
  if(read == HIGH){
    Serial.println("Teste");
    sendEmail();
    delay(3000);
  }
  delay(100);
}

// Callback function to get the Email sending status
void sendCallback(SendStatus msg) {
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
  }
}