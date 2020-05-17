#include <Arduino.h>
#include <Servo.h>
#include <ESPAsyncWebServer.h>

//Código html da página home
String page_home =
    "<h1>Sou a sua Home Page</h1>"
    "<h2>sou um subtitulo</h2>"
    "Pagina principal";

//Código html da página info
String page_info =
    "<h1>Pagina de informacoes</h1>"
    "<h2>sou um subtitulo</h2>"
    "Informacoes da pagina";

//Instancia do webserver assincrono
AsyncWebServer server(80);

//Funcao que cuida do retorno de página não encontrada
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

//Pino de indicação de conexão
int pin = GPIO_NUM_32;

void setup()
{
  Serial.begin(9600); //Inicializando a serial
  pinMode(pin, OUTPUT);//Inicializando saída do indicador

  int wStatus = WL_DISCONNECTED;
  int limit = 60; //tempo de espera para conexão
  WiFi.begin("NOME-DA-REDE", "senhadarede");//propriedades da rede a conectar
  while (wStatus != WL_CONNECTED &&
         wStatus != WL_CONNECT_FAILED) //Aguardando conexão ou falha
  {
    Serial.println("Tentando conexão...");
    delay(1000);
    wStatus = WiFi.status();
    if (limit-- <= 0)
    {
      wStatus = WL_CONNECT_FAILED; //Se o tempo de espera for excedido
      break;                       //Damos a conexão como falha
    }
  }

  if (wStatus == WL_CONNECTED) //Se a conexão for bem-sucedida
  {
    String ip = WiFi.localIP().toString(); //Mostramos o IP
    String ipStr = "Connected to the WiFi network: " + ip;
    Serial.println(ipStr);

    digitalWrite(pin, HIGH); //Acionamos o indicador na saída

    //Configuramos os enderecos que serao disponibilizados
    //Endereco home
    server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", page_home);
    });

    //Endereco info
    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", page_info);
    });

    server.onNotFound(notFound);//Endereco nao reconhecido
    server.begin();             //Iniciamos o servidor
  }
  else
  {
    //Caso não seja bem sucedido informamos via serial
    Serial.println("Falha ao conectar.");
  }
}

void loop()
{
  //Não temos funcao loop pois todas as conexões
  //estão sendo tratadas pelo nosso servidor assíncrono :)
}