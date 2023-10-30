import serial
import serial.tools.list_ports
import time


#32 caractere max car ecran 16*2
char_ecran=32


# Fonction pour récupérer le port série de l'Arduino
def recup_port_Arduino():
    ports = list(serial.tools.list_ports.comports())
    mData = 0
    for p in ports:
        print(p.description)
        if 'USB2.0-Serial' in p.description:
            mData = serial.Serial(p.device, 9600)
    return mData


#Envoie de tranche de msg avec la cadence de 1 par sec
def lst_send_32(arduino,chaine,char_max):
    if arduino is not None and arduino.is_open:
        #time.sleep(1)
        for i in range(0, len(chaine), char_max):
            msg = chaine[i:i+char_max]
            print(f"Message envoyé à l'Arduino: {msg}")
            arduino.write(msg.encode())
            

Data = recup_port_Arduino()
while(True):
    if Data is not None and Data.is_open:
        message = input(" q pour quit || ecris le msg a afficher : ")
        if(message=="q"):
            break
        if(len(message)>char_ecran):
            print("le message est trop long et envoyer par morceaux")
            lst_send_32(Data,message,char_ecran)
        else:
            Data.write(message.encode())
            print(f"Message envoyé à l'Arduino simple: {message}")
    else:
        print("Port série non disponible ou non ouvert.")