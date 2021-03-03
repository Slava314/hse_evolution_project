#ifndef EVOLUTION_PROJECT_SOURCE_VIEW_H_
#define EVOLUTION_PROJECT_SOURCE_VIEW_H_

#include "phase.h"
#include "window.h"

class View {
public:
    virtual void handle_event(GameWindow &window, const sf::Event &event) const = 0;
    virtual ~View() = default;
};

class DevelopmentPhaseView : public View {
public:
    explicit DevelopmentPhaseView(DevelopmentPhase &phase_) : phase(phase_) {
    }

    void handle_event(GameWindow &window, const sf::Event &event) const override;

    void start_development_phase(GameWindow &window) const;

    void cards_delivery(GameWindow &window) const;

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

    void handle_event(GameWindow &window, const sf::Event &event) const override;

    ~FeedingPhaseView() override = default;

private:
    FeedingPhase &phase;
};

#endif  // EVOLUTION_PROJECT_SOURCE_VIEW_H_
