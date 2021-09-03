#ifndef EVOLUTION_PROJECT_WINDOW_H_
#define EVOLUTION_PROJECT_WINDOW_H_
#include <SFML/Graphics.hpp>
#include <cmrc/cmrc.hpp>
#include "button.h"
#include "constants.h"
#include "game.h"
#include "settings.h"
#include "text_field.h"
CMRC_DECLARE(resources);

class Window {
public:
    virtual std::unique_ptr<Window> handle_events() = 0;
    virtual ~Window() = default;

protected:
    sf::Font font;
    sf::RenderWindow window;
    virtual void draw() = 0;
};

class StartWindow : public Window {
public:
    StartWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~StartWindow() override = default;

private:
    TextButton start_local_game_button;
    TextButton start_online_game_button;

    void init_window();
    void draw() override;
};

class GameWindow : public Window {
public:
    //<<<<<<< HEAD
    GameWindow(Game &&game_) : game(std::move(game_)) {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game_window",
                      //=======
                      //    GameWindow(Settings settings) {
                      //        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game",
                      //>>>>>>> origin/master
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        game.start_game();
        //        game.start_game(
        //            settings);  //важен порядок этих двух строчек, потом возможно надо будет
        //            исправить
        init_window();
    }
    GameWindow(Settings settings) {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        file = fs.open("card.png");
        std::string str1 = std::string(file.begin(), file.end());
        card_texture.loadFromMemory(str1.data(), str1.size());
        card_texture.setSmooth(true);
        sprite.setTexture(card_texture);
        sprite.setScale(CARD_WIDTH / sprite.getGlobalBounds().width,
                        CARD_HEIGHT / sprite.getGlobalBounds().height);
        game.start_game(settings);
        init_window();
    }
    ~GameWindow() override = default;

    std::unique_ptr<Window> handle_events() override;
    void recalc_cards();
    void set_cards_position();
    void init_window();
    void make_deck_shape();
    void add_animal_shape(const std::shared_ptr<Animal> &new_animal, int id);
    void set_animals_position();
    void set_players_names_positions();
    void recalc_animals();
    sf::RenderWindow &get_window();
    std::shared_ptr<Card> get_clicked_card();
    void click_card(const std::shared_ptr<Card> &card);
    bool check_new_animal();
    std::shared_ptr<Card> play_animal(const std::shared_ptr<Animal> &shared_ptr);
    bool check_end_turn();
    bool check_log_button();
    std::shared_ptr<Animal> check_animals();
    void add_property_to_animal(const std::shared_ptr<Animal> &new_animal);
    std::shared_ptr<Card> const &get_selected_card() const;
    bool const &get_food_clicked() const;

    void make_food();
    bool check_food();
    void click_food();
    void feed_animal(const std::shared_ptr<Animal> &animal);

    std::shared_ptr<AnimalButton> get_clicked_property_animal();
    void show_properties(std::shared_ptr<AnimalButton> animal_button, bool phase);
    void use_property(std::shared_ptr<AnimalButton>, Properties prop);

    void show_actions();

    void change_player();

private:
    void draw() override;
    Game game;
    sf::Font font;
    sf::Texture card_texture;
    sf::Sprite sprite;

    TextButton end_turn;
    TextButton log_button;
    sf::RectangleShape deck_shape;
    sf::Text deck_text;
    sf::Text turn_of;
    sf::Text instruction;
    TextButton play_animal_button;
    TextButton feed_animal_button;
    std::vector<CardButton> player_cards_buttons;
    std::vector<std::vector<AnimalButton>> player_animals_buttons;
    std::shared_ptr<Card> selected_card = nullptr;
    TextButton food;
    bool food_clicked = false;
    std::vector<sf::Text> players_names;
};

class PropertyWindow : Window {
public:
    PropertyWindow(bool able_to_use_) : able_to_use(able_to_use_) {
        window.create(sf::VideoMode(200, 300), "Properties",
                      sf::Style::Titlebar | sf::Style::Close);
        window.setPosition({200, 200});
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
    }

    std::unique_ptr<Window> handle_events() override;
    Properties handle_properties();
    void init_window(std::shared_ptr<AnimalButton> animal_button);

    ~PropertyWindow() override = default;

private:
    bool able_to_use;
    std::vector<PropertyButton> properties;
    void draw() override;
};

class StartChoiceWindow : public Window {
public:
    StartChoiceWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Choose your own destiny",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~StartChoiceWindow() override = default;

private:
    TextButton join_game_button;
    TextButton make_game_button;

    void init_window();
    void draw() override;
};

class JoinGameWindow : public Window {
public:
    JoinGameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Join online game",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        wait_text = sf::Text("", font);
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~JoinGameWindow() override = default;

private:
    sf::Text wait_text;
    TextField room_field;
    TextField name_field;
    TextButton join_button;

    void init_window();
    void draw() override;
};

class MakeGameWindow : public Window {
public:
    MakeGameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Make online game",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        room_id = sf::Text("", font);
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~MakeGameWindow() override = default;

private:
    sf::Text room_id;
    TextField room_field;
    TextField name_field;
    TextField number_of_cards_field;
    TextField number_of_players_field;
    TextField seconds_for_turn_field;
    TextField number_of_bots_field;
    TextButton start_button;
    Settings settings;

    void init_window();
    void draw() override;
};

class StartLocalGameWindow : public Window {
public:
    StartLocalGameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start local game",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~StartLocalGameWindow() override = default;

private:
    TextField number_of_cards_field;
    TextField number_of_players_field;
    TextField number_of_bots_field;
    TextField seconds_for_turn_field;
    std::size_t number_of_players = 0;
    std::size_t number_of_bots = 0;
    std::vector<TextField> players_names;
    TextField field_for_number_of_players;
    TextButton start_button;
    Settings settings;

    void init_window();
    void draw() override;
};

class EndGameWindow : public Window {
public:
    EndGameWindow(Game game_) : game(std::move(game_)) {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "End game",
                      sf::Style::Titlebar | sf::Style::Close);
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~EndGameWindow() override = default;

private:
    Game game;
    std::vector<std::tuple<std::string, int, int>> results;
    std::vector<sf::Text> leaders_name;
    std::vector<sf::Text> leaders_score;
    sf::Text leaderboard;

    void init_window();
    void draw() override;
};

class LogWindow : public Window {
public:
    LogWindow(){
        window.create(sf::VideoMode(800, 1500), "Log",
                      sf::Style::Titlebar | sf::Style::Close);
        window.setPosition({200, 200});
        auto fs = cmrc::resources::get_filesystem();
        auto file = fs.open("times.ttf");
        std::string str(file.begin(), file.end());
        font.loadFromMemory(str.data(), str.size());
    }

    std::unique_ptr<Window> handle_events() override;
    void init_window(std::unique_ptr<Log> const &log);

    ~LogWindow() override = default;

private:
    sf::Text actions_text;
    void draw() override;
};
#endif  // EVOLUTION_PROJECT_WINDOW_H_
