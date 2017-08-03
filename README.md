## Summerschool2017

Ziel ist der Bau einer Wetterstation, die:
- Temperatur
- Luftfeuchtigkeit
- Luftdruck
- Helligkeit
- Bodenfeuchtigkeit 
ausmessen und ausgeben kann. 

Die Ausgabe der Daten wird durch Lora übertragen und im Internet of Things gespeichert. 
Dort werden die Daten dann mithilfe von Node Red abgeholt und in eine InfluxDB gespeichert. 
Als Ausgabetool wird Grafana verwendet, dass die Sensordaten von der InfluxDB bekommt. 