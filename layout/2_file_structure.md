
A clean embedded project file structure helps you organize your code by responsibility and dependency.


project/
├── Makefile
├── build/              # Build output (object files, ELF, etc.)
│
├── src/                # Application code
│   ├── main.c
│   ├── state_machine.c
│   ├── state_machine.h
│   ├── enemy.c
│   ├── enemy.h
│   └── ...
├── drivers/            # Hardware-specific drivers
│   ├── uart.c
│   ├── uart.h
│   ├── pwm.c
│   ├── pwm.h
│   ├── io.c
│   ├── io.h
│   └── ...
├── include/            # Shared headers (optional)
│   └── config.h
│
└── libs/               # External libraries (e.g., lightweight printf)
    └── printf/
        ├── printf.c
        └── printf.h
