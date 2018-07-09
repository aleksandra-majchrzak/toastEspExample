# toastEspExample
Project for Android and ESP8266 - light module based on ESP8266 12E connecting with mobile app via WiFi.

Kod do wgrania z moduł ESP znajduje się w folderze `esp8266`. Plik `esp8266.ino` to wersja z paskiem ledowym, `esp8266_led` to wersja z diodą RGB.

# Konfiguracja środowiska
Aby móc programować w Arduino IDE musimy zainstalować odpowiedni Manager Płytek oraz zainstalować kilka niezbędnych bibliotek.

1. Po opdaleniu Arduino IDE wybieramy Plik->Preferencje i w polu <i>Dodatkowe adresy URL...</i> wpisujemy `http://arduino.esp8266.com/stable/package_esp8266com_index.json` (link z <a href="https://github.com/esp8266/Arduino">oficjalnej strony biblioteki ESP</a>).
2. W menu Narzędzia->Płytki->Menadżer Płytek znajdujemy i instalujemy `esp8266`.
3. W menu Narzędzia->Płytki wybieramy płytkę Generic ESP8266 Module.
4. Do poprawnego działania przykładów będą nam potrzebne dwie dodatkowe biblioteki: ArduinoJson (obsługa JSON) i Adafruit NeoPixel (obsługa paska LED). Aby je zainstalować wchodzimy w Szkic->Dołącz bibliotekę->Zarządzaj bibliotekami, a następnie z poziomu Menadżera bibliotek znajdujemy je i instalujemy.

# Wgrywanie programu na moduł
Aby wgrać program na moduł ESP musimy skorzystać z konwertera USB-UART. Schemat podpięcia zasilania, modułu ESP i przedstawiony został poniżej.

