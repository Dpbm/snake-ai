#include <cstddef>
#include <cstdint>
#include "board.h"
#include "../helpers/utils.h"
#include "./players/player.h"

using std::size_t;
using Utils::random_int;
using Players::Player;
using Players::Node;

namespace Game {
  Board::Board(uint8_t w, uint8_t h){
    this->w = w;
    this->h = h;
    this->board = new uint8_t*[h];

    for(size_t i = 0; i < h; i++)
      this->board[i] = new uint8_t[w];
    
    this->random_food();
  }

  void Board::random_food(){
    this->food.x = random_int(0, h-1);
    this->food.y = random_int(0, w-1);
  }

  void Board::clear_board(){
    for(size_t i = 0; i < h; i++)
      for(size_t j = 0; j < w; j++)
        this->board[i][j] = 0;
  }

  uint8_t** Board::get_board(){
    this->clear_board();
    this->update_player_pos();
    this->board[this->food.x][this->food.y] = 2;
    return this->board;
  }

  void Board::add_player(Player* player){
    this->player = player; 
  }

  void Board::update_player_pos(){
    this->player->update_pos();
    this->check_border_collision();
    this->player->head_tail_collision();
    if(this->player->is_dead())
      return;
 
    if(this->food.x == this->player->get_x() && this->food.y == this->player->get_y()){
      this->player->update_score();
      this->random_food();
    }

    Node* part = this->player->get_player();
    while(part != nullptr){
      this->board[part->value.x][part->value.y] = 1;
      part = part->next;
    }
  }

  void Board::check_border_collision(){
    int16_t px = this->player->get_x();
    int16_t py = this->player->get_y();

    if(px < 0 || px >= this->h || py < 0 || py >= this->w)
      this->player->set_died();
  }
 
  Board::~Board(){
    for(size_t i = 0; i < this->h; i++)
      delete[] this->board[i];
    delete[] this->board;
  }
}
