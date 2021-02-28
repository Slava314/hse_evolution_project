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

    void cards_delivery();
    // void place_card_on_board(Card &card);
    void set_next_phase();
    bool is_running_first_time() const;
    void set_start_of_phase(bool start);
    void add_animal(const std::shared_ptr<Card> &card, const std::shared_ptr<Animal> &new_animal);
    std::shared_ptr<Card> const &get_selected_card() const;
    ~DevelopmentPhase() override = default;

    void add_property_to_animal(const std::shared_ptr<Card> &card,
                                const std::shared_ptr<Animal> &animal);

private:
    Game &game;
    bool start_of_phase = true;
    std::shared_ptr<Card> selected_card = nullptr;
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