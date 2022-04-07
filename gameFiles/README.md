c-client.c:
Client code to connect to server (echo-server.py in cloud directory), has all the game logic merged into it. It first connects to our running server and then starts looping the game in "func()" which does all the computation required so that each client connected know the game state they are currently in.

.h files:
These files include every extension we need to run the game, such as HP computation etc. and the vga decoding so that hardware can read and display the game correctly.

Description.txt files:
These files have useful information about the game, basically the creative part of it.