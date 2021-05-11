Main Function:
  Where all function calls are called from
ran_num:
  generates a random number
how_many_dice:
  determines how many times the random numbers are generated
direction:
  prints who is giving whom money
right:
  returns position of player to the right of current player
left:
  returns position of player to the left of current player
test_end:
  tests to see if there is only one player left with money.  ends game if this is true
win:
  prints who won and how miuch they won


First loop starts that goes as many times as how_many_dice tells it to.  It generates the correct number of random numbers, which is then passed to direction, which evaluates the numbers and prints out where the money went, as well as allocate the money around.  It then runs test_end to see if the program should end.  Continues until test_end is true, then runs win, which prints out the result of the game.
