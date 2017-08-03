
Hardware:

Feather M0 Basic Proto
BME 280 -> Temperatur, Luftdruck & Luftfeuchtigkeit
Temt  6000 -> Ambient Light
Light Blocking *
Bodenfeuchtigkeit *
Display * (adafruit)
Gehäuse (Verteiler-Dose)

* Optionale Features


Frontend: (Graphische Darstellung der Daten)
Grafana


Was müssen wir Wissen? 
Feather Programmierung
Wie werden die verschiedenen Sensoren ausgelesen? 
Wie werden die ausgelesenen Daten verstanden/interpretiert? 
Verschicken der Daten mit LoRa
Node-RED Anbindung an die Influx-DB (Datenbank) und
    Visualisierung der Daten mit Grafana (VM in der bwCloud mit 
    Ubuntu als OS) 
Relative - und absolute Luftfeuchtigkeit
Nebel-Wert (als optionaler Wert (?))
Warum Influx-DB & Node-RED?
extra Chip -> RFM95W auf dem Feather
Frequenz Band ISM LoRa 
------------------------------------------------------


## Zeitplan: 
# Montag 31.07.2017
- Besprechen der Projektdurchführung 
- Planen der anfallenden Aufgaben
- Vortrag für Dienstag vorbereiten

# Dienstag 01.08.2017
- Vortrag besprechen ggf. überarbeiten
- Sammeln der benötigten Materialien (Datenblätter der Sensoren, Links..)
- Aufbau der Schaltung mit dem Arduino und den Sensoren
    - Programmierung des  Arduino und der zugehörigen Sensoren
- VM in der bwCloud einrichten
    - Node Red, InfluxDB und Grafana installiert

# Mittwoch 02.08.2017
- Anfangen die Doku zu schreiben, Github
- Node Red, InfluxDB und Grafana verbunden -> Auswerten erster Testdaten
- Sensor Daten über Lora an The Things Network gesendet

# Donnerstag 03.08.2017
- Zwischenpräsentation halten 
- Testläufe des Arduino mit ggf. Fehlererkennung und -behebung

Vorbereiten der Abschlusspräsentation 

# Freitag 04.08.2017
Abschlusspräsentation vorbereiten/verbessern 
14:00 Uhr Abschlusspräsentation


