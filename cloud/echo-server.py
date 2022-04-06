# echo-server.py

from random import randint
import socket
import threading

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 53535# 65432  # Port to listen on (non-privileged ports are > 1023)
MAXROUNDS = 9 #number of rounds that should be played

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
    order = randint(0, 1)
    if(order):
        print(f'Creating room: {nicknames[index1]} vs {nicknames[index2]}')
        #rooms.append( (clients[index1], clients[index2], 0))
        rounds = 0
        roundBuff = str(randint(0,2))
        player1Ult = str(randint(0,4))
        player2Ult = str(randint(0,4))
        rooms.append( [clients[index1], clients[index2], rounds, roundBuff])
        print(rooms[0][2])
        clients[index1].send(f'{player1Ult}{player2Ult}'.encode('ascii'))
        clients[index2].send(f'{player2Ult}{player1Ult}'.encode('ascii'))
        clients[index1].send(f'You will start the round{roundBuff}'.encode('ascii'))
        #clients[index1].send(f'{roundBuff}'.encode('ascii'))
        #clients[index1].send(f'g'.encode('ascii'))
    else:
        print(f'Creating room: {nicknames[index2]} vs {nicknames[index1]}')
        #rooms.append( (clients[index2], clients[index1], 0) )
        rounds = 0
        roundBuff = str(randint(0,2))
        player1Ult = str(randint(0,4))
        player2Ult = str(randint(0,4))
        rooms.append( [clients[index2], clients[index1], rounds, roundBuff] )
        print(rooms[0][2])
        clients[index1].send(f'{player1Ult}{player2Ult}'.encode('ascii'))
        clients[index2].send(f'{player2Ult}{player1Ult}'.encode('ascii'))
        clients[index2].send(f'You will start the round{roundBuff}'.encode('ascii'))
        #clients[index2].send(f'{roundBuff}'.encode('ascii'))
        #clients[index2].send(f'g'.encode('ascii'))
    #rooms.append(clients[index2])

# Sends a message to your opponent
def chat(message, client):
    try:
        for tuples in rooms:
            #print(len(tuples))
            if client in tuples:
                if client == tuples[1]:
                    try:
                        if message.decode('ascii').find("gameEnded") != -1:
                            endGame(tuples[0], tuples[1])
                    except:
                        print("continue...")
                    tuples[0].send(message)
                    tuples[0].send(f'{tuples[3]}'.encode('ascii'))
                    #tuples[0].send(f'g'.encode('ascii'))
                    tuples[2] += 1
                    #tuples[3] = str(randint(0,2))
                    #print(tuples[2])
                    if tuples[2] == MAXROUNDS:
                        endGame(tuples[0], tuples[1])
                    break
                else:
                    try:
                        if message.decode('ascii').find("gameEnded") != -1:
                            endGame(tuples[0], tuples[1])
                    except:
                        print("continue...")
                    tuples[1].send(message)
                    tuples[1].send(f'{tuples[3]}'.encode('ascii'))
                    tuples[3] = str(randint(0,2))
                    #tuples[1].send(f'g'.encode('ascii')) 
                    break
    except:
        print("Exception in chat method")
        #client.send(f'Waiting for available opponents...'.encode('ascii'))

# Function to send signals that the game should now end
def endGame(client1, client2):
     print("Rounds limit reached, closing room and clients")
     client1.close()
     client2.close()
     return 0

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
                            #tuples[1].send(f'No opponent available... Your Opponent has left the game...'.encode('ascii'))
                        else:
                            index1 = clients.index(waitingMM[0])
                            waitingMM.remove(clients[index1])
                            index2 = clients.index(client)
                            createRooms(index1, index2)
                    else:
                        if len(waitingMM) == 0:
                            waitingMM.append(tuples[0])
                            #tuples[0].send(f'No opponent available... Your Opponent has left the game...'.encode('ascii'))
                        else:
                            index1 = clients.index(waitingMM[0])
                            waitingMM.remove(clients[index1])
                            index2 = clients.index(client)
                            createRooms(index1, index2)
                    rooms.remove(tuples)
                    break
            clients.remove(client)
            client.close()
            print(f'{nickname} left the server'.encode('ascii'))
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
            nickname = client.recv(1024).decode('ascii').rstrip("\x00") #Clean buffer sent from C file
            nickname = nickname[0:len(nickname) - 1] #Clean buffer sent from C file
            nicknames.append(nickname)
            clients.append(client)
            if len(waitingMM) == 0:
                waitingMM.append(client)
                #client.send(f'No opponent available...'.encode('ascii'))
            else:
                index1 = clients.index(waitingMM[0])
                waitingMM.remove(clients[index1])
                index2 = clients.index(client)
                createRooms(index1, index2)

            print(f'Nickname is: {nickname}')
            #broadcast(f'{nickname} joined the server\n'.encode('ascii'))
            #client.send('Connected to the server'.encode('ascii'))

            thread = threading.Thread(target=handle, args=(client,))
            thread.start()
# Run the server
receive()