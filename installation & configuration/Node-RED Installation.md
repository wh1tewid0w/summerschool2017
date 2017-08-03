# Node-RED Installation und Konfiguration (Ubuntu/Debian)
## Installation
### Step 1: Node.js herunterladen und installieren
```bash
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -

sudo apt-get install -y nodejs
```

### Step 2: Installieren
```bash
sudo npm install -g --unsafe-perm node-red
```

### Step 3: Server starten
```bash
node-red
```

##### Optional in Screen starten
```bash
screen -d -m node-red
```
## Konfiguration
![Node-RED Flow Chart](../img/nodered.PNG)
