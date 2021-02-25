#ifndef EVOLUTION_PROJECT_SOURCE_PHASE_H_
#define EVOLUTION_PROJECT_SOURCE_PHASE_H_

#include <memory>
#include "game_fwd.h"
#include "view_fwd.h"

class Phase {
public:
    virtual std::unique_ptr<View> get_view() = 0;
    virtual ~Phase() = default;
};

class Feeding_Phase;

class Development_Phase : public Phase {
public:
    //Development_Phase() = default;
    explicit Development_Phase(Game &game_) : game(game_){};

    std::unique_ptr<View> get_view() override;

    void cards_delivery();
    //void place_card_on_board(Card &card);
    void set_next_phase();
    bool is_running_first_time() const;
    ~Development_Phase() override = default;

private:
    Game &game;

};

class Feeding_Phase : public Phase {
public:
    //Feeding_Phase() = default;
    explicit Feeding_Phase(Game &game_) : game(game_){};

    std::unique_ptr<View> get_view() override;

    void set_next_phase();
    bool is_running_first_time()const;
    ~Feeding_Phase() override = default;

private:
    Game &game;
};

#endif  // EVOLUTION_PROJECT_SOURCE_PHASE_H_
