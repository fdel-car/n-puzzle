#pragma once

#ifndef NDEBUG
#define NDEBUG
#endif

#include <assert.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <list>
#include <locale>
#include <queue>
#include <unordered_set>
#include "Node.hpp"

struct FrenchFacet : std::numpunct<char> {
  char do_thousands_sep() const { return ' '; }     // Separate with spaces
  std::string do_grouping() const { return "\3"; }  // Groups of 3 digits
  char do_decimal_point() const { return ','; }     // Separate with comma
};

class Puzzle {
 public:
  Puzzle(const std::vector<u_char> &startGrid);
  virtual ~Puzzle(void);

  enum Algorithm { AStar, Greedy, UniformCost };
  const std::vector<u_char> finalGrid;

  static int N;
  static int totalSize;
  static int nbrLength;
  static std::unordered_map<char, Algorithm> algoMap;
  static Algorithm currAlgorithm;

  int Solve(void);

  static bool updateGoalPattern(char flag);
  // void setAlgorithm(char flag);

 private:
  enum GoalPattern { Snail, Classic };
  size_t _moveCount = 0;
  size_t _timeComplexity = 0;
  size_t _sizeComplexity = 0;
  std::priority_queue<Node *, std::vector<Node *>, NodePtrGtrThan> _openedSet;
  std::unordered_map<std::string, Node *> _lookupTable;
  std::unordered_map<std::string, std::vector<u_char>> _closedSet;
  std::chrono::system_clock::time_point _start;
  std::chrono::system_clock::time_point _end;
  std::string _dataOutput = std::string();

  static const std::array<int, 4> _rowOffset;
  static const std::array<int, 4> _colOffset;
  static std::unordered_map<char, GoalPattern> _goalMap;
  static GoalPattern _goalPattern;

  Puzzle(void);
  Puzzle(Puzzle const &src);

  static std::unordered_map<char, GoalPattern> _getGoalMap(void);
  static std::unordered_map<char, Algorithm> _getAlgoMap(void);

  const std::vector<u_char> _initFinalGrid(void) const;
  void _writeToFile(void) const;
  void _printPath(const std::vector<u_char> &tiles);
  void _printPath(const Node *node);
  bool _isSwapSafe(const std::array<int, 2> &emptyTileCoords,
                   const std::array<int, 2> &emptyTileSwapDir) const;
  int _inversionCount(const std::vector<u_char> &tiles) const;
  bool _isSolvable(const std::vector<u_char> &startGrid) const;

  Puzzle &operator=(Puzzle const &rhs);
};
