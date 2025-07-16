#ifndef IR_REMOTE_H 
#define IR_REMOTE_H

typedef enum
{
    IR_CMD_0 = 0x98,
    IR_CMD_1 = 0xA2,
    IR_CMD_2 = 0x62,
    IR_CMD_3 = 0xE2,
    IR_CMD_4 = 0x22,
    IR_CMD_5 = 0x02,
    IR_CMD_6 = 0xC2,
    IR_CMD_7 = 0xE0,
    IR_CMD_8 = 0xA8,
    IR_CMD_9 = 0x90,
    IR_CMD_STAR = 0x68,
    IR_CMD_HASH = 0xB0,
    IR_CMD_UP = 0x18,
    IR_CMD_DOWN = 0x4A,
    IR_CMD_LEFT = 0x10,
    IR_CMD_RIGHT = 0x5A,
    IR_CMD_OK = 0x38,
    IR_CMD_NONE = 0xFF
} ir_command_e;

void ir_remote_init(void);
ir_command_e ir_remote_get_cmd(void);

const char *ir_remote_cmd_to_string(ir_cmd_e cmd);

/*
  High-Level Flow 
  - ir_remote_init() is called once 
  - IR pin interrupt fires -> isr_pulse() runs 
  - timer tracks time between edges 
  - bits are decoded and shifted into a 32-bit number 
  - when full message is received -> cmd byte is stored in ring buffer 
  - app calls ir_remote_get_cmd() to read it 
*/

/*
  Purpose: 
    - Receives commands from an IR remote, decodes the pulses, and stores the command in a buffer for later use 
  Basic Components: 
    - IR receiver pin: Detects rising edge pulses from the remote
    - Timer: Measures the time between each pulse 
    - Pulse Counter: Tracks which pulse we are on 
    - Ring Buffer: Stores the decoded command 
    - state machine: figures out if each pulse is valid and whether it represents a binary 1 or 0
  Timer Setup: 
    - sets up Timer A1 to fire an interrupt every 1ms 
  Start and Stop Timer: 
    - Starts the timer in count-up mode. Also resets the timer 
  How IR Decoding Works 
    - Each pulse from the IR remote causes an inerrupt. The time between pulses (in ms) is used to determine
      whether it's a 1 or 0 
    - short delay means a binary of 0 
    - longer delay means a binary of 1 
  ISR isr_pulse()
    - this is called every time rising edge happens (a pulse from the remote)
      - stop the timer 
      - inc pulse_count 
      - check is pulse is valid 
        - if not valuie, assume this is a new message 
        - if vlaid and between 3 & 34, record a bit 
          - timer_ms >= 2 means it's a binary 1 
          - else it's a binary 0 
      - check if the message is complete (pulse 34 or greater)
        - if yes, store the command byte in the ring buffer 
      - restart the timer for the next pulse 
  Timer A0 ISR isr_timer_a0()
    - fires every 1ms while the timer is running 
      - inc timer_ms 
      - if nothing happens for TIMER_TIMEOUT_ms (150 ms) reset
        - pulse_count, ir_message, and timer_ms 
  Decoding Validity Functions 
  Buffer for commands 
    - holds up to 10 decoded command bytes 
  Read decoded command 
    - called from main 

*/

#endif 
