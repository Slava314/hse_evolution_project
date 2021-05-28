#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_context.h>
#include <algorithm>
#include <cassert>
#include <charconv>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "proto-src/server.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using user::CreateRoomRequest;
using user::CreateRoomResponse;
using user::GetPlayerRequest;
using user::GetPlayerResponse;
using user::JoinRoomRequest;
using user::JoinRoomResponse;

using user::Error;
using user::Request;
using user::Response;
using user::User;
using user::UserService;

struct ServerError : public std::runtime_error {
    explicit ServerError(const std::string &str) : std::runtime_error(str) {
    }
};

class ServiceImpl final : public UserService::Service {
    Status CreateRoom(ServerContext *context,
                      const CreateRoomRequest *request,
                      CreateRoomResponse *response) override {
        std::cout << "Creating server - successfully\n";

        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }
        // TODO - print the id of the room

        std::string room_id;
        while (1) {
            for (int i = 0; i < ROOM_ID_LEN; ++i) {
                int a = random() % 255;
                while (isalpha(static_cast<char>(a)) == false and
                       isdigit(static_cast<char>(a)) == false) {
                    a = random();
                }
                room_id += std::to_string(a);
                if (room_id.size() >= ROOM_ID_LEN)
                    break;
            }
            if (id_sett_room_list.find(room_id) == id_sett_room_list.end()) {
                break;
            } else {
                continue;
            }
        }

        //        assert(room_id.size() == ROOM_ID_LEN);
        user::Settings settings = request->settings();
        settings.set_room_id(room_id);
        settings.set_total(1);
        /// adding new room with settings
        id_sett_room_list.insert({room_id, settings});
        /// adding player's /*id*/ and /*name*/
        pl_id_room_id_player_list.insert({{0, room_id}, request->player_name()});

        response->set_id(room_id);

        std::cout << "room id = " << room_id << std::endl;
        std::cout << "Creating server - successfully - getting out of here\n";

        return Status::OK;
    }

    Status JoinRoom(ServerContext *context,
                    const JoinRoomRequest *request,
                    JoinRoomResponse *reply) override {
        std::cout << "Joining server - successfully\n";
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }
        std::string room_id = request->room_name();
        std::string player_name = request->player_name();

        auto looking_id = id_sett_room_list.find(room_id);
        if (looking_id == id_sett_room_list.end()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Could not join room, there is no such room with this id --- " + room_id);
        }

        user::Settings settings = looking_id->second;

        settings.set_total(settings.total() + 1);
        settings.set_local_player(settings.local_player() + 1);
        // update settings in map

        id_sett_room_list.find(room_id)->second = settings;
        pl_id_room_id_player_list.insert({{settings.local_player(), room_id}, player_name});

        *reply->mutable_settings() = settings;
        std::cout << "Joining server - successfully - getting out of here\n";

        return Status::OK;
    }

    Status AddCardOnTheBoard(ServerContext *context,
                             const user::PlayAsAnimalAction *request,
                             user::PlayAsAnimalAction *reply) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }

        if (id_sett_room_list.find(request->room_id()) == id_sett_room_list.end()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Could not find room in HostHasStartedTheGame, there is no such room "
                          "with this id --- " +
                              request->room_id());
        }

        user::Action message;

        message.set_player_id(request->player());
        *message.mutable_play_animal() = *request;

        auto a = id_sett_room_list.find(request->room_id());
        int total_players = a->second.total();

        messages.push_back({"Player added new card on the board", total_players});
        saved_data_for_messages.push_back(message);

        return Status::OK;
    }

    Status get_message() {
        return Status::OK;
    }

    Status send_message() {
        return Status::OK;
    }

    Status GetPlayerName(ServerContext *context,
                         const GetPlayerRequest *request,
                         GetPlayerResponse *response) override {
        std::cout << "GetPlayerName - 1 \n";

        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }
        int player_id = request->player_id();
        std::string room_id = request->room_id();
        std::cout << "got player id = " << request->player_id() << std::endl;
        std::cout << "got room id = " << request->room_id() << std::endl;
        if (pl_id_room_id_player_list.find({player_id, room_id}) ==
            pl_id_room_id_player_list.end()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Could get player name with such id  --- " + std::to_string(player_id));
        }
        std::string name = pl_id_room_id_player_list[{player_id, room_id}];
        response->set_name(name);
        std::cout << "GetPlayerName - 2 \n";
        return Status::OK;
    }

    Status GetMessage(ServerContext *context,
                      const user::Nothing *request,
                      user::Message *response) override {
        if (messages.empty()) {
            return Status::CANCELLED;
        }
        response->set_str(messages.back().first);
        return Status::OK;
    }

    Status GetDataAboutMove(ServerContext *context,
                            const user::Request *request,
                            user::Action *response) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }
        if (messages.empty() == true) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Could not get message, the message vector is empty.");
        }

        return Status::OK;
    }

    Status GetTotalPlayers(ServerContext *context,
                           const user::Request *request,
                           user::TotalPlayers *response) override {
        std::cout << "GetTotalPlayers - 1 \n";
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }

        std::string room_id = request->room_id();

        std::cout << "room id in GetTotalPlayers = " << room_id << std::endl;

        if (id_sett_room_list.find(room_id) == id_sett_room_list.end()) {
            return Status(
                grpc::StatusCode::CANCELLED,
                "Could not join room in GetTotalPlayers, there is no such room with this id --- " +
                    room_id);
        }

        auto found = id_sett_room_list.find(room_id);
        response->set_count(found->second.total());

        std::cout << "GetTotalPlayers - 2 \n";

        return Status::OK;
    }

    Status HostHasStartedTheGame(ServerContext *context,
                                 const user::Request *request,
                                 user::Nothing *response) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }

        std::string room_id = request->room_id();

        std::cout << "size of map with rooms = " << id_sett_room_list.size() << std::endl;

        for (auto x : id_sett_room_list) {
            std::cout << "getting room id  = " << x.first << std::endl;
        }

        //                if (id_sett_room_list.find(room_id) == id_sett_room_list.end()) {
        //                    return Status(grpc::StatusCode::CANCELLED,
        //                                  "Could not find room in HostHasStartedTheGame, there is
        //                                  no such room with this id --- " + room_id);
        //                }

        auto a = id_sett_room_list.find(room_id);
        int total_players = a->second.total();
        messages.push_back({"Game has started", total_players - 1});
        return Status::OK;
    }

    Status HasTheGameStartedAlready(ServerContext *context,
                                    const user::Nothing *request,
                                    user::Nothing *response) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Deadline exceeded or Client cancelled, abandoning.");
        }

        if (messages.empty()) {
            return Status(grpc::StatusCode::CANCELLED,
                          "Could not get message, message vector is empty ");
        }

        if (messages.back().first == "Game has started") {
            if (messages.back().second == 1) {
                messages.pop_back();
                return Status::OK;
            } else {
                messages.back().second--;
                return Status::OK;
            }
        }
        // by default?
        return grpc::Status::CANCELLED;
    }

private:
    const int ROOM_ID_LEN = 2;
    std::map<std::string, user::Settings> id_sett_room_list;
    std::map<std::pair<int, std::string>, std::string> pl_id_room_id_player_list;
    std::vector<user::Action> saved_data_for_messages;
    std::vector<std::pair<std::string, int>> messages;
    std::vector<std::string> players_names;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    ServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}