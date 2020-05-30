#include <clima.h>

//https://portal.inmet.gov.br/manual
String getClima(String cidade, int hour)
{
    HTTPClient http;
    String result = "";

    http.begin("https://apiprev.inmet.gov.br/previsao/diaria/cidade/" + cidade);
    //Não funciona sem os headers
    http.addHeader("Host", "apiprev.inmet.gov.br");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Cache-Control", "max-age=0");
    http.addHeader("Upgrade-Insecure-Requests", "1");
    http.addHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36");
    http.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    http.addHeader("Sec-Fetch-Site", "none");
    http.addHeader("Sec-Fetch-Mode", "navigate");
    http.addHeader("Sec-Fetch-User", "?1");
    http.addHeader("Sec-Fetch-Dest", "document");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept-Language", "pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7");
    int httpCode = http.GET();
    if (httpCode == 200)
    { //Retorno OK html
        String payload = http.getString();
        String horario = "";
        StaticJsonDocument<256> doc;
        if(hour > 0 && hour <= 12){
            horario = "manha";
        }
        if(hour > 12 && hour <= 16){
            horario = "tarde";
        }
        if(hour > 16 && hour <= 24){
            horario = "noite";
        }
        Serial.println(cidade + " : " + String(hour, DEC) + " : " + horario);
        StaticJsonDocument<128> filter;
        filter[String(cidade)][String("27-05-2020")][String(horario)][String("temp_max")] = true;
        filter[String(cidade)][String("27-05-2020")][String(horario)][String("temp_min")] = true;
        Serial.println("FILTRO>>>>>");
        Serial.println(filter.as<String>());
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return "ERROR";
        }

        JsonObject obj = doc.as<JsonObject>();
        int t_max = obj[String(cidade)][String("27-05-2020")][String(horario)][String("temp_max")];
        int t_min = obj[String(cidade)][String("27-05-2020")][String(horario)][String("temp_min")];
        result = "M" + String(t_max) + "/m" + String(t_min) + " *C";
    }
    else
    {
        Serial.println("Error on HTTP request");
    }

    http.end();
    return result;
}
