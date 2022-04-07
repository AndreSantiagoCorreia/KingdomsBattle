# Multiplayer Card Game: Kingdoms Battle
## L2C_Team39 Members
- Andre Santiago Correia
- Cassiel Jung
- Nick Zhang
- Mike He

## Project Topic
Developing real-time multiplayer card game using *cloud, user interface, hardware, AI* that supports multiplayer mode between two people and single-player mode between a person and AI.

## Project Goal
Since our final product is a video game, the game should meet following goals:
- ease of use; intuitive game rules
- accessibility; users should be able to access the game everywhere through internet
- innovative and strategic game logic: game should be interesting to play and not similar to pre-existing games
- fast-paced: if game is taking for a long time user would lose their concentration

## Contribution
### Hardware_Nick
- Designed and implemented game UI
- Developed VGA video output driver in verilog
    - Fully hardware-accelrated graphics
    - Textures stored in on-chip memory
- Developed PS2 Keyboard input driver
### Cloud_Andre
- Developed a back-end server in Python
    - Handles multiple client connections
    - Create separate rooms for multiplayer and singlplayer modes
- Developed client code in Python and converted to C
    - Sends/Receives message
    - the game runs here
### Game_Cassiel
- Implemented game logic in C
- Merge game logic with client code
    - run the code on linux
    - synchronize two player's screen when running multiplayer mode
- Merge game code with VGA and Keyboard drivers
### AI_Mike
- Implemented first draft of game logic with Cassiel
    - Construct dataset by simulating above code 10,000 to 50,000 times
- Implemented AI logic which use dataset as a lookup table to determine the next move
    - Checked conditions when the dataset does not support the situation
- Merge the game and the AI to both client and server component
- AI has winning probability of 60% roughly

## Acknowledgement
HPS-to-FPGA and PIO IP cores was obtained from Altera website. Other than that, every code was written by team members.
