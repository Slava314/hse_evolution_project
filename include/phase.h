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

class DevelopmentPhase : public Phase {
public:
    explicit DevelopmentPhase(Game &game_) : game(game_){};

    std::unique_ptr<View> get_view() override;

    std::vector<std::vector<std::shared_ptr<Card>>> cards_delivery();
    // void place_card_on_board(Card &card);
    void set_next_phase();
    bool is_running_first_time() const;
    void set_start_of_phase(bool start);
    void add_animal(std::shared_ptr<Card> card, std::shared_ptr<Animal> new_animal);
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
    ~FeedingPhase() override = default;

private:
    Game &game;
};

#endif  // EVOLUTION_PROJECT_SOURCE_PHASE_H_
