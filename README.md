# toastEspExample
Projekt aplikacji na Androida i ESP8266 - moduł świetlny oparty o ESP8266 12E komunikujący się z aplikacją mobilną przez WiFi.

Kod do wgrania z moduł ESP znajduje się w folderze `esp8266`. Plik `esp8266.ino` to wersja z paskiem ledowym, `esp8266_led` to wersja z diodą RGB.

# Konfiguracja środowiska
Aby móc programować w Arduino IDE musimy zainstalować odpowiedni Manager Płytek oraz zainstalować kilka niezbędnych bibliotek.

1. Po opdaleniu Arduino IDE wybieramy Plik->Preferencje i w polu <i>Dodatkowe adresy URL...</i> wpisujemy `http://arduino.esp8266.com/stable/package_esp8266com_index.json` (link z <a href="https://github.com/esp8266/Arduino">oficjalnej strony biblioteki ESP</a>).
2. W menu Narzędzia->Płytki->Menadżer Płytek znajdujemy i instalujemy `esp8266`.
3. W menu Narzędzia->Płytki wybieramy płytkę Generic ESP8266 Module.
4. Do poprawnego działania przykładów będą nam potrzebne dwie dodatkowe biblioteki: ArduinoJson (obsługa JSON) i Adafruit NeoPixel (obsługa paska LED). Aby je zainstalować wchodzimy w Szkic->Dołącz bibliotekę->Zarządzaj bibliotekami, a następnie z poziomu Menadżera bibliotek znajdujemy je i instalujemy.

# Wgrywanie programu na moduł
Aby wgrać program na moduł ESP musimy skorzystać z konwertera USB-UART. Schemat podpięcia zasilania, modułu ESP i przedstawiony został poniżej.

![](https://github.com/aleksandra-majchrzak/toastEspExample/blob/master/toast0_bb.png)

Konwerter oczywiście musi być podłączony do komputera. Z poziomu Arduino IDE Narzędzia->Port musimy wybrać odpowiedni port do którego podłączony został konwerter (zwykle to jedyna opcja na liście), a następnie normalnie wgrać projekt na moduł.

Po prawidłowym wgraniu programu na dole Arduio IDE powinniśmy zobaczyć wyjście podobne do tego na screenie poniżej.

![](https://github.com/aleksandra-majchrzak/toastEspExample/blob/master/loading.png)

Jeśli w tym momencie na ekranie zamiast informacji o załadowaniu pliku widzisz informacje o błędach, sprawdż czy poprawnie podłączyłeś wszystkie kable oraz czy dostaczyłeś do układu odpowiednie zasilanie. Żle dobrane zasilanie to najczęstsza przyczyna błędów we wgrywaniu i działaniu programu. Więcej informacji o potencjalnych problemach znajdziesz w <a href="https://arduino-esp8266.readthedocs.io/en/latest/faq/readme.html">oficjalnej dokumentacji biblioteki</a>

# Uruchamianie programu
W celu uruchomienia programu należy usunąć kilka kabli z ESP oraz dodać elementy do diody/paska LED zgodnie z poniższym schematem.

![](https://github.com/aleksandra-majchrzak/toastEspExample/blob/master/toast1_bb.png)

![](https://github.com/aleksandra-majchrzak/toastEspExample/blob/master/toast2_bb.png)

Poniżej zdjęcie zmontowanego ukłdu z diodą RGB.
![](https://github.com/aleksandra-majchrzak/toastEspExample/blob/master/IMG_1810.png)


W kodzie modułu większość istotnych kominikatów (takich jak uzyskany adres IP) wypisywane są za pomocą konwertera USB-UART do Monitora szeregowego Arduino IDE. Aby otworzyć Monikor szeregowy wybierz Narzędzia->Monitor portu szeregowego.

# Uwagi
Pamiętaj, że do poprawnej komunikacji aplikacji z modułem oba urządzenia powinny być podłączone do tej samej sieci WiFi. A co za tym idzie, w kodzie modułu musisz wpisać nazwę i hasło sieci, do której ma się on podłączyć, a w aplikacji mobilnej musisz wpisać adres IP modułu, który uzyskasz gdy połączy się on już do sieci.
