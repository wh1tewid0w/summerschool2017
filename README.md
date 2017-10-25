# Summer School 2017


## Projektumfeld:
Das Projekt wurde im Kommunikations- und Informationszentrum (kiz) der Universität Ulm durchgeführt. 
Dabei handelte es sich um ein internes Projekt des kiz, dass im Rahmen der jährlichen einwöchigen Summer School für alle Fachinformatiker*innen Auszubildenden durchgeführt wurde.  



## Projektbeschreibung:
Projektziel ist der Bau einer Wetterstation, die:
- Temperatur
- Luftfeuchtigkeit
- Luftdruck
- Helligkeit
- Bodenfeuchtigkeit 

ausmessen und ausgeben kann.
 
Die Wetterdaten werden mit Sensoren gemessen und mithilfe des LoraWan-Protokoll an ein Gateway übergeben. Das Gateway schickt die Daten in IP-Paketen an das Backend vom Internet of Things.
Dort werden die Daten dann mithilfe von Node Red abgeholt und in eine InfluxDB gespeichert. 
Als Ausgabetool wird Grafana verwendet, dass die Sensordaten von der InfluxDB bekommt und darstellt. 


## Hardware-Komponenten
- Adafruit Feather M0
- BME 280 (Luftdruck, Luftfeuchtigkeit, Temperatur)
- Temt 6000 (Lichtsensor)
- Optional: 
	- Soil Moisture Sensor (Bodenfeuchtigkeitssensor)
	- Display SSD1306

	
## Fazit
- Sensor läuft seit Donnerstag und schickt Daten 
- Doku zum nachlesen auf Github, kann nachgebaut werden
- Kosten belaufen sich auf ca 40€ (Kosten sind nicht optimiert)

## Ausblick
- Jeder von uns kann es anhand der Doku nachbauen 
- Display
- Gehäuse
- Benutzung in der Bibliothek
- Massenproduktion möglich
- Solarzelle für Energieeffizienz
	
	
	
