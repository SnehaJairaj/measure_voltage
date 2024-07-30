#include <xc.h>

#define _XTAL_FREQ 20000000  
#define VREF 5.0  
#define ADC_MAX 1023 

// Function to initialize the ADC
void ADC_Init() {
    ADCON0 = 0x01;  // Enable ADC, select channel 0 (default)
    ADCON1 = 0x80;  // Configure ADC
}

// Function to read ADC value from a specified channel
unsigned int ADC_Read(unsigned char channel) {
    if (channel > 7) return 0;  // ADC has 8 channels 
    ADCON0 &= 0xC5;  // Clear the channel selection bits
    ADCON0 |= channel << 3;  // Set the new channel
    __delay_ms(2);  // Acquisition time 
    ADCON0bits.GO_nDONE = 1;  
    while (ADCON0bits.GO_nDONE);  
    return (ADRESH << 8) | ADRESL;  
}

// Function to convert ADC value to vg
float ADC_to_voltage(unsigned int adcValue) {
    return (adcValue * VREF) / ADC_MAX;
}

// Main function
void main() {
    unsigned int adc_value;
    float voltage;

    TRISA = 0xFF;  // Configure PORTA 
    ADC_Init();  // Initialize the ADC

    while (1) {
        adc_value = ADC_Read(0);  // Read ADC value from channel 0
        voltage = ADC_to_voltage(adc_value);  // Convert ADC value to voltage

       
        __delay_ms(500);  // Delay for a while
    }
}
