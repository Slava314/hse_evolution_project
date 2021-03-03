#ifndef EVOLUTION_PROJECT_SOURCE_PHASE_H_
#define EVOLUTION_PROJECT_SOURCE_PHASE_H_

#include <memory>
#include <vector>
#include "animal.h"
#include "cards.h"
#include "game_fwd.h"
#include "view_fwd.h"

class Phase {
public:
    virtual std::unique_ptr<View> get_view() = 0;
    virtual ~Phase() = default;
};

class FeedingPhase;

class DevelopmentPhase : public Phase {
public:
    explicit DevelopmentPhase(Game &game_) : game(game_){};

    std::unique_ptr<View> get_view() override;

    bool is_running_first_time() const;
    void set_next_phase();
    void set_start_of_phase(bool start);

    void cards_delivery();
    void add_animal(std::shared_ptr<Card> &card, std::shared_ptr<Animal> &new_animal);
    void give_property_to_animal(const std::shared_ptr<Card> &card,
                                     const std::shared_ptr<Animal> &new_animal);

    std::vector<std::vector<std::shared_ptr<Card>>> get_cards();
    ~DevelopmentPhase() override = default;

private:
    Game &game;
    bool start_of_phase = true;
};

class FeedingPhase : public Phase {
public:
    explicit FeedingPhase(Game &game_) : game(game_){};

    std::unique_ptr<View> get_view() override;

    void set_next_phase();
    bool is_running_first_time() const;
    [[nodiscard]] bool is_end_of_phase() const;

    void feed_animal(const std::shared_ptr<Animal> &animal);
    void decrease_food_balance();
    void kill_animals();

    ~FeedingPhase() override = default;


private:
    static constexpr size_t MIN_FOOD_BALANCE = 10;
    static constexpr size_t MAX_FOOD_BALANCE = 3;
    static size_t define_food_balance();

    Game &game;
    size_t food_balance = 0;
};

#endif  // EVOLUTION_PROJECT_SOURCE_PHASE_H_
