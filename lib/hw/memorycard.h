/*
 *  ALU Card HW Interface
 *  Evan Grissino 2024
 *
 */

 /*

 Memory Board Interface Pinout

 Pwr
 Gnd
 D0-D7
 MarLoad
 MemOut
 MemWrite
 ChipSelect

 */

#pragma once

#define BUS_DATA_0_PIN D0
#define BUS_DATA_1_PIN D1
#define BUS_DATA_2_PIN D2
#define BUS_DATA_3_PIN D3
#define BUS_DATA_4_PIN D4
#define BUS_DATA_5_PIN D5
#define BUS_DATA_6_PIN D6
#define BUS_DATA_7_PIN D7

#define CHIP_ENABLE_PIN D10
#define OUTPUT_ENABLE_PIN D11
#define WRITE_ENABLE_PIN D12
#define MAR_LOAD_PIN D13

#include <stdlib.h>

 // This runs in embedded only, never on host

namespace SAP8
{
namespace HW
{

enum Programs
{
    kProgram0,
    kProgram1,
    kProgram2,
    kProgram3,
    kProgram4,
    kProgram5,
    kProgram6,
    kProgram7,
    kProgram8,
    kProgram9,
    kProgram10,
    kProgram11,
    kProgram12,
    kProgram13,
    kProgram14,
    kProgram15,
    NumPrograms
};

enum PinDirection
{
    kInput,
    kOutput
};

class MemoryBoard
{
public:
    MemoryBoard();

    /*!
     * @brief Watch hardware Read Operation
     * @return data value read at current address
     */
    uint8_t readWatch();

    /*!
     * @brief Watch hardware set address operation
     * @return address set in the MAR
     */
    uint16_t setAddressWatch();

    /*!
     * @brief Watch hardware write operation
     * @return Data value written to current address
     */
    uint8_t writeWatch();

private:

    /*!
     * @brief Read data lines
     * @return
     */
    uint8_t read();

    /*!
     * @brief Write Data Lines
     * @return
     */
    uint8_t write(uint8_t address, uint8_t value);

    /*!
     * @brief Set PROM Output Enable
     */
    void enableOut(bool state);

    /*!
     * @brief Set PROM Write Enable
     */
    void enableWrite(bool state);

    /*!
     * @brief Set PROM Chip Enable
     */
    void enableChip(bool state);

    /*!
     * @brief set MAR Load enable
     */
    void enableMarLoad(bool state);

    /*!
     * @brief Out Enable ISR
     * @param state
     */
    void outHandler(bool state);

    /*!
     * @brief Write Enable ISR
     * @param state
     */
    void writeHandler(bool state);

    /*!
     * @brief Chip Enable ISR
     * @param state
     *
     * PROM Chip is enabled before read/write and disabled at all other times
     * There is a solder pad that can be bridged when using the standard board
     */
    void chipHandler(bool state);

    /*!
     * @brief MAR Load ISR
     * @param state
     *
     * Mar is loading, save data value as address
     */
    void marHandler(bool state);


    static uint8_t readDataLines();

    Programs program;
    uint16_t currentAddress;

    const uint8_t dataPins[8]{
        BUS_DATA_0_PIN,
        BUS_DATA_1_PIN,
        BUS_DATA_2_PIN,
        BUS_DATA_3_PIN,
        BUS_DATA_4_PIN,
        BUS_DATA_5_PIN,
        BUS_DATA_6_PIN,
        BUS_DATA_7_PIN};

    static const uint8_t WriteEnablePin{WRITE_ENABLE_PIN};
    static const uint8_t OutputEnablePin{OUTPUT_ENABLE_PIN};
    static const uint8_t ChipEnablePin{CHIP_ENABLE_PIN};
    static const uint8_t MarLoadPin{MAR_LOAD_PIN};
};

static const size_t busWidth{8};

};
};
