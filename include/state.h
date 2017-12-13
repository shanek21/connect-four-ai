#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_


#include <bitset>
#include <list>
#include <string>


class State {
 public:
  static const int WIDTH = 7;
  static const int HEIGHT = 6;

  typedef std::bitset<(WIDTH + 1) * HEIGHT> TileBoard;
  enum TileType { Red, Black, Empty };

  /**
   * Default constructor
   */
  State();

  /**
   * Copy constructor
   * @param s - pointer to State to copy
   */
  explicit State(const State* s);

  bool isRedTile(int row, int col) const;

  bool isBlackTile(int row, int col) const;

  TileType getTile(int row, int col) const;

  bool isEmpty(int row, int col) const;

  TileBoard getRedBoard() const;

  TileBoard getBlackBoard() const;

  uint64_t boardKey() const;

  TileBoard getNextToMoveBoard() const;

  int getBoardSize() const;

  State play(int col) const;

  /**
   * @param tile - tile type to play
   * @param col - the column to play the tile in
   * @returns a new State object with the play made
   */
  State play(TileType tile, int col) const;

  bool isPlayable(int col) const;

  TileType getMostRecentMoveColor() const;

  std::list<int> getWinningMoves(TileType color) const;

  bool isWinningPlay(TileType color, int col) const;

  int getNumMoves() const;

  /**
   * @returns true if WIDTH * HEIGHT moves have been made
   */
  bool isBoardFull() const;


  /**
  * @returns the color of the next tile to be played
  */
  TileType getNextTileColor() const;

  static State boardFromNums(std::string nums);

 protected:
  TileBoard redBoard;
  TileBoard blackBoard;

  int numMoves;

  void incrementNumMoves();

  void placeTile(TileType color, int row, int col);
};

std::ostream& operator<<(std::ostream& os, const State::TileType& t);


#endif  // INCLUDE_STATE_H_
