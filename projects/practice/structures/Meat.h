#include <print>
#include <vector>
#include <random>

class Game
{
public:
	Game() : rTools{} {};

	void start_game()
	{
		int initial_enemies = Random.rAny(1, 5);
		for (const auto& e : initial_enemies) {
			if (Random.r20() < 10) {
				enemies.push_back(Fighter());
				++fighter_count;
			}
			else {
				enemies.push_back(Archer());
				++archer_count;
			}
		}
	}

	void next_turn()
	{
		for (auto& enemy : enemies) {
			enemy.move();
			if (enemy.in_range) {
				enemy.attack();
			}
		}
	};

	void print_player_stats(const Player& player)
	{
		std::println("Player Stats:");
		std::println("Health: {}", player.health);
		std::println("Weapon: {}", player.weapon == 's' ? "Sword" : "Bow");
		std::println("Damage: {}-{}", player.damage_min, player.damage_max);
		std::println("Range: {}", player.range);
	}

	void print_total_enemies()
	{
		std::println("There are currently {} fighters and {} archers in front of you.", fighter_count, archer_count);
	}

	class Random
	{
	public:
		Random()
		{
			std::random_device rd;
			gen = std::mt19937(rd());
		}

		std::mt19937& getGenerator() { return gen; }

		int r20();
		int rAny(const int low, const int high);

	private:
		std::mt19937 gen;
	};

private:
	Random rTools;
	std::vector<Enemies> enemies;
	int archer_count = 0;
	int fighter_count = 0;
};

class Player
{
public:
	Player() : health{ 100 }, damage{ 10 }, range{ 1 }, highSpeed{ false } {};
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	virtual ~Player() = default;

public:
	void attack(const Enemies& enemy) {
		if (!enemy.in_range) {
			std::println("Enemy is out of range!");
			return;
		}
		int roll = Game::Random.r20();
		if (roll < 10) {
			std::println("Missed!");
		}
		else {
			int atk_dmg = Game::Random.rAny(damage_min, damage_max);
			enemy.health -= atk_dmg;
			std::println("Hit! Damage dealt: {}", atk_dmg);
		}
	}

	void heal() {
		if (health < 100) {
			health += 10;
			std::println("Healed 10 health points. Current health: {}", health);
		}
		if (health = 100) {
			std::println("Health is already full!");
		}
	}

	void switchWeapon() {
		if (weapon == 's') {
			weapon = 'b';
			damage_min = 1;
			damage_max = 5;
			range = 50;
			high_speed = true;
			std::println("Switched to Bow. Range: {}, Damage: {}-{}, High Speed: {}", range, damage_min, damage_max, high_speed);
		}
		else {
			weapon = 's';
			damage_min = 5;
			damage_max = 10;
			range = 5;
			high_speed = false;
			std::println("Switched to Sword. Range: {}, Damage: {}-{}, High Speed: {}", range, damage_min, damage_max, high_speed);
		}
	}

private:
	int health = 100;
	int damage_min = 5;
	int damage_max = 10;
	int range = 5;
	bool high_speed = false;

	char weapon = 'b'; // s = sword, b = bow
};

// Fighter and Archer classes

// Fighter = melee range, strong armor (sub 2-5 from dmg), low speed (every turn), high damage (5-10)
// Archer = longer range, weak armor (sub 0-2 from dmg), high speed (every other turn), low damage (1-5)

class Enemies
{
public:
	virtual Enemies() = 0;
	virtual Enemies& (const Enemies& other) = 0;
	virtual Enemies& operator=(const Enemies& other) = 0;
	virtual ~Enemies() = default;

public:
	virtual void attack() {
		if (in_range) {
			int roll = Game::Random.r20();
			if (roll < 10) {
				std::println("Missed!");
			}
			else {
				int atk_dmg = Game::Random.rAny(damage_min, damage_max);
				Player.health -= atk_dmg;
				std::println("Hit! Damage dealt: {}", atk_dmg);
			}
		}
	}

	virtual void move() = 0;

private:
	int health = 100;
	int damage_min = 1;
	int damage_max = 5;
	int range = 5;
	bool high_speed = false;

	bool in_range = false;

	int distance_to_player = 75;
};

class Fighter : public Enemies
{
public:
	Fighter() : Enemies(), health{ 100 }, damage_min{ 5 }, damage_max{ 10 }, range{ 5 }, high_speed{ false } {};
	Fighter(const Fighter& other) = default;
	Fighter& operator=(const Fighter& other) = default;
	~Fighter() override = default;

public:
	void move() override {
		if (distance_to_player > range) {
			distance_to_player -= 5;
		}
		else {
			in_range = true; 
		}
	}
};

class Archer : public Enemies
{
public:
	Archer() : Enemies(), health{ 100 }, damage_min{ 1 }, damage_max{ 5 }, range{ 50 }, high_speed{ true } {};
	Archer(const Archer& other) = default;
	Archer& operator=(const Archer& other) = default;
	~Archer() override = default;

public:
	void move() override {
		if (distance_to_player > range) {
			distance_to_player -= 7;
		}
		else {
			in_range = true; 
		}
	}
};