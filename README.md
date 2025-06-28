# Robot 3D - Mini Project OpenGL

## Mô tả
Đây là một mini project mô phỏng robot 3D sử dụng OpenGL và GLUT. Robot có thể di chuyển, xoay và có animation đi bộ với các phép biến đổi 3D.

## Tính năng
- **Hiển thị robot 3D** với các bộ phận: đầu, thân, tay, chân, mắt
- **Phép biến đổi 3D**: Tịnh tiến (translation) và xoay (rotation)
- **Animation đi bộ**: Chân và tay di chuyển khi robot đi
- **Điều khiển bằng bàn phím**: W/A/S/D hoặc arrow keys
- **Ánh sáng 3D**: Lighting và shading
- **Camera 3D**: Góc nhìn từ trên xuống

## Cài đặt

### 1. Cài đặt dependencies
```bash
make install-deps
```

### 2. Compile project
```bash
make
```

### 3. Chạy chương trình
```bash
make run
```

## Điều khiển
- **W** hoặc **↑** - Di chuyển tiến
- **S** hoặc **↓** - Di chuyển lùi  
- **A** hoặc **←** - Xoay trái
- **D** hoặc **→** - Xoay phải
- **ESC** - Thoát

## Cấu trúc code

### Các phép biến đổi 3D được sử dụng:
1. **glTranslatef()** - Tịnh tiến robot trong không gian 3D
2. **glRotatef()** - Xoay robot và các bộ phận
3. **glScalef()** - Thay đổi kích thước các bộ phận
4. **glPushMatrix()/glPopMatrix()** - Quản lý ma trận biến đổi

### Animation đi bộ:
- Sử dụng hàm sin() để tạo chuyển động mượt mà
- Chân và tay di chuyển ngược pha nhau
- Animation chỉ hoạt động khi robot đang di chuyển

## Yêu cầu hệ thống
- Ubuntu Linux
- OpenGL
- GLUT (FreeGLUT)
- GCC/G++ compiler

## Troubleshooting

### Lỗi "glutInit not found":
```bash
sudo apt-get install freeglut3-dev
```

### Lỗi "GL/glut.h not found":
```bash
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
```

### Lỗi display:
Nếu gặp lỗi display, thử chạy với:
```bash
DISPLAY=:0 ./robot3d
```

## Tác giả
Mini Project OpenGL - Robot 3D Simulation 