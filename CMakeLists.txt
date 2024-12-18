cmake_minimum_required(VERSION 3.28)
project(TrabalhoPratico)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrabalhoPratico main.cpp
        Buffer.cpp
        Buffer.h
        Deserto.cpp
        Deserto.h
        Cidade.cpp
        Cidade.h
        Cidade.h
        Caravanas/CaravanaMilitar.cpp
        Caravanas/CaravanaMilitar.h
        Caravanas/CaravanaComercio.cpp
        Caravanas/CaravanaComercio.h
        Caravanas/CaravanaSecreta.cpp
        Caravanas/CaravanaSecreta.h)
