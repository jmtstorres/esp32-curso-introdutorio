#include <ntp_esp.h>

WiFiUDP udp;
NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);
String hora;

void init_ntp()
{
    ntp.begin();
    ntp.forceUpdate();
}

String ntpGetTimeStr(){
    ntp.getFormattedTime();
    String str = String(ntp.getHours()) + ":" + String(ntp.getMinutes());
    return str;
}
