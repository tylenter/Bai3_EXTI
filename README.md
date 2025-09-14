CÁC BƯỚC THỰC HIỆN:
1. Cấu hình GPIO:
   - PA5: Output -> Kết nối led
   - PB0: Input ->Kết nối nút bấm


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

2. Cấu hình EXTIO:
   - Chọn PB0 làm chân ngắt ngoài EXTI0.
   - Kích hoạt ngắt cạnh Falling Edge (nhấn nút kéo xuống GND).
   - Bật NVIC cho EXTI0.


void EXTI0_Config(void)

{
    AFIO->EXTICR[0] &= ~(0xF << 0);
    AFIO->EXTICR[0] |=  (0x1 << 0);

    EXTI->IMR  |= (1 << 0);
    EXTI->FTSR |= (1 << 0);
    EXTI->RTSR &= ~(1 << 0);

    NVIC_EnableIRQ(EXTI0_IRQn);
}
  -Hàm ISR:


void EXTI0_IRQHandler(void)

{
    if(EXTI->PR & (1 << 0)) 
    {
        EXTI->PR |= (1 << 0);  
        led_enable = !led_enable; 
    }
}

3. Chương trình chính:
   - Nếu led_enable = 1: LED ở PA5 sẽ nhấp nháy 1 Hz (delay_ms 1000 ms).
   - Nếu led_enable = 0: LED luôn sáng.


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

4. Kết quả:
  - LED tại PA5:
    + Mặc định nhấp nháy 1 Hz.
    + Khi nhấn nút PB0 → đổi chế độ: luôn sáng.
    + Nhấn lại lần nữa → trở về nhấp nháy.
