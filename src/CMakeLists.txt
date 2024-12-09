
target_sources (${PROJECT_NAME} PRIVATE
    src/alu.cpp
    src/control.cpp
    src/eeprom.cpp
    src/emulator.cpp
    src/counter.cpp
    src/sram.cpp
)

target_include_directories (${PROJECT_NAME} PUBLIC
    src
)
