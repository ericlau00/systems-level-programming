# guess whom'st've

## by Eric Lau, Kazi Jamal, Matthew Chan (Period 5)

## Project Description

Our project is a twist on the class tabletop game by Hasbro: Guess Who. Instead of trying to guess fictional characters based on their appearance, players must guess Stuyvesant High School faculty or notable students by asking questions based on their prior knowledge of the school community. Two players will each be shown the instructions and then given a randomly selected character. The gameplay will consist of the two players going back and forth asking questions, analyzing answers to "flip down characters" (eliminate their possibility of being the opponents character), and, finally guessing the opponent's character.

## User Interface

1. Players will be shown instructions on how to play the game.
2. Players will be given a randomly selected character.
3. Players will be shown the main interface which will appear as shown below:
![Image of Game Interface](/examples/example_game.png)
4. Based on the state of the game, the player will be able to ask a question, answer a question, or act upon an opponent's answer to flip down their characters.
5. Player 1 Question --> Player 2 Answer --> Player 1 Flips Down Characters --> Player 2 Question --> Player 1 Answer --> Player 2 Flips Down Characters  --> repeat
6. **Question:** Player will be prompted to enter a question ending in a question mark. They can also enter "guess" and they will be prompted to choose the ID of the character they believe is the opponent's character.
7. **Answer:** Player will be shown opponent's question and then prompted to answer the question.
8. **Flip down character:** Player will be prompted to enter characters' IDs to flip down, and then enter "done" when they do not wish to flip down any more characters.
9. Once a player's character has been correctly guessed, the game will show a winning or losing message to players, and end the game.

## Technical Design

### Topics

#### Networking

We will use a server to send questions, answers, and guesses between two players (clients).

At the beginning of the game, we will also use the server to send the list of random names to the players.

#### Processes

We will use processes to fork the host terminal to be able to act both as the server and a client (player).

#### Working with files

We will be working with a file to access the names of teachers.

#### Allocating memory

### Data Structures

We will use an array to store the randomized names selected from the file.

We will use a struct to contain a resposne that is sent over the network which includes the following information:

- type - whether the response is a question or answer
- response - the actual message sent

### Algorithms

We will use a randomization algorithm to pick 16 random names from a file.

## Timeline

- Jan 6
  - Implement algorithm to generate random names
- Jan 8
- Jan 10
- Jan 12
- Jan 14
- Jan 16
  - Debugging and testing! (everybody)
