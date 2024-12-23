cmake_minimum_required(VERSION 3.27)
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
        Caravanas/CaravanaSecreta.h
        Caravana.cpp
        Caravana.h
        Caravana.cpp
        Montanhas.cpp
        Montanhas.h
        Barbaros.cpp
        Barbaros.h
        Barbaros.cpp
        Itens.cpp
        Itens.h
        Itens/CaixaPandora.cpp
        Itens/CaixaPandora.h
        Itens/ArcaTesouro.cpp
        Itens/ArcaTesouro.h
        Itens/Jaula.cpp
        Itens/Jaula.h
        Itens/Mina.cpp
        Itens/Mina.h
)
