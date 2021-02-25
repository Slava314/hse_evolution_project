#ifndef EVOLUTION_PROJECT_SOURCE_VIEW_H_
#define EVOLUTION_PROJECT_SOURCE_VIEW_H_

#include "phase.h"
#include "window.h"

class View {
public:
    virtual void handle_events(Game_Window& window) const = 0;
    virtual ~View() = default;
};

class Development_Phase_View : public View {
public:

    explicit Development_Phase_View(Development_Phase& phase_) : phase(phase_){
    }

    void handle_events(Game_Window &window) const override;

    void init_game(Game_Window& window) const;

    void cards_delivery(Game_Window& window) const;

    void place_card(Card& card, Game_Window& window);

    ~Development_Phase_View() override = default;


private:
    Development_Phase &phase;
};

class Feeding_Phase_View : public View {
public:

    explicit Feeding_Phase_View(Feeding_Phase & phase_) : phase(phase_){
    }

    void handle_events(Game_Window &window) const override;

    ~Feeding_Phase_View() override = default;

private:
    Feeding_Phase &phase;

};

#endif  // EVOLUTION_PROJECT_SOURCE_VIEW_H_
