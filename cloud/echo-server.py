AndreSC0407
#7987
proposal
Cassiel Jung — Yesterday at 3:01 PM
I will just push whatever i have rn
cuz it should be the latest one
Ziqiqiqll — Yesterday at 3:01 PM
ok
Cassiel Jung — Yesterday at 3:02 PM
You know what? There's nothing I can push again lol
Image
The first thing I saw from the terminal is everything is pushed 🤣
AndreSC0407 — Yesterday at 3:02 PM
:))))))))))))
Cassiel Jung — Yesterday at 3:03 PM
Ignore the comment on github🙃
AndreSC0407 — Yesterday at 3:03 PM
Ok so I just met with Mike, we have something to test (we didnt yet I have to go to my class 😦 ) We should be good  after meeting today at lab and debug a little bit
I just have one concern with the code he sent under useful links which is how we decode the messsage... I was trying to do something similar earlier on and I was getting a lot of unexpected exceptions hm
Let's hope we can find a way and we have our product complete 😄
Cassiel Jung — Yesterday at 3:16 PM
You mean the server code?
Nick — Yesterday at 3:46 PM
The usual lab is full again. I'm in the same room we were at yesterday
Cassiel Jung — Yesterday at 3:47 PM
Kk do u have mike's keyboard as well?
Nick — Yesterday at 3:47 PM
nope
AndreSC0407 — Yesterday at 3:47 PM
yess
Cassiel Jung — Yesterday at 4:03 PM
Let's see what happens after we combine that with current client code🙃
AndreSC0407 — Yesterday at 4:03 PM
yeahh, be there around 5-5:10
Ziqiqiqll — Yesterday at 4:32 PM
umm i think i left my keyboard beside my door...
i will pick it up
AndreSC0407 — Yesterday at 4:58 PM
heading to the lab right now!
Ziqiqiqll — Yesterday at 5:09 PM
on my way
AndreSC0407 — Yesterday at 9:59 PM
mike text me if you are stuck outside
i think the door is locked already LOL
Ziqiqiqll — Yesterday at 10:02 PM
umm
yes i just realized that
she lockedthe door infornt of me
yup
can anyone open the door thxthx
Cassiel Jung — Yesterday at 10:04 PM
Where u at tn?
Ziqiqiqll — Yesterday at 10:05 PM
watetgageside
water
downstair
Cassiel Jung — Yesterday at 10:05 PM
Oh first floor?
https://docs.google.com/presentation/d/15dYAXkHCo0-qbBDM2vqRl1DnCyhL1a8F5SRvBLEwZAM/edit?usp=sharing
Google Docs
CPEN391_L2C_39
Multiplayer Card Game: Kingdom Battle L2C Team39 Final Project Demo Andre Santiago Correia, Cassiel Jung, Nick Zhang, Mike He

Cassiel Jung — Today at 1:04 AM
Should we present at the lab at 9am tmr?
AndreSC0407 — Today at 1:05 AM
I am not sure how it works lol but I will be there at 9
arent we the last oens to present?
Cassiel Jung — Today at 1:06 AM
yes we are but we should be there sth like 30 min before to be ready i guess
Nick — Today at 1:06 AM
Yeah but I think we better be there early to make sure everthing is set up correctly
Cassiel Jung — Today at 1:07 AM
kk so I'll get there in 9:30ish
Nick — Today at 1:07 AM
And also to get ready for the presentation
Ziqiqiqll — Today at 1:07 AM
OK
Nick — Today at 1:08 AM
@Ziqiqiqll Your laptop has ethernet port right?
AndreSC0407 — Today at 1:09 AM
Alrighttt
Cassiel Jung — Today at 1:12 AM
@AndreSC0407 we had picture on the proposal lol
Image
AndreSC0407 — Today at 1:12 AM
NOWAY
HAHAHAHHA
it looks just like it
😍
Ziqiqiqll — Today at 1:14 AM
umm let me take a look
yes
Nick — Today at 1:17 AM
kk then we can probably use your laptop to set up the server for the demo then. I'm afraid that mine is going to freeze during the demo lol
Ziqiqiqll — Today at 1:17 AM
lol
ok
Cassiel Jung — Today at 1:17 AM
Mike do you have putty on your laptop?
Ziqiqiqll — Today at 1:17 AM
yuo
yup
Cassiel Jung — Today at 1:18 AM
ok great
see you all tmr 🙂
Ziqiqiqll — Today at 1:18 AM
^^
AndreSC0407 — Today at 1:28 AM
🙂 I Will be there 9:15max 
Nick — Today at 9:12 AM
I'm in the lab
at deck 27
Ziqiqiqll — Today at 9:16 AM
coming
Cassiel Jung — Today at 9:28 AM
Dont forget the keyboard!
Ziqiqiqll — Today at 10:28 AM
if roundbuff == 2:
            player_score = player_score * 0.6
        elif roundbuff == 3:
            player_score = player_score * 1.25
Ziqiqiqll — Today at 11:01 AM
def output_function(roundbuff, left_cards, stat, card_on_deck, index): #stat in string

    # read current status
    # suppose the file name is read_me.txt, it is kept overwrote
    # type is string

    #user_action = open(".\read_me.txt", "r")[0].strip() #only has one line

    #remain_card = open(".\read_me_remain.txt", "r")[0].strip() #only has one line

    result = 's' #initialize

    #2,[0,1,3,4,5,7,8,9,10,11,12],26,3,8,0

    #here leftcards
    user_action = str(roundbuff) + ',' + str(left_cards).replace(' ', '') + ',' + stat

    learning_list[index].append(user_action)
learning_list_result[index].append(result)

    return result
learning_list = []
learning_list_result = []
cards_Remain_list.append([0,1,2,3,4,5,6,7,8,9,10,11,12])
            ai_card_Remain_list.append([0,1,2,3,4,5,6,7,8,9,10,11,12])
            AIList_list.append([0,0,0,0]) #shares index
            learning_list.append([])
            learning_list_result.append([])
AndreSC0407 — Today at 11:02 AM
yo nick if the prof wanna try out our game make sure you close the server after the demo so that he doesnt notice any bug
and then u can safely restart the server w/o problema
🤙🤙
Ziqiqiqll — Today at 11:03 AM
if client in tuples:
                    if AIList_list[i][1] > 0: #AI wins
                        f = open("../AI/Generating_Database/cleaned_data.txt", "a")
                        for item in learning_list:
                            f.write("%s\n" % item)
                        f.close()
                        f = open("../AI/Generating_Database/cleaned_data_result.txt", "a")
                        for item in learning_list_result:
                            f.write("%s\n" % item)
                        f.close()
                    cards_Remain_list.pop(i)
                    ai_card_Remain_list.pop(i)
                    AIList_list.pop(i)
                    learning_list.pop(i)
                    roomsAI.remove(tuples)
                    break
Ziqiqiqll — Today at 11:12 AM
be back in 5
Cassiel Jung — Today at 11:16 AM
@Ziqiqiqll we are the next
Ziqiqiqll — Today at 11:17 AM
ok
coming
Ziqiqiqll — Today at 11:24 AM
TODO add a read me in git hub repo
Ziqiqiqll — Today at 2:24 PM
we are meeting in liferight？
Nick — Today at 2:25 PM
Yeah I think we can
Cassiel Jung — Today at 2:26 PM
Yup at 3:30
Ziqiqiqll — Today at 2:30 PM
yup
AndreSC0407 — Today at 2:48 PM
be there at 3:45-4:00
Cassiel Jung — Today at 3:15 PM
Just realized we still need to take video. Does lab rooms opened after the term ends?
Nick — Today at 3:19 PM
I think so
The building should be open
Cassiel Jung — Today at 3:19 PM
kk I am the lab now where we demo somehow lecture finished 10min early
Nick — Today at 3:20 PM
@Ziqiqiqll also can you bring the keyboard? I think I fixed the issues we encountered earlier today so we can do a quick test and finalize our code with the correct version
Cassiel Jung — Today at 3:21 PM
if he can bring the keyboard we can take video today too
Ziqiqiqll — Today at 3:21 PM
yesyesy
Nick — Today at 3:21 PM
Yeah sure
I'm not very sure about what we need to show in the video, but we can probably include a demo run of the game which we can film today
Cassiel Jung — Today at 3:24 PM
I think we should explain the game rules and show the demo. and maybe how things are connected
Ziqiqiqll — Today at 3:31 PM
coming
AndreSC0407 — Today at 3:44 PM
going rn
Cassiel Jung — Today at 3:54 PM
@AndreSC0407 we are at the lab where we worked on it yesterday
Ziqiqiqll — Today at 3:54 PM
# echo-server.py

from random import randint
import random
import socket
import threading
Expand
echo-server.py
19 KB
AndreSC0407 — Today at 3:55 PM
cool im in the bus
Nick — Today at 4:20 PM
Image
Ziqiqiqll — Today at 4:21 PM
if result == 's':
        user_input = stat.split(',') #okay we only wants last 4 and first 1
        user_input = user_input[0:1] + user_input[-4:]
        player_score = int(user_input[1]) + int(user_input[2]) * 0.6
        ai_score = int(user_input[3]) + int(user_input[4]) * 0.8

        if roundbuff == 2:
            player_score = player_score * 0.6
        elif roundbuff == 3:
            player_score = player_score * 1.25

        attack_card = []
        defense_card = []

        for item in card_on_deck:
            if item <= 6:
                attack_card.append(item)
                if ((item + 1) * 2 >= (int(user_input[3]) + int(user_input[4])) and roundbuff == 2) or (roundbuff != 2 and (item + 1) >= (int(user_input[3]) + int(user_input[4]))):
                    result = str(item)
                    break
            else:
                defense_card.append(item)

        attack_card.sort(reverse = True)
        defense_card.sort(reverse = True)

        if result == 's':
            if (len(attack_card) == 0 and len(defense_card) != 0) or user_input[0] == 1:
                #result = str(defense_card[0]) + ',1'
                result = str(defense_card[0])

            elif len(defense_card) == 0 or user_input[0] == 2:
                #result = str(attack_card[0]) + ',0'
                result = str(attack_card[0])

            elif ai_score > player_score:
                # we attack
                result = str(attack_card[0])

            else:
                result = str(defense_card[0])

    learning_list_result[index].append(result)

    return result
Nick — Today at 4:53 PM
https://drive.google.com/file/d/1Q3ffPw-O31Our8ZJgfQxa3Z-n0tV4ZFm/view?usp=sharing
Google Docs
hardware.zip
# echo-server.py

from random import randint
import random
import socket
import threading
import string
import time

HOST = "192.168.0.101"  # Standard loopback interface address (localhost)
PORT = 3000# 65432  # Port to listen on (non-privileged ports are > 1023)
MAXROUNDS = 10 #number of rounds that should be played

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen() # listen incoming connections

#changed
#global variable

cards_Remain_list = []
ai_card_Remain_list = []
AIList_list = []

learning_list = []
learning_list_result = []

#cards_Remain = [0,1,2,3,4,5,6,7,8,9,10,11,12]
#ai_card_Remain = [0,1,2,3,4,5,6,7,8,9,10,11,12]
#ai_Ult = 0

#stat, retrieve from client
#AIList = [0,0,0,0]
#ai_shield = 0
#ai_health = 0
#player_shield = 0
#player_health = 0

clients = [] # store clients that connected
nicknames = [] # store the nickname of choice for each client that connects
rooms = [] # Store tuples of clients to connect them together
roomsAI = []
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
... (362 lines left)
Collapse
echo-server.py
19 KB
﻿
Cassiel Jung — Today at 1:12 AM
@AndreSC0407 we had picture on the proposal lol
Image
Nick — 03/21/2022
it will become completely different from the proposal if we change that
Nick — 03/21/2022
well I'm not sure but I think wes should at least give ethernet a try, otherwise we need so much change in the proposal
Nick — 02/18/2022
Regarding the AI, I think what we have written in the proposal is that we are going to run it on the cloud, so DE1 shouldn't be any limitation here?
Ziqiqiqll — 02/15/2022
Can I take a look at what prof said to our proposal?
Nick — 02/08/2022
Yeah, so maybe we can join a discord call to talk about the proposal? It seems that they are not using zoom breakrooms for this purpose
Cassiel Jung — 02/08/2022
the proposal. how we submit is like a quiz
AndreSC0407 — 02/07/2022
https://docs.google.com/document/d/15mL2ZgD9D-7PvfOxqNypIlnxuDex3UQynBB4t-NoONM/edit
Google Docs
CPEN391 Project Proposal
GROUP NUMBER: 66 1. PROJECT TITLE SWIFD: Smart Watch with Internet-connected Fall-Detection 2. GENERAL PROJECT DESCRIPTION WHAT: This project will build an internet-connected Smart Watch that can detect when a person falls. The DE1-SoC will represent a prototype of the Smart Watch and it wil...

Cassiel Jung — 02/07/2022
and since tmr's lab is 3 hours, we may work on the proposal during that time after we got 'pre-approval'
AndreSC0407 — 02/07/2022
Maybe throw some ideas to some TA and get somewhat a “pre-aproval” to our proposal
AndreSC0407 — 02/07/2022
So, the proposal is to be submitted on Canvas, but I dont see a reference/example posted by the prof...
Nick — 02/07/2022
Has our professor uploaded any proposal template? I can't find it on Canvas
# echo-server.py

from random import randint
import random
import socket
import threading
import string
import time

HOST = "192.168.0.101"  # Standard loopback interface address (localhost)
PORT = 3000# 65432  # Port to listen on (non-privileged ports are > 1023)
MAXROUNDS = 10 #number of rounds that should be played

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen() # listen incoming connections

#changed
#global variable

cards_Remain_list = []
ai_card_Remain_list = []
AIList_list = []

learning_list = []
learning_list_result = []

#cards_Remain = [0,1,2,3,4,5,6,7,8,9,10,11,12]
#ai_card_Remain = [0,1,2,3,4,5,6,7,8,9,10,11,12]
#ai_Ult = 0

#stat, retrieve from client
#AIList = [0,0,0,0]
#ai_shield = 0
#ai_health = 0
#player_shield = 0
#player_health = 0

clients = [] # store clients that connected
nicknames = [] # store the nickname of choice for each client that connects
rooms = [] # Store tuples of clients to connect them together
roomsAI = []
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
                    #if tuples[2] == MAXROUNDS:
                    #    endGame(tuples[0], tuples[1])
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
#changed
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
                        if len(waitingMM) != 0:
                            index1 = clients.index(waitingMM[0])
                            waitingMM.remove(clients[index1])
                            index2 = clients.index(client)
                            createRooms(index1, index2)
                    else:
                        if len(waitingMM) != 0:
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
        thread = threading.Thread(target=dispatch, args=(client,address))
        thread.start()    

def dispatch(client, address):
    print(f"Connected with {str(address)}")
    client.send('SINGLE'.encode('ascii'))
    string = client.recv(1024).decode('ascii')
    string = string[0]
    if string == "Y":
        # Run singleplayer mode
        print("Starting AI...")

        #changed
        client.send('NICK'.encode('ascii'))
        nickname = client.recv(1024).decode('ascii').rstrip("\x00") #Clean buffer sent from C file
        nickname = nickname[0:len(nickname) - 1] #Clean buffer sent from C file
        nicknames.append(nickname)
        clients.append(client)

        #changed for many access to AI
        cards_Remain_list.append([0,1,2,3,4,5,6,7,8,9,10,11,12])
        ai_card_Remain_list.append([0,1,2,3,4,5,6,7,8,9,10,11,12])
        AIList_list.append([0,0,0,0]) #shares index
        learning_list.append([])
        learning_list_result.append([])

        #create room for AI
        createRoomsAI(clients.index(client))

        print(f'Nickname is: {nickname}')

        handleAI(client)

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
            #waitingMM.remove(clients[index2])
            createRooms(index1, index2)

        print(f'Nickname is: {nickname}')
        #broadcast(f'{nickname} joined the server\n'.encode('ascii'))
        #client.send('Connected to the server'.encode('ascii'))

        handle(client)

#changed
def createRoomsAI(index1):
    print(f'Creating room: {nicknames[index1]} vs AI')
    rounds = 0
    roundBuff = str(randint(0,2))
    player1Ult = str(randint(0,4))
    player2Ult = str(randint(0,4))
    ai_Ult = int(player2Ult)
    roomsAI.append( [clients[index1], rounds, roundBuff, ai_Ult])
    clients[index1].send(f'{player1Ult}{player2Ult}'.encode('ascii'))
    clients[index1].send(f'You will start the round{roundBuff}'.encode('ascii'))

#changed
# Handle connections
def handleAI(client):
    while True:
        try:
            message = client.recv(1024) #1024 bytes should be card information
            chatAI(message, client)
        except: # remove client if it has left
            index = clients.index(client)
            nickname = nicknames[index]
            #chatAI(f'{nickname} left the room'.encode('ascii'), client)
            for i, tuples in enumerate(roomsAI):
                if client in tuples:
                    if AIList_list[i][1] + AIList_list[i][0] > AIList_list[i][2] + AIList_list[i][3]: #AI wins
                        f = open("../AI/Generating_Database/cleaned_data.txt", "a")
                        for item in learning_list[i]:
                            f.write("%s\n" % item)
                        f.close()
                        f = open("../AI/Generating_Database/cleaned_data_result.txt", "a")
                        for item in learning_list_result[i]:
                            f.write("%s\n" % item)
                        f.close()
                    cards_Remain_list.pop(i)
                    ai_card_Remain_list.pop(i)
                    AIList_list.pop(i)
                    learning_list.pop(i)
                    roomsAI.remove(tuples)
                    break
            clients.remove(client)
            client.close()
            print(f'{nickname} left the server'.encode('ascii'))
            nicknames.remove(nickname)
            break

#changed
def chatAI(message, client): #player_array[myID]->ultimate, player_array[myID]->ultUseThisRound, myCard
    try:
        for i, tuples in enumerate(roomsAI):
            if client in tuples:
                #print("MESSAGE IS: " + message)
                stringMessage = message[0:25]
                stringMessage = str(stringMessage)
                try:
                    if stringMessage.find("gameEnded") != -1:
                        endGameAI(tuples[0])
                except:
                    print("continue...")

                # update status
                stringMessage = stringMessage[2:]
                if stringMessage.find("thestatus") != -1: # maybe in ?
                    stringMessage = stringMessage.split(' ')
                    for j in range(4):
                        AIList_list[i][j] = int(stringMessage[j])
                    #ai_health = int(stringMessage[0]) #find way to decode messg
                    #ai_shield = int(stringMessage[1])
                    #player_health = int(stringMessage[2])
                    #player_shield = int(stringMessage[3])
                    break
                else: # the message that is not for status
                    #This is not correct
                    stringMessage = stringMessage.split(' ')
                    if stringMessage[2][1] == '\\':
                        stringMessage[2] = stringMessage[2][0]
                    else:
                        stringMessage[2] = stringMessage[2][0:1]
                    client_ultimate = int(stringMessage[0])
                    client_ultuse = int(stringMessage[1]) #can i code like this
                    client_card = int(stringMessage[2])
                    sleepTime = random.uniform(1.5,3.0)
                    time.sleep(sleepTime)
                    #ENDOF This is not correct

                    if client_card in cards_Remain_list[i]: # the cards get tidied
                        cards_Remain_list[i].remove(client_card)

                    # choose card here
                    card_i1 = randint(0, len(ai_card_Remain_list[i]) - 1)

                    while True:
                        card_i2 = randint(0, len(ai_card_Remain_list[i]) - 1)
                        if (card_i2 != card_i1):
                            break

                    while True:
                        card_i3 = randint(0, len(ai_card_Remain_list[i]) - 1)
                        if (card_i3 != card_i1 and card_i3 != card_i2):
                            break

                    ai_card_on_deck = []

                    ai_card_on_deck.append(ai_card_Remain_list[i][card_i1])
                    ai_card_on_deck.append(ai_card_Remain_list[i][card_i2])
                    ai_card_on_deck.append(ai_card_Remain_list[i][card_i3])

                    stat = str(AIList_list[i][0]) + ',' + str(AIList_list[i][1]) + ',' + str(AIList_list[i][2]) + ',' + str(AIList_list[i][3])

                    if AIList_list[i][0] <= 0:
                        endGameAI(tuples[0])

                    if AIList_list[i][2] <= 0:
                        endGameAI(tuples[0])

                    ai_card_chosen = int(output_function(int(tuples[2]), cards_Remain_list[i], stat, ai_card_on_deck, i)) #trigger AI in string (should in int???)

                    ai_card_Remain_list[i].remove(ai_card_chosen) # update the card_remain array

                    tuples[2] = str(randint(0,2)) #update roundbuff

                    ai_used = 0
                    # this can be more complicated, consider later
                    if tuples[3] == 4:
                        if AIList_list[i][3] <= 6:
                            ai_used = 0
                        elif randint(0,10) >= 7:
                            ai_used = 1
                        else:
                            ai_used = 0
                    elif tuples[3] != 0:
                        if randint(0,10) >= 4:
                            ai_used = 0
                        else:
                            ai_used = 1 #used the ult

                    tuples[0].send(f'{str(tuples[3])} {str(ai_used)} {str(ai_card_chosen)}'.encode('ascii')) #AI send information back
                    tuples[3] = 0 # changed after it is sent to the client? Important!
                    tuples[0].send(f'{str(tuples[2])}'.encode('ascii')) #update roundbuff
                    tuples[1] += 1
                    #Check round limit
                    if tuples[1] == MAXROUNDS:
                        endGameAI(tuples[0])
                    break
    except:
        print("Exception in chatAI method")

#changed
def endGameAI(client1):
    print("Rounds limit reached, closing room and clients")
    client1.close()
    return 0

#changed
def output_function(roundbuff, left_cards, stat, card_on_deck, index): #stat in string

    # read current status
    # suppose the file name is read_me.txt, it is kept overwrote
    # type is string

    #user_action = open(".\read_me.txt", "r")[0].strip() #only has one line

    #remain_card = open(".\read_me_remain.txt", "r")[0].strip() #only has one line

    result = 's' #initialize

    #2,[0,1,3,4,5,7,8,9,10,11,12],26,3,8,0

    #here leftcards
    user_action = str(roundbuff) + ',' + str(left_cards).replace(' ', '') + ',' + stat

    learning_list[index].append(user_action)

    for i, line in enumerate(cleaned_data):
        if line == user_action:
            if cleaned_data_result[i].split(',')[0] in card_on_deck:
                result = str(cleaned_data_result[i])
                break

    # other case... using threshold

    player_score = 0
    ai_score = 0

    if result == 's':
        user_input = stat.split(',') #okay we only wants last 4 and first 1
        user_input = user_input[0:1] + user_input[-4:]
        player_score = int(user_input[1]) + int(user_input[2]) * 0.6
        ai_score = int(user_input[3]) + int(user_input[4]) * 0.8

        if roundbuff == 2:
            player_score = player_score * 0.6
        elif roundbuff == 1:
            player_score = player_score * 1.25

        attack_card = []
        defense_card = []

        for item in card_on_deck:
            if item <= 6:
                attack_card.append(item)
                if ((item + 1) * 2 >= (int(user_input[3]) + int(user_input[4])) and roundbuff == 2) or (roundbuff != 2 and (item + 1) >= (int(user_input[3]) + int(user_input[4]))):
                    result = str(item)
                    break
            else:
                defense_card.append(item)

        attack_card.sort(reverse = True)
        defense_card.sort(reverse = True)

        if result == 's':
            if (len(attack_card) == 0 and len(defense_card) != 0) or user_input[0] == 1:
                #result = str(defense_card[0]) + ',1'
                result = str(defense_card[0])

            elif len(defense_card) == 0 or user_input[0] == 2:
                #result = str(attack_card[0]) + ',0'
                result = str(attack_card[0])

            elif ai_score > player_score:
                # we attack
                result = str(attack_card[0])

            else:
                result = str(defense_card[0])

    learning_list_result[index].append(result)

    return result

#changed also may need to edit the path
cleaned_data_result_onread = open("../AI/Generating_Database/cleaned_data_result.txt", "r")
cleaned_data_result = []
for i, line in enumerate(cleaned_data_result_onread):
    cleaned_data_result.append(line.strip())

cleaned_data_onread = open("../AI/Generating_Database/cleaned_data.txt", "r")
cleaned_data = []
for i, line in enumerate(cleaned_data_onread):
    cleaned_data.append(line.strip())

# Run the server
receive()