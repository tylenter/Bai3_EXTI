#include "stm32f10x.h"

void GPIO_Config(void);
void EXTI0_Config(void);
void delay_ms(uint16_t time);

volatile uint8_t led_enable = 1;

int main(void)
{
    GPIO_Config();    
    EXTI0_Config();   

    while(1)
    {
        if(led_enable) {
            GPIOA->ODR &= ~(1 << 5); 
            delay_ms(1000);
            GPIOA->ODR |=  (1 << 5); 
            delay_ms(1000);
        } else {
          
            GPIOA->ODR |= (1 << 5);  
        }
    }
}

void GPIO_Config(void)
{
    RCC->APB2ENR |= (1<<2) | (1<<3) | (1<<0);

    GPIOA->CRL &= ~(0xF << 20);  
    GPIOA->CRL |=  (0x3 << 20);  
    GPIOA->ODR |=  (1 << 5);     

    GPIOB->CRL &= ~(0xF << 0);   
    GPIOB->CRL |=  (0x8 << 0);   
    GPIOB->ODR |=  (1 << 0);     
}

void EXTI0_Config(void)
{
    // Ch?n PB0 cho EXTI0
    AFIO->EXTICR[0] &= ~(0xF << 0);
    AFIO->EXTICR[0] |=  (0x1 << 0);  

    EXTI->IMR  |= (1 << 0);
    EXTI->FTSR |= (1 << 0); 
    EXTI->RTSR &= ~(1 << 0);

    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0)) 
    {
        EXTI->PR |= (1 << 0); 
        led_enable = !led_enable; 
    }
}

void delay_ms(uint16_t time)
{
    int i,j;
    for(i=0; i<time; i++){
        for(j=0; j<0x2AFF; j++);
    }
}
