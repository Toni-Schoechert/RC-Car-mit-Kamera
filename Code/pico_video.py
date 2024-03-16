import cv2
import numpy as np
import serial

# Serielle Verbindung einrichten
ser = serial.Serial('/dev/ttyACM0', 115200)

# Größe des Bildes
width = 160
height = 120

# Video-Writer erstellen
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (width, height))

# Fenster für das Video erstellen
cv2.namedWindow('Frame', cv2.WINDOW_NORMAL)

while True:
    # Seriellen Puffer leeren
    ser.reset_input_buffer()

    # Bilddaten von der seriellen Verbindung empfangen
    frame = ser.read(width * height)

    # Sicherstellen, dass genug Daten empfangen wurden
    if len(frame) == width * height:
        # Bilddaten in ein Bild umwandeln
        img = np.frombuffer(frame, dtype=np.uint8).reshape((height, width))

	        # Video auf den Kopf stellen
        img_flipped = cv2.flip(img, -1)  # Vertikales Spiegeln
        
        # Video-Writer schreiben
        out.write(img_flipped)

        # Video im Fenster anzeigen
        cv2.imshow('Frame', img_flipped)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        print("Ungültige Daten empfangen!")

# Ressourcen freigeben
out.release()
cv2.destroyAllWindows()

