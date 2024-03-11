# Advanced C/C++
**Lesson: Memory Layout**

Memory layout của một chương trình C bao gồm 5 phần:

Text segment  (i.e. instructions)

Initialized data segment 

Uninitialized data segment  (bss) 

Heap 

Stack


<img src="https://media.geeksforgeeks.org/wp-content/uploads/memoryLayoutC.jpg">

**Text Segment (Code Segment):** Là khu vực bộ nhớ chứa mã máy của chương trình sau khi được biên dịch. Đây là phần chứa các lệnh và hàm thực thi của chương trình. Khu vực này thường được đánh dấu là chỉ đọc để ngăn chặn việc sửa đổi mã thực thi.

**Initialized Data Segment (DS):** chứa các biến toàn cục và biến static đã được khởi tạo với giá trị khác 0.
- Ví dụ:
```c
int global = 100; //global được khởi tạo với giá trị 100
int foo() {
    static int number = 10; //biến static number được khởi với giá trị 10
    return 0;
}
```
**Uninitialized Data Segment (BSS):** là nơi lưu trữ global variables, static variables không được khởi tạo hoặc khởi tạo với giá trị bằng 0.
- Ví dụ:
```c
int global; //không được khởi tạo giá trị 
int foo() {
    static int number = 0; //biến static number được khởi tạo với giá trị bằng 0
    return 0;
}
```
**Heap (Dynamic Memory Allocation):** Trong C/C++ chúng ta có thể hoàn toàn control được quá trình cấp phát hoặc giải phóng bộ nhớ bằng các lệnh như malloc, calloc, relloc, free, new, delete, ... Vùng nhớ được cấp phát chính là HEAP, vùng nhớ này sẽ phình lên ( grows upward ) mỗi khi bạn cấp phát. Khi sử dụng xong các bạn phải delete vùng nhớ này. Nếu quên không delete sẽ gây ra hiện tượng Memory Leak.
- Ví dụ:
```c
#include <stdio.h>
#include <stdlib.h>

struct MyClass {
  int data[100];
};

void MyClass_construct(struct MyClass* obj) {
  printf("constructed [%p]\n", obj);
}

int main() {
  printf("1: ");
  struct MyClass* p1 = (struct MyClass*)malloc(sizeof(struct MyClass));
  MyClass_construct(p1);
  free(p1);
  return 0;
}
```

**Stack (Automatic Variable Storage):** Khác với HEAP, Stack là một vùng nhớ được cấp phát tự động và có cấu trúc LIFO. 
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20231130114919/LIFO-Operations-in-stack.jpg">

Mỗi khi chương trình được gọi, thì các function frame sẽ được gọi và push vào trong stack. Function Frame có cấu trúc như ví dụ dưới đây:
- Ví dụ:
```c
#include <stdio.h>

// Định nghĩa hàm add
int add(int a, int b) {
    return a + b; // Tính tổng của a và b, sau đó trả về kết quả
}

int main() {
    int result;
    result = add(5, 3); // Gọi hàm add với 5 và 3 là đối số

    printf("The result is: %d\n", result); // In ra kết quả
    return 0;
}
```
```c
[Trước khi gọi add]
   +-----------------+
   | main's frame    |
   | - result (??)   | <- Top of Stack
   +-----------------+

[Gọi add(5, 3)]
   +-----------------+
   | add's frame     |
   | - Return Addr   |
   | - Parameters    |
   |   a = 5         |
   |   b = 3         | <- Top of Stack
   +-----------------+
   | main's frame    |
   | - result (??)   |
   +-----------------+

[Sau khi add trả về giá trị 8]
   +-----------------+
   | main's frame    |
   | - result (8)    | <- Top of Stack
   +-----------------+

```
Trước khi gọi add: Stack chứa chỉ frame của main, với biến result chưa được khởi tạo.

Khi gọi add(5, 3): Stack giờ đây có thêm frame cho add ở đỉnh. Frame này chứa địa chỉ trở về (nơi trong main mà sau khi add thực thi xong sẽ trở về), và tham số cho add là a = 5 và b = 3.

Sau khi add trả về giá trị 8 và frame của add được loại bỏ: Giá trị trả về được gán cho result trong frame của main. Stack trở lại như ban đầu nhưng với result đã được cập nhật.

Hình ảnh này giúp minh họa cách mà stack quản lý việc gọi và trở về từ các hàm, thông qua việc sử dụng các stack frames. Mỗi frame chứa tất cả thông tin cần thiết cho việc thực thi của một hàm, bao gồm địa chỉ trở về, tham số, và biến cục bộ, giúp cho việc thực thi hàm được tổ chức và cô lập một cách rõ ràng.

**Cấu trúc của một function frame gồm bốn phần chính: Function Parameter, Return Address, Saved Previus Frame Pointer, Local Variable.**

- Funtion Parameter là các tham số truyền vào.
- Return Address trong ví dụ trên, Return Address trả về địa chỉ p trong hàm main() chính là Local Variable.
- Saved Previus Frame Pointer trỏ vào vị trí đầu tiên của function foo() tức là kết thúc của function main()
- Local Variable là các biến local của function
Lưu ý: Nếu chúng ta sử dụng hết vùng nhớ của Stack thì sẽ có một lỗi rất kinh điển đó là Stack OverFlow xảy ra.



