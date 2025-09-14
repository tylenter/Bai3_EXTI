CÁC BƯỚC THỰC HIỆN:
1. Cấu hình GPIO:
   - PA5: Output -> Kết nối led
   - PB0: Input ->Kết nối nút bấm
<img width="717" height="252" alt="image" src="https://github.com/user-attachments/assets/b4295667-7d79-4850-ba26-48b885428e99" />


2. Cấu hình EXTIO:
   - Chọn PB0 làm chân ngắt ngoài EXTI0.
   - Kích hoạt ngắt cạnh Falling Edge (nhấn nút kéo xuống GND).
   - Bật NVIC cho EXTI0.
<img width="642" height="233" alt="image" src="https://github.com/user-attachments/assets/e8d08ad2-6263-4c6a-9779-05e1411d4b4a" />

  -Hàm ISR:
<img width="504" height="171" alt="image" src="https://github.com/user-attachments/assets/944acf8e-b8e1-4748-8cb7-ba6f0d50a1ac" />


3. Chương trình chính:
   - Nếu led_enable = 1: LED ở PA5 sẽ nhấp nháy 1 Hz (delay_ms 1000 ms).
   - Nếu led_enable = 0: LED luôn sáng.
<img width="744" height="362" alt="image" src="https://github.com/user-attachments/assets/275fc213-b38f-4ab7-b603-d16e7ccf23b3" />


4. Kết quả:
  - LED tại PA5:
    + Mặc định nhấp nháy 1 Hz.
    + Khi nhấn nút PB0 → đổi chế độ: luôn sáng.
    + Nhấn lại lần nữa → trở về nhấp nháy.
