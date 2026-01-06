# DISCUSSION QUESTIONS
1. What types of game entities could you create with aggregation?
2. Do friend functions undermine encapsulation in OOP?
3. What advantages does dynamic memory offer to game programs?
4. Why are memory leaks difficult errors to track down?
5. Should objects that allocate memory on the heap always be required to
free it?
---
### My Answers
1. A car: you could have a Car object/class that is composed of body, engine, handling, exhaust classes/objects. Organizing it in this way would allow you to more easily manage and extend code for upgrades (e.g. the player upgrading the engine of the car they're racing). A party-based RPG game's party managment is a form of aggregation. The class you'd write for the player's health, experience points, and inventory would also be used for the other party members. Then you could compose party-characteristics (e.g. the total experience points in the party as a whole) to influence interactions in the world.
2. I'm unsure. I think they don't if they are not returning private data members. However, by virtue of their unlimited access they can undermine encapsulation by exposing private data members one class to another.
3. You can make copies of objects that have unique memory address locations. You can make your program more efficient by reserving the amount of memory required ahead of time instead of having the program need to expand its reserves during its execution. Dynamic memory allocation allows for more flexible resource management for the lifetime of a program where the requirements can change from state to state -- especially in a game where the number of objects can greatly vary.
4. Memory leak errors are difficult to track down because by definition the address that is "leaked" is cut-off from the program and functionally invisible. Also, the memory leak might gradually decrease performance at fist and so be hard to detect until a later point in a program's execution.
5. Almost always. It is common and good practice to write a 'delete' for every 'new'. This will not only help prevent memory leak errors but also helps structure the life cycle of an object in the program.