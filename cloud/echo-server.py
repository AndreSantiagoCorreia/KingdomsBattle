# echo-server.py

import socket
import threading

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 23535# 65432  # Port to listen on (non-privileged ports are > 1023)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen() # listen incoming connections

clients = [] # store clients that connected
nicknames = [] # store the nickname of choice for each client that connects
rooms = [] # Store tuples of clients to connect them together
waitingMM = [] # Store clients waiting for matchmaking

# Sends a message to every client
def broadcast(message):
    for client in clients:
        client.send(message)

# Creates room and "isolate" two players for an 1v1 battle
def createRooms(index1, index2):
    print(f'Creating room: {nicknames[index1]} vs {nicknames[index2]}')
    rooms.append( (clients[index1], clients[index2]) )
    #rooms.append(clients[index2])

# Sends a message to your opponent
def chat(message, client):
    try:
        for tuples in rooms:
            #print(len(tuples))
            if client in tuples:
                if client == tuples[1]:
                    tuples[0].send(message)
                    break
                else:
                    tuples[1].send(message) 
                    break
        #index = rooms.index(client)
        #print("Room length: " + len(rooms))
        #if index % 2 == 0:
        #    rooms[index + 1].send(message)
        #else:
        #    rooms[index - 1].send(message)
    except:
        client.send(f'Waiting for available opponents...'.encode('ascii'))

# Handle connections
def handle(client):
    while True:
        try:
            message = client.recv(1024) #1024 bytes
            #broadcast(message)
            chat(message, client)
        except: # remove client if it has left
            index = clients.index(client)
            nickname = nicknames[index]
            chat(f'{nickname} left the room'.encode('ascii'), client)
            for tuples in rooms:
                if client in tuples:
                    if client == tuples[0]:
                        if len(waitingMM) == 0:
                            waitingMM.append(tuples[1])
                            tuples[1].send(f'Your Opponent has left the game... No opponent available...\n'.encode('ascii'))
                        else:
                            index1 = clients.index(waitingMM[0])
                            waitingMM.remove(clients[index1])
                            index2 = clients.index(client)
                            createRooms(index1, index2)
                    else:
                        if len(waitingMM) == 0:
                            waitingMM.append(tuples[0])
                            tuples[0].send(f'Your Opponent has left the game... No opponent available...\n'.encode('ascii'))
                        else:
                            index1 = clients.index(waitingMM[0])
                            waitingMM.remove(clients[index1])
                            index2 = clients.index(client)
                            createRooms(index1, index2)
                    rooms.remove(tuples)
                    break
            clients.remove(client)
            client.close()
            broadcast(f'{nickname} left the server'.encode('ascii'))
            nicknames.remove(nickname)
            break

# Accepting every connection
def receive():
    while True:
        client, address = server.accept()
        print(f"Connected with {str(address)}")
        client.send('SINGLE'.encode('ascii'))
        string = client.recv(1024).decode('ascii')
        string = string[0]
        if string == "Y":
            # Run singleplayer mode
            print("Starting AI...")
        else:
            # add client to the list
            client.send('NICK'.encode('ascii'))
            nickname = client.recv(1024).decode('ascii')
            nickname = nickname[0:len(nickname)]
            nicknames.append(nickname)
            clients.append(client)
            if len(waitingMM) == 0:
                waitingMM.append(client)
                client.send(f'No opponent available...\n'.encode('ascii'))
            else:
                index1 = clients.index(waitingMM[0])
                waitingMM.remove(clients[index1])
                index2 = clients.index(client)
                createRooms(index1, index2)

            print(f'Nickname is: {nickname}')
            broadcast(f'{nickname} joined the server\n'.encode('ascii'))
            client.send('Connected to the server'.encode('ascii'))

            thread = threading.Thread(target=handle, args=(client,))
            thread.start()
# Run the server
receive()