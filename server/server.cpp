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
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "proto-src/server.grpc.pb.h"
//#include "settings.h"

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
using user::Token;
using user::User;
using user::UserService;

class ServiceImpl final : public UserService::Service {
    Status CreateRoom(ServerContext *context,
                      const CreateRoomRequest *request,
                      CreateRoomResponse *response) override {
        // TODO - print the id of the room

        // should i get name of this player too?
        std::string room_id;
        while (1) {
            for (int i = 0; i < ROOM_ID_LEN; ++i) {
                int a = random();
                while (isalpha(static_cast<char>(a)) == false and
                       isdigit(static_cast<char>(a)) == false) {
                    a = random();
                }
                room_id += std::to_string(a);
            }
            if (id_sett_room_list.find(room_id) == id_sett_room_list.end()) {
                break;
            } else {
                continue;
            }
        }
        assert(room_id.size() == ROOM_ID_LEN);
        /// default seed equals 0 in settings
        //        user::Settings settings{request->settings().quantity_of_players(),
        //                          request->settings().size_of_deck(),
        //                          request->settings().time_of_move(),
        //                          request->settings().local_player(),
        //                          rand(),
        //                          1,
        //                          room_id};
        user::Settings settings = request->settings();
        /// adding new room with settings
        id_sett_room_list.insert({room_id, settings});
        /// adding player's /*id*/ and /*name*/
        id_name_player_list.insert({{0, room_id}, request->player_name()});
        response->set_id(room_id);
        return Status::OK;
    }

    Status JoinRoom(ServerContext *context,
                    const JoinRoomRequest *request,
                    JoinRoomResponse *reply) override {
        std::cout << "FAIL1" << '\n';
        std::string room_id = request->room_name();
        std::string player_name = request->player_name();  // todo - use it somewhere

        auto looking_id = id_sett_room_list.find(room_id);
        // TODO suppose its better to do /throw/
        assert(looking_id != id_sett_room_list.end());

        user::Settings settings = looking_id->second;
        std::cout << "FAIL2" << '\n';

        //        settings1.set_quantity_of_players(settings.get_quantity_of_players());
        //        settings1.set_size_of_deck(settings.get_size_of_deck());
        //        settings1.set_time_of_move(settings.get_time_of_move());
        //        settings1.set_local_player(settings.get_local_player() + 1);  // todo think about
        //        it settings1.set_seed(settings.get_seed());
        //        settings1.set_room_id(settings.get_room_id());
        //        // todo update in future if user left lobby
        //        settings1.set_total(settings.get_total() + 1); //TODO
        //        settings1.set_room_id(request->room_name());



//        std::cout << "FAIL3" << '\n';
//
//        id_name_player_list.insert(
//            {{settings.get_local_player() + 1, room_id}, request->player_name()});
//        // update /*local_player*/ field in settings to update this field correctly in future
//        id_sett_room_list[room_id].set_local_player(settings.get_local_player() + 1);
//
//        std::cout << "FAIL4" << '\n';
//
//        // i guess this should be true - todo think about it
//        assert(settings.get_local_player() + 1 == id_sett_room_list[room_id].get_local_player());

//        reply->set_settings(settings);
        *reply->mutable_settings() = settings;
        std::cout << "FAIL5" << '\n';

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
        int player_id = request->player_id();
        std::string room_id = request->room_id();
        std::string name = id_name_player_list[{player_id, room_id}];
        response->set_name(name);
        return Status::OK;
    }

private:
    const int ROOM_ID_LEN = 10;
    std::unordered_map<std::string, user::Settings> id_sett_room_list;
    std::unordered_map<std::pair<int, std::string>, std::string> id_name_player_list;
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
