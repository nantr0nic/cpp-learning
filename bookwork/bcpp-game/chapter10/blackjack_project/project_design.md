# Beginning C++ Through Game Programming (4th ed.)
### Chapter 10 Project: Blackjack
This author does a good job of demonstrating pre-planning practices before starting a (relatively) larger coding project. I'm reproducing portions of this pre-planning exercise for posterity, as well as for future reference when planning my own projects. This is from all from the book.
---
```
Before you start coding a project with multiple classes, it is helpful to map them out on paper.
You might make a list and include a brief description of each class. [This table] shows my first
pass at such a list for the Blackjack game.
```

|**Class**       |**Base Class**|**Description**|
|:--------------|:-------------:|:----------------------------|
|Card           |None           |A Blackjack Playing card.    |
|Hand           |None           |A Blackjack hand. A collection of **Card** objects.|
|Deck           |*Hand*         |A Blackjack deck. Has extra functionality that **Hand** doesn't, such as shuffling and dealing.|
|GenericPlayer  |*Hand*         |Generic Blackjack Player. Not full, but common elements of a human/computer player.|
|Player         |*GenericPlayer*|A human Blackjack player.|
|House          |*GenericPlayer*|The computer player (the house).|
|Game           |None           |A Blackjack game.            |
---
Here is an instructive suggestion:
```md
I see Card objects as real-life cards. You don’t copy a card when you deal it
from the deck to a hand; you move it. For me, that means **Hand** will have a
**data member that is a vector of pointers to Card objects**, which will exist on
the heap. When a card moves from one Hand to another, it’s really pointers
that are being copied and destroyed.
```
```
To really flesh things out, you can list the data members and member
functions that you think the classes will have, along with a brief description of
each. That’s what I do [in the next tables]. For each class, I list
only the members I define in it. Several classes will, of course, be inherited
members from base classes.
```
---
### Card Class
|**Member**     |**Description**            |
|:--------------|:--------------------------|
|rank m_Rank    |Rank of the card. *rank* is an enumeration for all 13 ranks.|
|suit m_Suit    |Suit of the card. *suit* is an enumeration for the four possible suits.|
|bool m_IsFaceUp|Indicated whether the card is face up. Affects how card is displayed/valued.|
|int GetValue() |Returns the value of the card.|
|void Flip()    |Flips a card. Face up -> face down, down -> up.|
---
### Hand Class
|**Member**     |**Description**            |
|:--------------|:--------------------------|
|vector<Card*>m_Cards|Collection of cards. Stores pointers to *Card* objects.|
|void Add(Card* pCard)|Adds a card to the hand. Adds a pointer to *Card* to the vector *m_Cards*.|
|void Clear()   |Clears all cards from the hand. Removes all pointers in the vector *m_Cards*, deleting all associated *Card* objects on the heap.|
|int GetTotal() const|Returns the total value of the hand.|
---
I'm a little too lazy to reproduce all of the tables from the book; however, the preceding two examples demonstrate the degree to which the author brainstorms the class members.
---
## Planning the Game Logic.
### (Pseudocode)
---
```
The last part of my planning is to map out the basic flow of one round of the
game. I wrote some pseudocode for the Game class’ Play() member function.
Here’s what I came up with:
```
```md
Deal players and the house two initial cards
Hide the house’s first card
Display players’ and house’s hands
Deal additional cards to players
Reveal house’s first card
Deal additional cards to house
If house is busted
    Everyone who is not busted wins
Otherwise
    For each player
        If player isn’t busted
            If player’s total is greater than the house’s total
                Player wins
            Otherwise if player’s total is less than house’s total
                Player loses
            Otherwise
                Player pushes
Remove everyone’s cards
```
```
At this point, you know a lot about the Blackjack program and you haven’t
even seen a single line of code yet! But that’s a good thing. Planning can be as
important as coding (if not more so).
```
