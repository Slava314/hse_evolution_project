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
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, abandoning.");
        }
        // TODO - print the id of the room
        std::cout << "CREATE1" << '\n';

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
        std::cout << "CREATE2" << '\n';

        std::cout << "room_id len = " << room_id.size() << std::endl;
        std::cout << "room id --- " << room_id << std::endl;
        //        assert(room_id.size() == ROOM_ID_LEN);
        user::Settings settings = request->settings();
        std::cout << (request->settings().seed() == 0) << std::endl;
        std::cout << "GETTING SEED  = " << settings.seed() << std::endl;
        std::cout << "CREATE3" << '\n';

        /// seed is random for specific room
        // gets it from the host settings
        //        settings.set_seed(random());
        settings.set_total(1);
        /// adding new room with settings
        id_sett_room_list.insert({room_id, settings});
        /// adding player's /*id*/ and /*name*/

        std::cout << "CREATE4" << '\n';

        id_name_player_list.insert({{0, room_id}, request->player_name()});
        response->set_id(room_id);

        std::cout << "CREATE5" << '\n';
        std::cout << "is_sett_room_list.size() = " << id_sett_room_list.size() << std::endl;
        std::cout << "room_id = " << room_id << std::endl;
        return Status::OK;
    }

    Status JoinRoom(ServerContext *context,
                    const JoinRoomRequest *request,
                    JoinRoomResponse *reply) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, abandoning.");
        }
        std::string room_id = request->room_name();
        std::string player_name = request->player_name();

        std::cout << "JOIN1" << '\n';
        auto looking_id = id_sett_room_list.find(room_id);
        std::cout << "JOIN1.5" << '\n';

        if (looking_id == id_sett_room_list.end()) {
            throw ServerError("Could not join room, there is no such room with this id --- " +
                              room_id);
        }
        std::cout << "JOIN2" << '\n';

        user::Settings settings = looking_id->second;

        settings.set_total(settings.total() + 1);
        settings.set_local_player(settings.local_player() + 1);
        // update settings in map
        std::cout << "JOIN3" << '\n';
        id_sett_room_list.find(room_id)->second = settings;
        id_name_player_list[{settings.local_player(), room_id}] = player_name;
        std::cout << "JOIN4" << '\n';

        *reply->mutable_settings() = settings;

        return Status::OK;
    }

    Status AddCardOnTheBoard(ServerContext *context,
                             const user::PlayAsAnimalAction *request,
                             user::PlayAsAnimalAction *reply) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, abandoning.");
        }
        user::Action message;
        message.set_player_id(request->player());
        *message.mutable_play_animal() = *request;
        saved_messages.push_back(message);
        return Status::OK;
    }

    Status AskHowManyPlayersInTotal(ServerContext *context,
                                    const user::Nothing *request,
                                    user::AskHowManyPlayersTotalInGame *reply) override {
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, abandoning.");
        }
        if(id_sett_room_list.find(request->message().value()) == id_sett_room_list.end()){
            std::cout << "Could not get total players before delivering cards\n";
//            throw ServerError("Could not get total players before delivering cards");
        }

        auto looking_settings = id_sett_room_list[request->message().value()];
        //getting the last's player settings - they have to be valid
        reply->set_how_many(looking_settings.total());
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
        if (context->IsCancelled()) {
            return Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, abandoning.");
        }
        int player_id = request->player_id();
        std::string room_id = request->room_id();
        std::string name = id_name_player_list[{player_id, room_id}];
        response->set_name(name);
        return Status::OK;
    }

private:
    const int ROOM_ID_LEN = 5;
    std::map<std::string, user::Settings> id_sett_room_list;
    std::map<std::pair<int, std::string>, std::string> id_name_player_list;
    std::vector<user::Action> saved_messages;
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
