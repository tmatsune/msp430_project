UART is a hardware-based serial communication protocol that transmits data bit by bit over two main lines
    - TX and RX 
    - no shares clock both devices agree on a baud rate (bits per second)
    - Data is sent one byte at a time 

## Config
    - Select a clock source for UART 
        - DCO 1MHz 
        - SMCLK as source for uart 
    - Set the baud rate 
        - 9600 
    - Enable UART pins 

**Polling:**
Put the current char into the tx buffer, wait for tx buffer to be empty. Then send the next bit continue
until you reach the null char 

**Interrupts:**
Ring Buffer (circular queue) is used to store outgoing characters 
    - tx_head where you write new data (enqueue) 
    - tx_tail where ISR reads (dequeue)
    - tx_head == tx_tail, buffer is empty
    - tx_head + 1 == tail, buffer is full 

uart_puts function 
    - adds each char into the ring buffer 
    - waits if the buffer is full (next_head = tx_tail)
    - After queuing the string, if tx-active is false 
        - sets tx_active = 1 
        - enables tx_interrupt to start sending from buffer 
ix interrupts 
    - when uart is ready to send next byte 
    - if tx_tail != tx_head 
        - sends tx_buffer[tx_tail] to UART 
        - advances tx_tail 
    - tx_tail == tx_head 
        - buffer is empty 
        - disables tx interrupt 
        = tx-active = 0 


