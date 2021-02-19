#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_

#include <vector>
#include "board.h"
#include "button.h"
#include "deck.h"
#include "player.h"

class Game {
public:
    std::vector<Player> players;
    Deck deck;
    Board board;
    enum Phase { None, Start_developing, Developing, Start_feeding, Feeding, Death };
    Phase cur_phase = None;

    sf::Font font;
    sf::RenderWindow game_window;
    sf::RectangleShape deck_shape;
    sf::Text deck_text;
    std::vector<Button> player_cards_buttons;
    std::vector<Text_Button> player_animals_shapes;
    int selected_card = -1;
    Button place_for_new_animal;
    Text_Button end_turn;

    void make_deck_shape();
    void run_game();
    void prepare_game();
    void draw_game_window();
    void shuffle_players(int quantity);
    void start_developing_phase();
    void start_feeding_phase();
    void death_phase();
    void handle_event(sf::Event event);
    void add_cards_buttons();
    void set_cards_position();
    void add_animal_shape();
    void set_animals_position(bool with_new_place);
    void delete_animal_shape();
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_
