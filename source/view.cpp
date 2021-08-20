#include "view.h"
#include <thread>
#include "phase.h"
#include "window.h"

void DevelopmentPhaseView::start_development_phase(GameWindow &window) const {
    cards_delivery(window);
    window.recalc_cards();
    phase.set_start_of_phase(false);
}

void DevelopmentPhaseView::cards_delivery(GameWindow &window) const {
    phase.cards_delivery();
    window.recalc_cards();
}
void DevelopmentPhaseView::add_animal(GameWindow &window) const {
    auto new_animal = std::make_shared<Animal>(phase.get_cur_player());
    phase.add_animal(window.get_selected_card(), new_animal);
    window.play_animal(new_animal);
}

void DevelopmentPhaseView::add_property(const std::shared_ptr<Animal> &selected_animal,
                                        GameWindow &window) const {
    phase.give_property_to_animal(window.get_selected_card(), selected_animal);
    window.add_property_to_animal(selected_animal);
}

int DevelopmentPhaseView::parse_message(const std::string &str,
                                        GameWindow &window,
                                        const sf::Event &event) const {
    const std::string add_card("Player added new card on the board");
    const std::string add_property("Player added property to animal");

    if (str == add_card) {
        add_animal(window);  //сам разберется кто?
        return 1;
    }

    if (str == add_property) {
        //        add_property(selected_animal, window);
        return 1;
    }

    return -1;
}

int DevelopmentPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    if (phase.is_running_first_time()) {
        start_development_phase(window);
    }

    if (phase.get_game().stub_ != nullptr) {
        auto code = -1;
        auto f = [&]() {
            grpc::Status status = grpc::Status::CANCELLED;
            std::string message_from_server;
            auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(30000ms);

            while (!status.ok()) {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(60ms);
                grpc::ClientContext context;
                user::Nothing request;
                user::Message response;
                request.set_player_id(phase.get_game().get_cur_player_index());
                status = phase.get_game().stub_->GetMessage(&context, request, &response);
                if (status.ok() and std::chrono::steady_clock::now() < end_time) {
                    message_from_server = response.str();
                    code = parse_message(message_from_server, window, event);
                    break;
                } else {
                    std::this_thread::sleep_until(x);
                    code = -1;
                }
            }
        };

        if (phase.get_game().get_cur_player_index() !=
            phase.get_game().get_settings().get_local_player()) {
            std::thread thread(f);
            thread.join();
            if (code != -1) {
                return code;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            phase.get_game().get_log()->add_action_end_turn(phase.get_cur_player().get_name());
            return 2;
        }
        if (const auto &clicked_property_animal = window.get_clicked_property_animal();
            clicked_property_animal != nullptr) {
            window.show_properties(clicked_property_animal, false);
            return 0;
        }
        if (const auto &clicked_card = window.get_clicked_card(); clicked_card != nullptr) {
            window.click_card(clicked_card);
            return 0;
        }
        if (window.get_selected_card() != nullptr && window.check_new_animal()) {
            add_animal(window);
            phase.get_game().get_log()->add_action_new_animal(phase.get_cur_player().get_name());
            return 1;
        }
        if (const auto &clicked_animal = window.check_animals(); clicked_animal != nullptr) {
            add_property(clicked_animal, window);
            phase.get_game().get_log()->add_action_new_property(phase.get_cur_player().get_name(), window.get_selected_card()->property);
            return 1;
        }
    }
    if (phase.get_game().stub_ != nullptr) {
        return -1;
    } else {
        return 0;
    }
}

int FeedingPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    if (phase.is_running_first_time()) {
        start_feeding_phase(window);
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            phase.get_game().get_log()->add_action_end_turn(phase.get_cur_player().get_name());
            return 2;
        }
        if (const auto &clicked_property_animal = window.get_clicked_property_animal();
            clicked_property_animal != nullptr) {
            window.show_properties(clicked_property_animal, true);
            return 0;
        }
        if (window.check_food()) {
            window.click_food();
            return 0;
        }
        if (window.get_food_clicked()) {
            if (const auto &clicked_animal = window.check_animals(); clicked_animal != nullptr) {
                feed_animal(clicked_animal, window);
                phase.get_game().get_log()->add_action_feeding(phase.get_cur_player().get_name());
                return 1;
            }
        }
        //// при использовании свойств не забыть кинуть в log
    }
    return -1;
}
void FeedingPhaseView::start_feeding_phase(GameWindow &window) const {
    window.make_food();
    window.recalc_cards();
    phase.set_start_of_phase(false);
}
void FeedingPhaseView::feed_animal(const std::shared_ptr<Animal> &animal,
                                   GameWindow &window) const {
    phase.feed_animal(animal);
    window.feed_animal(animal);
}
