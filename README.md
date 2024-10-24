Prezentare generala

Acest cod controleaza un sistem de incarcare care utilizeaza 4 LED-uri albastre si un LED RGB. Doua butoane, START si STOP, 
sunt utilizate pentru a porni si a opri secventa de incarcare. LED-urile albastre clipesc pentru a indica progresul procesului de incarcare, 
iar LED-ul RGB isi schimba culorile pentru a arata starea de incarcare (rosu pentru incarcare si verde pentru oprire sau idle).


Definirea pinilor

BLUE1_PIN (Pin 10): Controleaza primul LED albastru.
BLUE2_PIN (Pin 9): Controleaza al doilea LED albastru.
BLUE3_PIN (Pin 8): Controleaza al treilea LED albastru.
BLUE4_PIN (Pin 7): Controleaza al patrulea LED albastru.
RED_RGB_PIN (Pin 6): Controleaza canalul rosu al LED-ului RGB.
GREEN_RGB_PIN (Pin 5): Controleaza canalul verde al LED-ului RGB.
BLUE_RGB_PIN (Pin 4): Controleaza canalul albastru al LED-ului RGB.
START_PIN (Pin 2): Este conectat la butonul de START.
STOP_PIN (Pin 3): Este conectat la butonul de STOP.


Descriere variabile

buttonState: Stocheaza starea actuala a butonului START.
lastButtonState: Stocheaza ultima stare a butonului START, folosita pentru debounce.
lastDebounceTime: Retine timpul ultimei schimbari de stare a butonului START.
debounceDelay: Defineste timpul de debounce (50ms).
stopButtonState: Stocheaza starea actuala a butonului STOP.
lastStopButtonState: Stocheaza ultima stare a butonului STOP, folosita pentru debounce.
lastStopDebounceTime: Retine timpul ultimei schimbari de stare a butonului STOP.
stopButtonPressTime: Retine cat timp este tinut apasat butonul STOP.
charging: Flag care indica daca procesul de incarcare este in curs.


Functii principale

-setup()

Initializeaza toti pinii ca input sau output.
Seteaza rezistentele pull-up interne pentru butoanele START si STOP.
Porneste LED-ul RGB pe verde (idle).


-loop()

Verifica periodic starea butonului START si, folosind debounce, detecteaza cand este apasat.
La apasarea butonului START, se porneste secventa de incarcare prin functia startCharging().
Verifica de asemenea butonul STOP si opreste procesul de incarcare daca este tinut apasat mai mult de 1 secunda, apelând functia stopCharging().


-startCharging()

Porneste secventa de incarcare si seteaza LED-ul RGB pe rosu (indica starea de incarcare).
LED-urile albastre clipesc in secvente pentru a simula procesul de incarcare.
Dupa terminarea secventei, toate LED-urile albastre clipesc de 3 ori pentru a semnala finalizarea incarcarii.
La final, LED-ul RGB se seteaza din nou pe verde (idle).


-checkStopButton()

Verifica daca butonul STOP este apasat.
Daca este apasat, apeleaza functia stopCharging() pentru a opri procesul de incarcare.


-stopCharging()

Opreste procesul de incarcare, stinge toate LED-urile albastre si LED-ul RGB.
LED-urile albastre clipesc de 3 ori pentru a semnala oprirea procesului.
LED-ul RGB este setat inapoi pe verde.
Mecanism de debounce
Debouncing-ul este utilizat pentru a preveni declansarea falsa a butoanelor din cauza zgomotului mecanic. Pentru aceasta, 
se monitorizeaza fiecare schimbare de stare a butoanelor, si o schimbare este validata doar daca a ramas stabila pentru un anumit timp 
(debounceDelay).

-Secventa de incarcare

Cand butonul START este apasat, LED-ul RGB devine rosu pentru a indica starea de incarcare.
LED-urile albastre clipesc in secvente pentru a reprezenta progresul incarcarii.
La final, toate LED-urile albastre clipesc de 3 ori pentru a semnala finalizarea procesului.
Oprirea incarcarii
Apasand butonul STOP pentru mai mult de 1 secunda, se opreste procesul de incarcare.
LED-urile albastre clipesc de 3 ori pentru a semnala oprirea, iar LED-ul RGB revine la verde.

Video Buton start :https://github.com/Patrascu02/TEMA1-ROBOTICA/blob/main/buton-start.mp4
Video Buton stop :https://github.com/Patrascu02/TEMA1-ROBOTICA/blob/main/buton-stop.mp4



Link wokwi :https://wokwi.com/projects/412549149853231105
