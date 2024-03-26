In order to start the program you should run inside the command window "./game game_name number".
The game_name can be "dice" or "hangman". The third variable is optional and should be used only if the "hangman" is the first argument.
The third variable must be a number between 5 and 12.

1. Dice game

A number between 1 and 100 will be generated and the user must guess the number.
Each answear will cost a life. After each guess the interval will get smaller.
Letters or characters are not allowed the game will stop.
Only integers are allowed.

2. Hangman

A word with x letters will be randomly selected from the files. X represents the number given in the command window and if no number selected than will be generated automaticaly.
The user have 6 tries to guess. Each wrong guess will cost 1 try, each right guess will be completed.
If the user imput a letter twice will cost 1 try.