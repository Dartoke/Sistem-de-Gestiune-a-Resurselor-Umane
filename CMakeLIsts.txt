cmake_minimum_required(VERSION 3.10)
project(SistemHR)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/proiect)

add_executable(SistemHR
    proiect/main.cpp
    proiect/utile.cpp
    proiect/angajati.cpp
    proiect/angajatFullTime.cpp
    proiect/angajatPartTime.cpp
    proiect/contractor.cpp
    proiect/departament.cpp
    proiect/proiect.cpp
)
