#ifndef CPU_i4004_H
#define CPU_i4004_H

#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>
#include <iomanip>

class i4004 {
public:
  i4004();
  void load_program(const std::vector<uint8_t>& program);
  void run();
  void reset();
  void clock();
  void print_state() const;

private:
    std::array<uint8_t, 4096> rom; // 4 KB ROM
    std::array<uint8_t, 640> ram; // 640 bytes RAM
    std::array<uint8_t, 16> registers; // 16 registers
    std::pair<std::array<uint8_t, 640>, std::array<uint16_t, 3>> stack; // Stack with 640 bytes and 3 12-bit registers
    uint16_t pc; // Program Counter
    uint8_t sp; // Stack Pointer
    uint8_t slr; // Stack Layer Register
    uint8_t acc; // Accumulator
    uint8_t temp_reg; // Temporary Register
    bool halted; // HLT instruction flag
    bool current_phase; // Current clock phase (false for Ph1, true for Ph2)
    uint8_t instruction_register; // Instruction Register
    // uint8_t fetched_instruction; // Instruction fetched in Ph1

  void fetch_instruction();
  void execute_instruction();
  void clock_tick();
};

enum instruction_set_architecture_i4004 {
  nop,
};

#endif