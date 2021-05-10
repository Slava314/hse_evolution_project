#include <algorithm>
#include <cassert>
#include <charconv>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <grpcpp/server_context.h>

#include <grpc++/grpc++.h>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

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

using user::CreateRoom;
using user::CreateRoomResponse;
using user::Error;
using user::JoinRoom;
using user::Request;
using user::Response;
using user::Token;
using user::User;
using user::UserService;
using user::JoinRoomResponse;

//TODO
struct Settings {
  std::string room_name;
  int quantity_of_players;
  int size_of_deck;
  int time_of_move;
  int local_player = 0;
};

class ServiceImpl final : public UserService::Service {

  Status create_room(ServerContext *context, const CreateRoom *request, CreateRoomResponse *reply) override {
    //    reply.set
    std::string room_id;
    for (int i = 0; i < ROOM_ID_LEN; ++i) {
      int a = random();
      while (a < 48 or (a > 57 and a < 65) or (a > 90 and a < 97) or a > 122) {//TODO check this again __IS ALPHA
        a = random();
      }
      room_id += std::to_string(a);
    }
    assert(room_id.size() == ROOM_ID_LEN);

    Settings settings{request->settings().room_name(),
                      request->settings().quantity_of_players(),
                      request->settings().size_of_deck(),
                      request->settings().time_of_move(),
                      request->settings().local_player()};
    id_sett_room_list.insert({room_id, settings});

//    unsigned int room_num = id_sett_room_list.size() + 1;
//    id_num_room_list.insert({room_id, room_num});

    std::string room_name = request->settings().room_name();
    name_id_room_list.insert({room_name, room_id});

    return Status::OK;
  }

  Status join_room(ServerContext *context, const JoinRoom *request, JoinRoomResponse *reply) override {
    std::string room_name = request->room_name();
    auto looking_id = name_id_room_list.find(room_name);
    assert(looking_id != name_id_room_list.end());

    Settings settings = id_sett_room_list.find(looking_id->second)->second;
//    reply->settings().room_name(). = settings.room_name;
//    reply->settings().quantity_of_players() = settings.quantity_of_players;

//    user::Settings *settigns_{settings.room_name};
//    reply->set_allocated_settings(settigns_);
//    reply->set_allocated_settings()
    user::Settings settings1;
    std::string a = settings.room_name;
    settings1.set_allocated_room_name(&settings.room_name);
    settings1.set_quantity_of_players(settings.quantity_of_players);
    settings1.set_size_of_deck(settings.size_of_deck);
    settings1.set_time_of_move(settings.time_of_move);
    settings1.set_local_player(settings.local_player + 1); //todo think about it
//    reply.s

    return Status::OK;
  }

  Status get_message() {
    return Status::OK;
  }

  Status send_message() {
    return Status::OK;
  }

 private:
  const int ROOM_ID_LEN = 100;
  std::unordered_map<std::string, Settings> id_sett_room_list;
//  std::unordered_map<std::string, int> id_num_room_list;
  std::unordered_map<std::string, std::string> name_id_room_list; //todo can get rid of
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
