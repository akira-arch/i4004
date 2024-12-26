#include "./i4004.h"

i4004::i4004() : pc(0), sp(0), acc(0), temp_reg(0), instruction_register(0), halted(false), current_phase(false) {};

void i4004::reset() {
  pc = 0;
  sp = 0;
  slr = 0;
  acc = 0;
  temp_reg = 0;
  for (auto &reg : registers) reg = 0;
  stack.first.fill(0);
  stack.second.fill(0);
  halted = false;
  current_phase = false;
}

void i4004::load_program(const std::vector<uint8_t> &program) {
  // std::cout << program.size() << std::endl;
  for (size_t i = 0; i < program.size(); ++i) {
    this->rom[i] = program[i];
    // this->pc += 0x01;
  }
}

void i4004::print_state() const {
  std::cout << "SHW Registers: " << std::endl; // SHW - Shadow
  std::cout << "PC: " << "0x" << std::setfill('0') << std::setw(4) << std::hex << static_cast<uint>(pc) << std::endl;
  std::cout << "SP: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(sp) << std::endl;
  std::cout << "SLR: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(slr) << std::endl;
  std::cout << "ACC: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(acc) << std::endl;
  std::cout << "TEMPR: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(temp_reg) << std::endl;
  std::cout << "GPR Registers: " << std::endl;
  for (auto &&reg : this->registers) {
    std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(reg) << " ";
  }
  std::cout << std::endl;
}

void i4004::clock_tick() {
  if (halted) return;

  if (current_phase) {
    // Ph2: Execute phase
    execute_instruction();
  } else {
    // Ph1: Fetch phase
    fetch_instruction();
  }

  // Toggle the phase
  current_phase = !current_phase;
}

void i4004::run() {
  // while (this->pc < rom.size()) {
  while (!halted) {
    // std::cout << this->pc << " " << rom.size() << std::endl;
    clock_tick();
    // this->pc++;
  }
}

void i4004::clock() {
  this->clock_tick();
}

void i4004::fetch_instruction() {
  instruction_register = rom.at(pc);
}

void i4004::execute_instruction() {
  switch (instruction_register & 0xFF) {
  // switch (instruction_register) {
    case instruction_set_architecture_i4004::nop:  // NOP
      this->pc += 1;
      break;
    case 0xD0:  // LDM (Load Immediate)
      this->acc = rom.at(pc + 1);
      this->pc += 2;
      break;
    case 0x20:  // JMP (Jump)
      this->pc = (pc & 0xFFF0) | (instruction_register & 0x0F);
      break;
    case 0x30:  // JCN (Jump on Condition)
      // will release
      this->pc++;
      break;
    case 0x40:  // ISZ (Increment and Skip if Zero)
    {
      uint8_t reg = instruction_register & 0x0F;
      registers[reg]++;
      if (registers[reg] == 0)
        this->pc += 2;
      else
        this->pc++;
    } break;
    case 0x50:  // ADD (Add)
      this->acc += registers[instruction_register & 0x0F];
      this->pc++;
      // set flags
      break;
    case 0xFE:  // HLT (Halt)
      this->halted = true;
      break;

    default:
      // add the interrupt
      this->pc++;
      break;
  }
}
