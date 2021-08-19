#ifndef EVOLUTION_PROJECT_SOURCE_VIEW_H_
#define EVOLUTION_PROJECT_SOURCE_VIEW_H_

#include "phase.h"
#include "window.h"

class View {
public:
    virtual int handle_event(GameWindow &window, const sf::Event &event) const = 0;
    virtual ~View() = default;
    };

class DevelopmentPhaseView : public View {
public:
    explicit DevelopmentPhaseView(DevelopmentPhase &phase_) : phase(phase_) {
    }

    int handle_event(GameWindow &window, const sf::Event &event) const override;
    void start_development_phase(GameWindow &window) const;

    void cards_delivery(GameWindow &window) const;
    int parse_message(const std::string &str, GameWindow &window, const sf::Event &event) const ;

    void add_animal(GameWindow &window) const;
    void add_property(const std::shared_ptr<Animal> &selected_animal, GameWindow &window) const;

    ~DevelopmentPhaseView() override = default;

private:
    DevelopmentPhase &phase;
};

class FeedingPhaseView : public View {
public:
    explicit FeedingPhaseView(FeedingPhase &phase_) : phase(phase_) {
    }

    int handle_event(GameWindow &window, const sf::Event &event) const override;

    ~FeedingPhaseView() override = default;

private:
    FeedingPhase &phase;
    void start_feeding_phase(GameWindow &window) const;
    void feed_animal(const std::shared_ptr<Animal> &animal, GameWindow &window) const;
};

#endif  // EVOLUTION_PROJECT_SOURCE_VIEW_H_
