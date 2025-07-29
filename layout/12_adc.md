
ADC stands for Analog-to-Digital Converter. Essential component in electronics that conversts analog signals 
(continuouse signals) into digital values that a microntroller or digital system can process 
**Why:**
    - Computers can only understand digital values. Real world signals, like sounds temperature, lights, or voltage are analog 
**How it works:**
    - Analog input: continuous voltage 
    - Sampling: ADC takes a snapshot of the voltage at fixed intervals  
    - Quantization: Each sample is rounded to the nearest gidital level 
    - Digital output: The result is a binary number representing the analog value 
**Example:**
    - 10-bit ADC, can represent analog input with 2^10 = 1024 levels. 
    - 0V 0000000000, 2.5V 1000000000, 5V 1111111111 
**Config:**
    - which pin to read the analog signal from 
    - how to convert 
    - when to start the conversion 
    how to get the result (e.g. poll a flag or use an interrupt)

ADC10CTL0: ADC10 control register 0, controls ADC power, sampling, ref voltage, start conversion 
ADC10CTL1: ADC10 control register 1, controls clock source, input channel, conversoin mode 
ADC10AE0: ADC analog enable 0, enables analog input on pins 
ADC10AE1: ADC analog enable 1, Addictinoal analog input enables on some devices
ADC10MEM: Holds the latest ADC conversion result 
ADC10DTC0: Controls DTC behvior 
ADC10DTC1: DTA transfer count 
ADC10SA: DTC start address regsiter 

ADC10MEM(Memory register): This is hwere the ADC puts ints conversion result after it's done sampling 
    - If you don't use DTC, manually read ADC10MEM each time 
    - If you use DTC, DTC atumoatically copies ADC10MEM to your buffer 

ADC10DTC0: Control how the DMA-style transfer behaves 
ADC10DTC1: Set how many samples to store 
ADC10SA: Where to store the results 

DTC: Move ADC10 conversoin results directly into memory without CPU intervention 
    

  ADC10CTL1 = INCH_5 + ADC10DIV_7  ffa+ CONSEQ_1 + SHS_0 + ADC10SSEL_1;
  ADC10CTL0 = ADC10ON + SREF_0 + ADC10SHT_2 + MSC + ADC10IE;
  ADC10AE0 = BIT5 | BIT4 | BIT3 | BIT0;
  ADC10DTC0 = ADC10CT;
  ADC10DTC1 = ADC_COUNT;
  ADC10SA = (uint16_t)adc_mem;
  adc_enable_and_start_conversion();

__attribute__((interrupt(ADC10_VECTOR)))
void ADC10_ISR(void)
{
    for (uint8_t i = 0; i < ADC_COUNT; i++) {
        adc_mem_cache[i] = adc_mem[i];
    }
    printf("here\r\n");
    adc_enable_and_start_conversion();
}

/*
void adc_get_channel_values(uint16_t* values)
{
    _disable_interrupts();
    for (uint8_t i = 0; i < 4; i++) {
        values[i] = adc_mem_cache[i];  
    }
    _enable_interrupts();
}
*/
