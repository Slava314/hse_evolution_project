#ifndef EVOLUTION_PROJECT_SOURCE_PHASE_H_
#define EVOLUTION_PROJECT_SOURCE_PHASE_H_

#include <SFML/Window/Event.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include "animal.h"
#include "cards.h"
#include "game_fwd.h"
#include "server.grpc.pb.h"
#include "view_fwd.h"
#include "window_fwd.h"

using namespace std::chrono_literals;
class Phase {
public:
    virtual std::unique_ptr<View> get_view() = 0;
    virtual std::size_t get_cur_player_index() const = 0;
    virtual void run_phase(GameWindow &window, sf::Event event) = 0;
    virtual ~Phase() = default;
    const int INTERVAL = 100;
};

class DevelopmentPhase : public Phase {
public:
    explicit DevelopmentPhase(Game &game_);

    std::unique_ptr<View> get_view() override;
    std::size_t get_cur_player_index() const override;
    Player &get_cur_player();

    bool is_running_first_time() const;
    void set_next_phase();
    void set_start_of_phase(bool start);

    void cards_delivery();
    void add_animal(const std::shared_ptr<Card> &card, std::shared_ptr<Animal> &new_animal);
    void give_property_to_animal(const std::shared_ptr<Card> &card,
                                 const std::shared_ptr<Animal> &new_animal);

    std::vector<std::vector<std::shared_ptr<Card>>> get_cards();
    void run_phase(GameWindow &window, sf::Event event) override;
    void parse_message(const std::string &str);

        ~DevelopmentPhase() override = default;

private:
    void add_animal();
private:
    Game &game;
    int cur_player_index;
    std::vector<int> end_turn;
    int sum = 0;
    bool start_of_phase = true;
};

class FeedingPhase : public Phase {
public:
    FeedingPhase(Game &game_);
    std::unique_ptr<View> get_view() override;
    std::size_t get_cur_player_index() const override;

    void set_next_phase();
    bool is_running_first_time() const;
    void set_start_of_phase(bool start);
    [[nodiscard]] bool is_end_of_phase() const;

    void kill_animals();

    void decrease_food_balance();
    size_t get_food_balance() const;
    void feed_animal(std::shared_ptr<Animal> animal);
    void run_phase(GameWindow &window, sf::Event event) override;

    ~FeedingPhase() override = default;

private:
    static constexpr size_t MIN_FOOD_BALANCE = 3;
    static constexpr size_t MAX_FOOD_BALANCE = 10;
    static size_t define_food_balance();
    int cur_player_index;
    std::vector<int> end_turn;
    int sum = 0;

    Game &game;
    size_t food_balance = 0;
    bool start_of_phase = true;
    void attack(std::shared_ptr<Animal> attacker, std::shared_ptr<Animal> victim);
};

#endif  // EVOLUTION_PROJECT_SOURCE_PHASE_H_
