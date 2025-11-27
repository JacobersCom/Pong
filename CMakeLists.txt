cmake_minimum_required(VERSION 3.14)

project(Pong LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG)

add_subdirectory(Project)
add_subdirectory(Game)