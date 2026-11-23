# tm4c-uart-cmd-line-shell

A bare-metal command-line shell for the **TI EK-TM4C123GXL** LaunchPad (TM4C123GH6PM, Cortex-M4F). It runs over UART0 and has no vendor SDK or libc, only a custom startup file and linker script.

## Features

- **Interactive shell over UART** with a prompt, line editing (backspace) and echo, at 115200 baud, 8N1.
- **Command parsing** that splits each line into arguments and reports errors for bad input.
- **Built-in commands:**

  | Command | Description |
  |---|---|
  | `help [command]` | List all commands, or show help for one |
  | `info` | Show board, MCU, UART and firmware details |
  | `led <red\|green\|blue> <on\|off>` | Control the onboard RGB LED |
  | `button` | Report the state of SW1 and SW2 |
  | `uptime` | Show time elapsed since boot (SysTick-based) |
  | `reboot` | Reset the MCU |

- **Host-side tests** for the argument tokenizer, which build and run on a PC.

## Project layout

```
src/
  main.c            entry point
  startup.c         vector table and reset handler
  board/            board-level init
  drivers/          UART, LED, buttons, SysTick
  shell/            line reader, tokenizer, command table
inc/                device register definitions
Makefile            build and flash rules
linker.ld           memory map
test/               host-side parser test
```

## Requirements

- `arm-none-eabi-gcc` toolchain (GCC, binutils and `size`)
- `make`
- `openocd`, for flashing over the board's on-board ICDI debugger
- A serial terminal such as `picocom`, `minicom` or `screen`

On Debian/Ubuntu:

```sh
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi make openocd picocom
```

## Build

```sh
make          # builds build/firmware.elf
make bin      # also produces build/firmware.bin
make size     # prints the memory footprint
make clean    # removes the build directory
```

## Flash

Connect the LaunchPad to your PC through the **DEBUG** USB port, then run:

```sh
make flash
```

This calls OpenOCD with the `ti_ek-tm4c123gxl` board config. It programs and verifies the ELF, then resets the board.

## Use

The on-board debugger also exposes a virtual serial port, usually `/dev/ttyACM0` on Linux. Open it at 115200 baud:

```sh
picocom -b 115200 /dev/ttyACM0
```

Then type `help` at the prompt:

```
> led green on
OK
> uptime
```

## Host tests

The tokenizer test is plain C and needs no hardware:

```sh
gcc -Isrc/shell test/test_shell_parser.c src/shell/shell_parser.c -o /tmp/test_parser && /tmp/test_parser
```

## License

See [LICENSE](LICENSE).
