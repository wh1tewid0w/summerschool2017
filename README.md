# Summerschool2017


## Projektumfeld:
Das Projekt wurde im Kommunikations- und Informationszentrum (kiz) der Universität Ulm durchgeführt. 
Dabei handelte es sich um ein internes Projekt des kiz, dass im Rahmen der jährlichen einwöchigen Summer School für alle Fachinformatiker*innen Auszubildenden durchgeführt wurde.  
Das kiz wurde 2002 gegründet und hat die früheren zentralen Einrichtungen Universitätsbibliothek, Universitätsrechenzentrum und Zentrale für Fotografie, 
Grafik und Reproduktion zusammengefasst. Das kiz umfasst zurzeit rund 140 Beschäftigte und wird von Herrn Prof. Dr. Ing. Stefan Wesner geleitet. 
Zu den Aufgaben des kiz gehört es, den Hochschulbetrieb in den Bereichen Forschung, Lehre, Studium und Verwaltung durch Sicherung einer 
bedarfsgerechten Informationsversorgung zu unterstützen.
Das kiz untergliedert sich in 5 Abteilungen, mit denen die 3 Dienstleistungsbereiche abgedeckt werden.


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