# 8SAP_EMU

8SAP_EMU is an emulator for an 8-bit SAP (Simple-As-Possible) computer, inspired by educational architectures like the SAP-1 and SAP-2. This project aims to simulate the fundamental operations of an 8-bit microcomputer, providing a platform for learning and experimentation with basic computer architecture concepts.

## Features

- **8-bit Data Width**: Emulates an 8-bit data bus, allowing for operations on 8-bit data.
- **Custom Instruction Set**: Implements a simplified instruction set tailored for educational purposes.
- **Memory Management**: Simulates a basic memory model for instruction and data storage.
- **CPU Emulation**: Models the essential components of a CPU, including the accumulator, program counter, and instruction register.

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- **C++ Compiler**: Supports C++11 standard or higher.
- **CMake**: Version 3.10 or higher.
- **Make**: For building the project.

### Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/egrissino/8SAP_EMU.git
   cd 8SAP_EMU
   ```

2. **Configure the Build Environment**:

   ```bash
   ./configure.sh
   ```

3. **Build the Emulator**:

   ```bash
   ./make.sh
   ```

### Usage

After building the project, you can run the emulator with:

```bash
./8SAP_EMU
```

For detailed usage instructions and examples, refer to the [documentation](https://github.com/egrissino/8SAP_EMU/wiki).

## Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes. Ensure that your code adheres to the project's coding standards and includes appropriate tests.

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/egrissino/8SAP_EMU/blob/main/LICENSE) file for details.

## Acknowledgements

This emulator is inspired by the educational architectures presented in resources like the SAP-1 and SAP-2 models. Special thanks to the contributors of similar projects for their foundational work.
