#include <stdint.h>
#include <stdio.h>
typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

const char *names[] = { "Dude", "Walter", "Maude", "Big Lebowski", "Brandt",
  "Bunny", "Karl", "Kieffer", "Franz", "Smokey" };

//
// Returns the position of the player to the left.
//
// pos: The position of the current player.
// players: the number of players in the game.
//
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

//
// Returns the position of the player to the right.
//
// pos:the position of the current player.
// players: number of players in the game.
//
uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}

uint32_t players;
uint32_t pos = 0;
uint32_t bank = 0;

void win(uint32_t money[]);
uint32_t test_end(uint32_t money[], uint32_t players);
int main(void);
uint32_t right(uint32_t, uint32_t);
uint32_t left(uint32_t, uint32_t);
uint32_t how_many_dice(uint32_t);
void direction(uint32_t, uint32_t player[]);
void srand(uint32_t);
uint32_t rand(void);
uint32_t ran_num(void);

// Main Function
int main(void) {
  uint32_t ran;
  uint32_t temp1;
  uint32_t temp2;
  printf("Random seed: ");
  scanf("%d", &ran);
  srand(ran);
  printf("How many players? ");
  scanf("%d", &temp1);
  players = temp1;
  uint32_t money[players];
  temp2 = 0;
  for (uint32_t i = 0; i < players; i++) {
    money[i] = 3;
  }
  for (uint32_t i = 0; test_end(money, players) != 0; i = right(i, players)) {
    if (money[i] != 0) {
      printf("%s", names[i]);
      printf(" rolls...");
      temp2 = 0;
    } else {
      temp2 = 1;
    }
    for (uint32_t z = how_many_dice(money[pos]); z != 0; z--) {
      uint32_t x = ran_num();
      direction(x, money);
    }
    if (temp2 == 0) {
      printf("\n");
    }
    pos = right(pos, players);
  }
  win(money);
  return 0;
}

// Prints out what direction the money is flowing
void direction(uint32_t x, uint32_t money[]) {
  if (x == LEFT) {
    printf(" gives $1 to ");
    printf("%s", names[left(pos, players)]);
    money[pos]--;
    money[left(pos, players)]++;
  }
  if (x == RIGHT) {
    printf(" gives $1 to ");
    printf("%s", names[right(pos, players)]);
    money[pos]--;
    money[right(pos, players)]++;
  }
  if (x == CENTER) {
    printf(" puts $1 in the pot");
    money[pos]--;
    bank++;
  } else if (x > CENTER) {
    printf(" gets a pass");
  }
  return;
}

// Calculates how many dice are used
uint32_t how_many_dice(uint32_t x) {
  if (x == 1) {
    return 1;
  } else if (x == 2) {
    return 2;
  } else if (x >= 3) {
    return 3;
  } else {
    return 0;
  }
}

// Tests to see if it is the end of the game
uint32_t test_end(uint32_t money[], uint32_t x) {
  uint32_t end = 0;
  for (uint32_t i = 0; i < x; i++) {
    if (money[i] != 0) {
      end++;
    }
  }
  if (end <= 1) {
    return 0;
  } else {
    return 1;
  }
}

// Generates random numbers between 0-5
uint32_t ran_num(void) {
  uint32_t y = (rand() % 6);
  return y;
}

// Prints out who wone, how much they had left in thier hand, and how much was in the pot
void win(uint32_t money[]) {
  for (uint32_t i = 0; i < players; i++) {
    if (money[i] >= 1) {
      printf("%s", names[i]);
      printf(" wins the $");
      printf("%d", bank);
      printf(" pot with $");
      printf("%d", money[i]);
      printf(" left in the bank!\n");
    }
  }
  return;
}
