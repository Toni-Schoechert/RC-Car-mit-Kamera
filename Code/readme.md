# Pico Programieren
Als Entwicklungsumgebung für den Raspberry Pi Pico diente die Pico SDk C/C++. Die Installation erfolgt mittels eigenem Installer. Durch die Installation steht dann Pico-VS Code zur Verfügung. Per Pico-VS Code kann dann der entsprechende Ordner mit dem Code geladen werden. In der Konfiguration muss nun der PICO ARM GCC ausgewählt werden. Dies passiert automatisch bei laden der Dateien oder manuell unter "configure" in CMake. Anschließend erstellt CMake die nötigen Dateien im Ordner build. Zum Schluss muss die im "Build"-Ordner erstellte UF2-Datei, hier "car.uf2", auf den Pico kopiert werden. Um das kopieren der Datei möglich zu machen, muss der Pico per USB an den Computer angeschlossen werden während die BOOTSEL-Taste gedrückt wird.
Der Pico sollte nun den Code ausführen. Hat der Pico sich mit dem W-Lan verbunden leuchtet die LED dauerhaft. Im Fall, dass die Kamera nicht richtig verbunden ist, wird die LED zweimal kurz blinken.
Zu beachten ist, dass die SSID und das Passwort an das eigene W-Lan angepasst werden muss.

# Video auslesen
Das Auslesen des Videos erfolgt indem der Raspberry Pi Pico per USB mit einem PC verbunden wird. Der PC sollte Python, und speziell noch opencv, numpy und pyserial installiert haben. Zum Anzeigen des Videos muss 
das in Python geschriebene Programm pico_video ausgeführt werden.
Unter Windows muss in `ser = serial.Serial('/dev/ttyACM0', 115200)` /dev/ttyACMO zu dem entsprechenden COM Port gewechselt werden.

# Quellen
Für die Kamera wurde folgende Bibliothek verwendet: [hm01b0-library-for-pico](https://github.com/ArmDeveloperEcosystem/hm01b0-library-for-pico?tab=readme-ov-file) (Stand 10.03.2024)
Für den entsprechenden Webserver diente [pico-w-webserver-template](https://github.com/LearnEmbeddedSystems/pico-w-webserver-template) (Stand 08.03.2024) als Vorlage.
