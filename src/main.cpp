#include <cstdint>
#include <iostream>
#include <vector>

#include "./arch/i4004/i4004.h"

int main() {
  i4004 vm;
  vm.reset();

  std::vector<uint8_t> program = {
    0x00,        // NOP
    0xD0, 0x04,  // LDM 4
    // 0x20, 0x03,  // JMP 3 (Infinity cycle)
    0xFE         // HLT
  };

  vm.load_program(program);
  vm.print_state();
  vm.run();
  vm.print_state();

  return 0;
}
