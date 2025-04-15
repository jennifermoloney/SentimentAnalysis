cmake_minimum_required(VERSION 3.22)

project(SentimentAnalysis VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic handling of Qt's MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
# If you are using Qt5 instead, use:
# find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# List your source files
set(SOURCES
        src/main.cpp
        src/UI.cpp
        src/UI.h
        src/hashmap.cpp
        src/hashmap.h
)

# Create the executable using the project's name ("SentimentAnalysis")
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the Qt libraries to your target using ${PROJECT_NAME}
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

# (Optional) macOS: Create an application bundle

