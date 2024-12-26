
<div class="image-container" style="display: flex; flex-direction: row; justify-content: space-around; align-items: center;">
    <img src="https://github.com/user-attachments/assets/5e8145f7-8661-47fa-9212-7fe42bb13114" style="max-width: 45%; height: auto;" alt="i4004 Scheme">
    <img src="https://github.com/user-attachments/assets/22305a9b-a2a8-4c75-ac83-772ca9a1f2dd" style="max-width: 45%; height: auto;" alt="i4004 Chip">
</div>


---

# i4004 Virtual Machine

This project is a virtual machine emulator for the Intel 4004 microprocessor, the world's first commercially available microprocessor. The emulator is implemented in C++20 and aims to accurately replicate the behavior and architecture of the original Intel 4004.

## Table of Contents

- [Introduction](#introduction)
- [Technical Specifications](#technical-specifications)
- [Instruction Set Architecture (ISA)](#instruction-set-architecture-isa)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Intel 4004 was introduced on November 15, 1971, and was a groundbreaking innovation in the field of microprocessors. It was designed for use in calculators and other simple computing devices. This virtual machine emulator allows you to run and test programs written for the Intel 4004, providing an educational and historical insight into early microprocessor technology.

## Technical Specifications

- **Release Date**: November 15, 1971
- **Transistor Count**: 2300
- **Die Size**: 12 mm²
- **Process Technology**: 10 µm (P-channel silicon gate MOS technology)
- **Clock Speed**: 740 kHz reference (92.6 kHz clock, 8 cycles per instruction)
- **Register Width**: 4 bits
- **Register Count**: 16 (16 four-bit registers can be used as 8 eight-bit registers)
- **Ports**: 16 four-bit input/output ports (in the program area) and 32 four-bit output ports (in the data area)
- **Internal Bus**: 4 bits
- **External Bus**: Multiplexed for address, data, and control — 4 bits (plus 5 CM bank selection lines)
- **Architecture**: Harvard architecture
- **Stack**: Internal 3-level stack
- **Program Memory (ROM/RAM)**: 4 KB (32768 bits)
- **Data Memory (RAM)**: 640 bytes (5120 bits) without address decoder, or 1280 bytes (10240 bits) with address decoder
- **Address Space Organization**:
  - Program area: 1 bank, 12-bit address, 8-bit data
  - Data register area: 8 banks (3 bits), 8-bit address, 4-bit data
  - Status register area: 8 banks (3 bits), 4-bit address, 4-bit data
  - Input/output area (in the program bank): 1 bank, 4-bit address, 4-bit data
  - Output area (in the data banks): 8 banks (3 bits), 4-bit address, 4-bit data
- **Instruction Set**: 46 instructions (41 8-bit and 5 16-bit)
- **Instruction Cycle**: 10.8 microseconds
- **Power Supply**: -15 V (pMOS)
- **Operating Temperature**: 0 to +70 °C
- **Storage and Operation Temperature**: -40 to +85 °C
- **Package**: 16-pin DIP (directly soldered to the PCB or placed in a special slot)
- **Delivery Type**: Individual or as part of the MCS-4 set (ROM, RAM, I/O, CPU)

## Instruction Set Architecture (ISA)

The Intel 4004 has a complex instruction set architecture (ISA) that requires multiple bytes to encode the instruction’s opcode, operands, and addressing modes. Below is a table of the opcodes and their technical details.

### Opcodes and Descriptions

[intel-4004.pdf](https://github.com/user-attachments/files/18255967/intel-4004.pdf)

### Instruction Details

#### NOP (0x00)
- **Description**: No Operation. The processor does nothing for one instruction cycle.
- **Length**: 1 byte

#### HLT (0xFE)
- **Description**: Halt. Halts the processor.
- **Length**: 1 byte

## Features

- **Accurate Emulation**: Faithfully replicates the behavior of the Intel 4004 microprocessor.
- **Two-Phase Clock**: Implements the two-phase clock mechanism (Ph1 and Ph2) used by the Intel 4004.
- **Instruction Set**: Supports the full instruction set of the Intel 4004, including multi-byte instructions.
- **Stack Management**: Implements the 3-level stack with 12-bit stack level registers.
- **Detailed State Output**: Provides detailed output of the CPU state, including registers, program counter, and stack pointer.

## Installation

To build and run the emulator, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/akira-arch/i4004.git
   cd i4004/src
   ```

2. Compile the project:
   ```sh
   g++ @ld
   ```

3. Run the emulator:
   ```sh
   ./vm
   ```

## Usage

1. **Load a Program**: Use the `load_program` method to load a program into the ROM.
   ```cpp
   std::vector<uint8_t> program = {
      0x00,        // NOP
      0xD0, 0x04,  // LDM 4
      0xFE         // HLT
   };
   vm.load_program(program);
   ```

2. **Run the Program**: Use the `run` method to execute the loaded program.
   ```cpp
   vm.run();
   ```

3. **Print State**: Use the `print_state` method to print the current state of the CPU.
   ```cpp
   vm.print_state();
   ```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
