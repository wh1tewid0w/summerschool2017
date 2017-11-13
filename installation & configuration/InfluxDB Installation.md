# InfluxDB Installation und Kofiguration (Ubuntu/Debian)
## Installation
### Step 1: Herunterladen des InfluxDB Package
```bash
wget https://dl.influxdata.com/influxdb/releases/influxdb_1.3.7_amd64.deb
```

### Step 2: Installieren
```bash
sudo dpkg -i influxdb_1.3.7_amd64.deb
```

### Step 3: Datenbank starten
```bash
influxd
```
##### Optional in Screen starten
```bash
screen -d -m influxd
```
## Konfiguration
### Datenbank anlegen für Messwerte (vor Node-RED Konfiguration anlegen)
1. Influx Shell öffnen mit `influx` auf Server (VM/Putty etc.)
2. `CREATE DATABASE DB_NAME`
#### Für weitere Konfiguration
Um Datenbank zu selektieren `USE DB_NAME`

Messwerte zurücksetzen `DROP SERIES FROM /.*/`
