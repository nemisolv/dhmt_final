# BÁO CÁO DỰ ÁN ROBOT 3D - OPENGL

## 1. TỔNG QUAN DỰ ÁN

### 1.1 Mục tiêu
- Xây dựng mô phỏng robot 3D sử dụng OpenGL và GLUT
- Thực hiện các phép biến đổi 3D cơ bản
- Tạo animation đi bộ tự nhiên cho robot
- Cung cấp giao diện điều khiển bằng bàn phím

### 1.2 Công nghệ sử dụng
- **OpenGL**: Thư viện đồ họa 3D
- **GLUT (FreeGLUT)**: Thư viện utility cho OpenGL
- **C++**: Ngôn ngữ lập trình chính
- **GCC/G++**: Compiler

## 2. KIẾN THỨC LÝ THUYẾT

### 2.1 OpenGL là gì?
OpenGL (Open Graphics Library) là một API đồ họa đa nền tảng để render đồ họa 2D và 3D. Nó cung cấp:
- Các hàm vẽ hình học cơ bản
- Hệ thống tọa độ 3D
- Các phép biến đổi ma trận
- Quản lý ánh sáng và texture

### 2.2 Các phép biến đổi 3D cơ bản

#### 2.2.1 Tịnh tiến (Translation)
```cpp
glTranslatef(x, y, z);
```
- Di chuyển đối tượng theo vector (x, y, z)
- Trong dự án: Di chuyển robot trong không gian 3D

#### 2.2.2 Xoay (Rotation)
```cpp
glRotatef(angle, x, y, z);
```
- Xoay đối tượng quanh trục (x, y, z) một góc angle
- Trong dự án: Xoay robot và các bộ phận

#### 2.2.3 Tỷ lệ (Scaling)
```cpp
glScalef(sx, sy, sz);
```
- Thay đổi kích thước đối tượng theo tỷ lệ (sx, sy, sz)
- Trong dự án: Tạo các bộ phận có kích thước khác nhau

### 2.3 Ma trận biến đổi
- OpenGL sử dụng ma trận 4x4 để thực hiện các phép biến đổi
- `glPushMatrix()`: Lưu trạng thái ma trận hiện tại
- `glPopMatrix()`: Khôi phục ma trận đã lưu
- Cho phép áp dụng biến đổi cục bộ cho từng bộ phận

## 3. THIẾT KẾ VÀ CÀI ĐẶT

### 3.1 Cấu trúc robot
Robot được tạo từ các hình khối cơ bản (cube):
- **Thân**: Hình hộp chữ nhật (0.8 x 1.0 x 0.4)
- **Đầu**: Hình lập phương (0.6 x 0.6 x 0.6)
- **Tay**: 2 hình hộp (0.15 x 0.6 x 0.15)
- **Chân**: 2 hình hộp (0.2 x 1.0 x 0.2)

### 3.2 Hàm vẽ hình khối
```cpp
void drawCube(float size) {
    float s = size / 2.0f;
    glBegin(GL_QUADS);
    // Vẽ 6 mặt của cube
    glEnd();
}
```

### 3.3 Hàm vẽ robot
```cpp
void drawRobot() {
    glPushMatrix();
    glTranslatef(robotX, 0.0f, robotZ);
    glRotatef(robotRotation, 0.0f, 1.0f, 0.0f);
    
    // Vẽ từng bộ phận với biến đổi riêng
    // ...
    
    glPopMatrix();
}
```

## 4. ANIMATION VÀ CHUYỂN ĐỘNG

### 4.1 Điều khiển di chuyển
```cpp
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Di chuyển tiến
            newX += moveSpeed * sin(robotRotation * M_PI / 180.0f);
            newZ -= moveSpeed * cos(robotRotation * M_PI / 180.0f);
            break;
        // ...
    }
}
```

### 4.2 Animation vung tay
- **Nguyên lý**: Tay vung ngược pha nhau khi di chuyển
- **Thực hiện**: Tăng/giảm góc xoay của tay
- **Giới hạn**: Reset về 0° khi đạt 45°

```cpp
// Vung tay khi di chuyển
leftArmAngle += 10.0f;
rightArmAngle -= 10.0f;
// Reset về 0 khi đạt 45 độ
if (leftArmAngle >= 45.0f) leftArmAngle = 0.0f;
if (rightArmAngle <= -45.0f) rightArmAngle = 0.0f;
```

## 5. CÁC BƯỚC THỰC HIỆN

### 5.1 Bước 1: Thiết lập môi trường
```bash
# Cài đặt dependencies
sudo apt-get install freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev

# Compile project
make
```

### 5.2 Bước 2: Tạo cấu trúc cơ bản
- Khởi tạo OpenGL và GLUT
- Thiết lập window và callback functions
- Tạo hàm vẽ hình khối cơ bản

### 5.3 Bước 3: Xây dựng robot
- Vẽ từng bộ phận với kích thước và vị trí phù hợp
- Sử dụng các phép biến đổi để tạo hình dạng
- Áp dụng màu sắc cho từng bộ phận

### 5.4 Bước 4: Thêm chuyển động
- Cài đặt điều khiển bằng bàn phím
- Thêm logic di chuyển và xoay
- Tạo animation cho tay

### 5.5 Bước 5: Hoàn thiện
- Thêm mặt đất và môi trường
- Tối ưu hóa hiệu suất
- Kiểm tra và sửa lỗi

## 6. CÁC CÂU HỎI THƯỜNG GẶP

### 6.1 Về OpenGL
**Q: Tại sao sử dụng OpenGL thay vì thư viện khác?**
A: OpenGL là thư viện đồ họa 3D chuẩn, đa nền tảng, có hiệu suất cao và được hỗ trợ rộng rãi.

**Q: Sự khác biệt giữa OpenGL và DirectX?**
A: OpenGL là API mở, đa nền tảng; DirectX chỉ chạy trên Windows.

### 6.2 Về các phép biến đổi
**Q: Tại sao cần sử dụng glPushMatrix() và glPopMatrix()?**
A: Để quản lý ma trận biến đổi, tránh ảnh hưởng đến các đối tượng khác.

**Q: Thứ tự thực hiện các phép biến đổi có quan trọng không?**
A: Có, thứ tự ảnh hưởng đến kết quả cuối cùng (không giao hoán).

### 6.3 Về animation
**Q: Làm thế nào để tạo animation mượt mà?**
A: Sử dụng hàm sin/cos để tạo chuyển động tuần hoàn, cập nhật liên tục.

**Q: Tại sao tay vung ngược pha nhau?**
A: Mô phỏng chuyển động đi bộ tự nhiên của con người.

## 7. KHÓ KHĂN VÀ GIẢI PHÁP

### 7.1 Khó khăn gặp phải
1. **Hiểu về hệ tọa độ 3D**: Phức tạp với người mới học
2. **Quản lý ma trận biến đổi**: Dễ gây nhầm lẫn
3. **Tối ưu hiệu suất**: Render liên tục có thể chậm

### 7.2 Giải pháp
1. **Học từ đơn giản**: Bắt đầu với 2D trước khi chuyển sang 3D
2. **Sử dụng debug**: In ra các giá trị để kiểm tra
3. **Tối ưu code**: Chỉ vẽ những gì cần thiết

## 8. KẾT LUẬN

### 8.1 Kết quả đạt được
- Tạo thành công robot 3D với animation
- Thực hiện đầy đủ các phép biến đổi 3D
- Giao diện điều khiển thân thiện
- Code có cấu trúc rõ ràng, dễ hiểu

### 8.2 Kiến thức thu được
- Hiểu về OpenGL và đồ họa 3D
- Thành thạo các phép biến đổi ma trận
- Kỹ năng lập trình animation
- Khả năng debug và tối ưu code

### 8.3 Hướng phát triển
- Thêm texture và lighting
- Tạo nhiều robot và tương tác
- Thêm âm thanh và hiệu ứng
- Phát triển thành game 3D

## 9. TÀI LIỆU THAM KHẢO
- OpenGL Programming Guide (Red Book)
- GLUT Documentation
- C++ Programming Tutorials
- Computer Graphics Principles and Practice

## 10. PHỤ LỤC

### 10.1 Cấu trúc file
```
robot/
├── main.cpp            # Source code chính
├── Makefile            # Build script
├── README.md           # Hướng dẫn sử dụng
└── robot3d             # Executable
```

### 10.2 Các lệnh quan trọng
```bash
make install-deps    # Cài đặt dependencies
make                # Compile project
make run            # Chạy chương trình
make clean          # Xóa file build
```

### 10.3 Điều khiển
- **↑/↓**: Di chuyển tiến/lùi
- **←/→**: Xoay trái/phải
- **ESC**: Thoát chương trình 