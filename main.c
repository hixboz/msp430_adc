


#include <msp430.h>
#include <stdint.h>

volatile uint16_t adc_values[8];
volatile uint8_t adc_index = 0;

void led_config();
void led_on();
void led_off();


void main(void) {
    // D���k frekans ayar�
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    //led_config();

    // P9 pins as ADC
    P9SEL0 |= 0xFF;
    P9SEL1 |= 0xFF;

    while(REFCTL0 &REFGENBUSY);
     REFCTL0 |= REFVSEL_1 | REFON;
     __delay_cycles(75);
     REFCTL0 |= REFOUT;
     while(!(REFCTL0 &REFGENRDY));


    ADC12CTL0 = ADC12SHT0_2 | ADC12MSC | ADC12ON;
    ADC12CTL1 = ADC12SHP | ADC12CONSEQ_3;
    ADC12CTL2 = ADC12RES_2; // 12-bit conversion results
    ADC12CTL3 = ADC12CSTARTADD_0;
    ADC12MCTL0 |= ADC12INCH_8 | ADC12VRSEL_1 ;
    ADC12MCTL1 |= ADC12INCH_9 | ADC12VRSEL_1;
    ADC12MCTL2 |= ADC12INCH_10 | ADC12VRSEL_1 ;
    ADC12MCTL3 |= ADC12INCH_11 | ADC12VRSEL_1 ;
    ADC12MCTL4 |= ADC12INCH_12 | ADC12VRSEL_1 ;
    ADC12MCTL5 |= ADC12INCH_13 | ADC12VRSEL_1 ;
    ADC12MCTL6 |= ADC12INCH_14 | ADC12VRSEL_1 ;
    ADC12MCTL7 |= ADC12INCH_15 | ADC12VRSEL_1 | ADC12EOS;



    ADC12IER0 |= ADC12IE7;
    //ADC12IER0 |= ADC12IE0 | ADC12IE1 | ADC12IE2 | ADC12IE3 | ADC12IE4 | ADC12IE5 | ADC12IE6 | ADC12IE7 ;
    ADC12CTL0 |= ADC12ENC;




   // led_on();

    while(1) {
        ADC12CTL0 |= ADC12SC | ADC12ENC;   // ADC �rnekleme ve d�n���m� ba�lat
        //__delay_cycles(2000);
       __bis_SR_register(LPM0_bits | GIE);

    }
}

void led_on(){
    P1OUT |= BIT0;
}

void led_off(){
    P1OUT &= ~(BIT0);
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC_ISR(void) {
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
    {
//        case ADC12IV_ADC12IFG0:
//            adc_values[0] = ADC12MEM0;
//            break;
//        case ADC12IV_ADC12IFG1:
//            adc_values[1] = ADC12MEM1;
//            break;
//        case ADC12IV_ADC12IFG2:
//            adc_values[2] = ADC12MEM2;
//            break;
//        case ADC12IV_ADC12IFG3:
//            adc_values[3] = ADC12MEM3;
//            break;
//        case ADC12IV_ADC12IFG4:
//            adc_values[4] = ADC12MEM4;
//            break;
//        case ADC12IV_ADC12IFG5:
//            adc_values[5] = ADC12MEM5;
//            break;
//        case ADC12IV_ADC12IFG6:
//            adc_values[6] = ADC12MEM6;
//            break;
        case ADC12IV_ADC12IFG7:
            adc_values[0] = ADC12MEM0;
            adc_values[1] = ADC12MEM1;
            adc_values[2] = ADC12MEM2;
            adc_values[3] = ADC12MEM3;
            adc_values[4] = ADC12MEM4;
            adc_values[5] = ADC12MEM5;
            adc_values[6] = ADC12MEM6;
            adc_values[7] = ADC12MEM7;
            __bic_SR_register_on_exit(LPM0_bits);
            break;

    }
}


void led_config(){
    P1DIR |= BIT0;
    P1OUT &= ~(BIT0);
}
