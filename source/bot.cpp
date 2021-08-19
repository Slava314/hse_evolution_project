#include "bot.h"
#include "game.h"

void Bot::make_move(Game &game) {
    if (game.get_phase()->get_name() == "DevelopmentPhase") {
        make_move_in_dev_phase(game);
    } else if (game.get_phase()->get_name() == "FeedingPhase") {
        make_move_in_feed_phase(game);
    } else {
        return;
    }
}

void Bot::make_move_in_dev_phase(Game &game) {
    if (get_bot_player(game).get_cards_in_hands().empty()) {
        end_turn(game);
        return;
    }

    std::unordered_map<Properties, bool> is_defending_property = {
        {FAT_TISSUE, false}, {BIG, true},        {STOMPER, false},
        {SWIMMINGS, true},   {RUNNING, true},    {CARNIVOROUS, false},
        {BURROWING, true},   {CAMOUFLAGE, true}, {SHARP_VISION, false},
    };

    for (auto animal : get_bot_player(game).get_animals_on_board()) {
        bool has_defending_property = false;
        for (auto property : animal->get_properties()) {
            if (is_defending_property[property]) {
                has_defending_property = true;
            }
        }
        if (!has_defending_property) {
            for (auto card : get_bot_player(game).get_cards_in_hands()) {
                if (is_defending_property[card->property]) {
                    play_card_as_property(game, card, animal);
                    return;
                }
            }
            if (random_num(0, 1) == 0) {
                dynamic_cast<DevelopmentPhase *>(game.get_phase().get())
                    ->give_property_to_animal(get_bot_player(game).get_cards_in_hands()[0], animal);
                return;
            }
        }
    }

    if (get_bot_player(game).get_cards_in_hands().size() == 1) {
        if (get_bot_player(game).get_animals_on_board().empty()) {
            auto new_animal = std::make_shared<Animal>(get_bot_player(game));
            dynamic_cast<DevelopmentPhase *>(game.get_phase().get())
                ->add_animal(get_bot_player(game).get_cards_in_hands()[0], new_animal);
            return;
        } else {
            if (random_num(0, 1) == 0) {
                auto new_animal = std::make_shared<Animal>(get_bot_player(game));
                dynamic_cast<DevelopmentPhase *>(game.get_phase().get())
                    ->add_animal(get_bot_player(game).get_cards_in_hands()[0], new_animal);
            } else {
                end_turn(game);
                return;
            }
        }
    } else {
        bool has_defending_property_card = false;
        for (auto card : get_bot_player(game).get_cards_in_hands()) {
            if (is_defending_property[card->property]) {
                has_defending_property_card = true;
            }
        }
        if (has_defending_property_card) {
            for (auto card : get_bot_player(game).get_cards_in_hands()) {
                if (!is_defending_property[card->property]) {
                    play_card_as_animal(game, card);
                    return;
                }
            }
            play_card_as_animal(game, get_bot_player(game).get_cards_in_hands()[0]);
            return;
        } else {
            if (random_num(0, 1) == 0) {
                play_card_as_animal(game, get_bot_player(game).get_cards_in_hands()[0]);
                return;
            } else {
                end_turn(game);
                return;
            }
        }
    }
}

void Bot::make_move_in_feed_phase(Game &game) {
    if (dynamic_cast<FeedingPhase *>(game.get_phase().get())->get_food_balance() == 0) {
        for (auto attacker : get_bot_player(game).get_animals_on_board()) {
            for (auto property : attacker->get_properties()) {
                if (attacker->is_hungry() && property == CARNIVOROUS) { // also checking fat tissue would be better
                    std::vector<std::shared_ptr<Animal>> animals_that_can_be_eaten;
                    for (auto player : game.get_players()) {
                        for (auto victim : player.get_animals_on_board()) {
                            if (victim->could_be_attacked(attacker) && victim != attacker) {
                                animals_that_can_be_eaten.emplace_back(victim);
                            }
                        }
                    }
                    if (!animals_that_can_be_eaten.empty()) {
                        dynamic_cast<FeedingPhase *>(game.get_phase().get())
                            ->attack(attacker, animals_that_can_be_eaten[random_num(0, animals_that_can_be_eaten.size() - 1)]);
                        return;
                    }
                }
            }
        }
        end_turn(game);
        return;
    } else {
        for (auto animal : get_bot_player(game).get_animals_on_board()) {
            if (animal->is_hungry()) {
                dynamic_cast<FeedingPhase *>(game.get_phase().get())->feed_animal(animal);
            }
        }
        for (auto animal : get_bot_player(game).get_animals_on_board()) {
            if (dynamic_cast<FeedingPhase *>(game.get_phase().get())->get_food_balance() == 0) {
                break;
            } else if (animal->get_properties().find(STOMPER) != animal->get_properties().end()) {
//                animal->use_property(STOMPER, game.get_phase());
            }
        }
    }
}

void Bot::play_card_as_animal(Game &game, const std::shared_ptr<Card> &card) {
    auto new_animal = std::make_shared<Animal>(get_bot_player(game));
    dynamic_cast<DevelopmentPhase *>(game.get_phase().get())
        ->add_animal(get_bot_player(game).get_cards_in_hands()[0], new_animal);
}

void Bot::play_card_as_property(Game &game,
                                const std::shared_ptr<Card> &card,
                                const std::shared_ptr<Animal> &animal) {
    dynamic_cast<DevelopmentPhase *>(game.get_phase().get())->give_property_to_animal(card, animal);
}

Player &Bot::get_bot_player(Game &game) {
    return game.get_players()[game.get_cur_player_index()];
}

int Bot::random_num(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
void Bot::end_turn(Game &game) {
    get_bot_player(game).set_ended_turn(true);
    game.set_players_ended_turn(game.get_players_ended_turn() + 1);
}
