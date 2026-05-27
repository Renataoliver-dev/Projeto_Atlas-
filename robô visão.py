# arduino = serial.Serial('COM3', 9600)
# time.sleep(2)

import cv2
import mediapipe as mp
import serial
import time

# Tenta conectar ao Arduino. Ajuste a porta 'COM3' se necessário.
try:
    arduino = serial.Serial('COM3', 9600)
    time.sleep(2)
except:
    print("Arduino não encontrado na porta COM3. Verifique a conexão.")
    arduino = None

# Configuração do Mediapipe
mp_maos = mp.solutions.hands
maos = mp_maos.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_desenho = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

print("A.T.L.A.S. ativo! Mão aberta = Frente, Fechada = Parar.")

while cap.isOpened():
    sucesso, frame = cap.read()
    if not sucesso: break

    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    resultado = maos.process(frame_rgb)

    comando = 'P' # Por padrão, para o carrinho

    if resultado.multi_hand_landmarks:
        for hand_landmarks in resultado.multi_hand_landmarks:
            # Posição X (horizontal) da mão
            pos_x = hand_landmarks.landmark[9].x
            
            # Lógica: Dedo médio (12) acima da base (9) = Aberta
            dedo_medio_y = hand_landmarks.landmark[12].y
            base_dedo_y = hand_landmarks.landmark[9].y
            
            if dedo_medio_y < base_dedo_y: # Mão Aberta
                if pos_x < 0.33: comando = 'E'
                elif pos_x > 0.66: comando = 'D'
                else: comando = 'F'
            else: # Mão Fechada
                comando = 'P'
            
            mp_desenho.draw_landmarks(frame, hand_landmarks, mp_maos.HAND_CONNECTIONS)

    # Envia para o Arduino
    if arduino and arduino.is_open:
        arduino.write(comando.encode())
    
    cv2.imshow('A.T.L.A.S. - Controle', frame)
    if cv2.waitKey(1) == 27: break

cap.release()
cv2.destroyAllWindows()
# if arduino: arduino.close()
# if arduino and arduino.is_open:
#     arduino.write(comando.encode())