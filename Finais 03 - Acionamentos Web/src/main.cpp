#include <Arduino.h>
#include <ESPAsyncWebServer.h>

//Código html da página ligar
String page_on =
    "<h1>Controle do LED</h1>"
    "<h2>projeto final 03</h2>"
    "LED ligado"
    "<a href=\"/desligar\">"
    "<button>desligar</button>"
    "</a>";

//Código html da página desligar
String page_off =
    "<h1>Controle do LED</h1>"
    "<h2>projeto final 03</h2>"
    "LED desligado"
    "<a href=\"/ligar\">"
    "<button>ligar</button>"
    "</a>";

//Código html da página controle
String page_controle =
    "<h1>Controle do LED</h1>"
    "<h2>projeto final 03</h2>"
    "LED"
    "<a href=\"/controle?estado=true\">"
    "<button>ligar</button>"
    "</a>"
    "<a href=\"/controle?estado=false\">"
    "<button>desligar</button>"
    "</a>";

//Instancia do webserver assincrono
AsyncWebServer server(80);

//Funcao que cuida do retorno de página não encontrada
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

//Pino de indicação de conexão
int pin = GPIO_NUM_16;

void setup()
{
  Serial.begin(9600); //Inicializando a serial
  pinMode(pin, OUTPUT);//Inicializando saída do indicador

  int wStatus = WL_DISCONNECTED;
  int limit = 60; //tempo de espera para conexão
  //WiFi.begin("NOME-DA-REDE", "senhadarede");//propriedades da rede a conectar
  WiFi.begin("NET_2GDC570B", "4BDC570B");//propriedades da rede a conectar
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

    digitalWrite(pin, LOW); //desligamos o indicador na saída

    //Configuramos os enderecos que serao disponibilizados
    //Endereco ligar
    server.on("/ligar", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", page_on);
      digitalWrite(pin, HIGH);
    });

    //Endereco desligar
    server.on("/desligar", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", page_off);
      digitalWrite(pin, LOW);
    });

    //Configuramos os enderecos que serao disponibilizados
    //Endereco ligar
    server.on("/controle", HTTP_GET, [](AsyncWebServerRequest *request) {
      String message;
      if (request->hasParam("estado")) {
          message = request->getParam("estado")->value();
      } else {
          message = "No message sent";
      }
      if(message.equalsIgnoreCase("true")){
        digitalWrite(pin, HIGH);
      } else if(message.equalsIgnoreCase("false")){
        digitalWrite(pin, LOW);
      }
      request->send(200, "text/html", page_controle);
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