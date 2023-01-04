#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// A simple class to represent a player in the game.
class Player {
 public:
  std::string name;
  int score;

  // Overload the < operator to allow players to be sorted based on their scores.
  bool operator<(const Player& other) const {
    return score > other.score;
  }
};

// A class to represent the leaderboard of the game.
class Leaderboard {
 private:
  // Use a vector to store the players on the leaderboard.
  std::vector<Player> players;
  // Use an unordered map to store the indices of the players in the vector.
  std::unordered_map<std::string, int> player_indices;

 public:
  // Add a new player to the leaderboard.
  void AddPlayer(const Player& player) {
    // Check if the player is already on the leaderboard.
    auto it = player_indices.find(player.name);
    if (it == player_indices.end()) {
      // If the player is not on the leaderboard, add them to the end of the vector.
      players.push_back(player);
      // Store the index of the player in the map.
      player_indices[player.name] = players.size() - 1;
    } else {
      // If the player is already on the leaderboard, update their score.
      players[it->second].score = player.score;
    }
  }

  // Remove a player from the leaderboard.
  void RemovePlayer(const std::string& name) {
    // Check if the player is on the leaderboard.
    auto it = player_indices.find(name);
    if (it != player_indices.end()) {
      // Remove the player from the vector.
      players.erase(players.begin() + it->second);
      // Remove the index of the player from the map.
      player_indices.erase(it);
      // Update the indices of the players in the map.
      for (auto& [name, index] : player_indices) {
        if (index > it->second) {
          index--;
        }
      }
    }
  }

  // Get the top N players on the leaderboard.
  std::vector<Player> GetTopPlayers(int n) {
    // Sort the players in descending order by score.
    std::sort(players.begin(), players.end());
    // Return the top N players.
    return std::vector<Player>(players.begin(), players.begin() + n);
  }
};

int main() {
  Leaderboard leaderboard;
  leaderboard.AddPlayer({"Alice", 100});
  leaderboard.AddPlayer({"Bob", 90});
  leaderboard.AddPlayer({"Charlie", 80});
  leaderboard.AddPlayer({"Dave", 70});
  leaderboard.AddPlayer({"Eve", 60});

  // Remove a player from the leaderboard.
  leaderboard.RemovePlayer("
  // Get the top 3 players on the leaderboard.
  auto top_players = leaderboard.GetTopPlayers(3);
  std::cout << "Top 3 players:" << std::endl;
  for (const auto& player : top_players) {
    std::cout << player.name << ": " << player.score << std::endl;
  }

  return 0;
}
