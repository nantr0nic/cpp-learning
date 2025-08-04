#include <print>

#include "Meat.h";

int main()
{
	Game game;
	Player player;

	std::println("Welcome to the Game!");
	std::println("You spawn into a random abyss with a weapon and some health.");
	std::println("Here's what you randomly showed up with:");
	game.print_player_stats(player);

	std::println("Oh shit, a few random fighters and archers showed up (of course).");
	game.start_game();
	game.print_total_enemies();

	return 0;
}
