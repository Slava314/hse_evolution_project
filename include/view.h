#ifndef EVOLUTION_PROJECT_SOURCE_VIEW_H_
#define EVOLUTION_PROJECT_SOURCE_VIEW_H_

#include "phase.h"
#include "window.h"

class View {
public:
    virtual void handle_events(Game_Window &window, sf::Event) const = 0;
    virtual ~View() = default;
};

class Development_Phase_View : public View {
public:
    explicit Development_Phase_View(DevelopmentPhase &phase_) : phase(phase_) {
    }

    void handle_events(Game_Window &window, sf::Event event) const override;

    void start_development_phase(Game_Window &window) const;

    void cards_delivery(Game_Window &window) const;

    void add_animal(Game_Window &window) const;

    void add_property(int selected_animal, Game_Window &window) const;

    ~Development_Phase_View() override = default;

private:
    DevelopmentPhase &phase;
};

class Feeding_Phase_View : public View {
public:
    explicit Feeding_Phase_View(FeedingPhase &phase_) : phase(phase_) {
    }

    void handle_events(Game_Window &window, sf::Event) const override;

    ~Feeding_Phase_View() override = default;

private:
    FeedingPhase &phase;
};

#endif  // EVOLUTION_PROJECT_SOURCE_VIEW_H_
