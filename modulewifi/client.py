import socket
import sys

def client_program(msg):
    host = "192.168.1.15"
    port = 80
    timeout = 10  # Définir le timeout à 10 secondes

    client_socket = socket.socket()
    client_socket.settimeout(timeout)  # Définir le timeout pour les opérations de réception
    try:
        client_socket.connect((host, port))

        message = msg
        client_socket.send(message.encode())
        data = client_socket.recv(1024).decode()

        print('Message reçu du serveur : ' + data)
    except socket.timeout:
        print('Timeout : Aucune réponse du serveur dans les {} secondes.'.format(timeout))
    except Exception as e:
        print('Erreur :', e)
    finally:
        client_socket.close()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Utilisation: python3 client.py msg")
    else:
        msg = sys.argv[1]
        client_program(msg)
