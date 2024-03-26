# Advanced C/C++
## **Lesson: Memory Layout**
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

## **Lesson: Storage Classes Extern - Static - Volatile - Register**
**Extern:** Mục đích của `extern` là để báo cho trình biên dịch biết rằng biến hoặc hàm đó sẽ được định nghĩa ở một nơi khác trong chương trình hoặc trong các file nguồn khác. Điều này cho phép các file nguồn khác nhau trong cùng một chương trình chia sẻ và sử dụng các biến và hàm mà không cần phải định nghĩa lại chúng.
- Ví dụ

File_1
```c
#include<stdio.h>

int counter = 0; // Khai báo và khởi tạo biến

void incrementCounter() {
    counter++; // Hàm tăng giá trị của biến
    printf("Counter in file1.c: %d\n", counter);
}
```
File_2
```c
#include<stdio.h>

extern int counter; // Sử dụng extern để khai báo biến từ file khác
extern void incrementCounter(); // Khai báo hàm từ file khác

int main() {
    printf("Counter in file2.c before increment: %d\n", counter);
    incrementCounter(); // Gọi hàm tăng giá trị của biến
    printf("Counter in file2.c after increment: %d\n", counter);
    return 0;
}
```
File_1 chứa định nghĩa và khởi tạo của biến `counter`, định nghĩa hàm `incrementCounter()` để tăng giá trị của biến.
File_2 sử dụng `extern` để khai báo biến `counter` và hàm `incrementCounter()` mà không cần khởi tạo hoặc định nghĩa lại chúng. Điều này cho phép File_2 truy cập và sử dụng biến và hàm được định nghĩa trong File_1.
Khi chương trình được biên dịch và chạy, hàm `main()` trong File_2 sẽ hiển thị giá trị của `counter` trước và sau khi gọi hàm `incrementCounter()`, thể hiện rằng biến `counter` được chia sẻ giữa hai file.

**Static:**

- Phạm Vi Truy Cập (Scope)
Biến Cục Bộ: Chỉ có thể truy cập được trong block hoặc hàm mà nó được khai báo. Nó không thể được truy cập bởi các hàm hoặc block khác.
Biến Toàn Cục: Có thể được truy cập từ bất kỳ đâu trong chương trình, bao gồm tất cả các hàm và block.
- Tuổi Thọ (Lifetime)
Biến Cục Bộ: Biến cục bộ sẽ được tạo mới và mất đi sau khi hàm kết thúc.
Biến Toàn Cục: Biến toàn cục tồn tại suốt vòng đời của chương trình.
- Vị Trí Lưu Trữ (Storage Location)
Biến Cục Bộ: Thường được lưu trữ trên stack, điều này giúp việc tạo mới và thu hồi bộ nhớ diễn ra nhanh chóng.
Biến Toàn Cục: Được lưu trữ trong một phần vùng nhớ cố định (Data or BSS), nên giá trị của chúng được giữ nguyên trong suốt thời gian thực thi của chương trình.
- Khởi Tạo Mặc Định
Biến Cục Bộ: Không được tự động khởi tạo với một giá trị mặc định; giá trị của chúng là không xác định nếu không được khởi tạo rõ ràng.
Biến Toàn Cục: Được tự động khởi tạo với giá trị mặc định (ví dụ, 0 cho kiểu số nguyên, NULL cho con trỏ) nếu không có giá trị khởi tạo được cung cấp.

- Ví dụ
```c
#include <stdio.h>

int globalVar = 10; // Biến toàn cục

void demoFunction() {
    int localVar = 5; // Biến cục bộ
    printf("Local Var: %d, Global Var: %d\n", localVar, globalVar);
    localVar++;
    globalVar++;
}

int main() {
    demoFunction(); // Local Var: 5, Global Var: 10
    demoFunction(); // Local Var: 5, Global Var: 11
    printf("Final Global Var: %d\n", globalVar); // Final Global Var: 12
    return 0;
}
```
```c
Local Var: 5, Global Var: 10
Local Var: 5, Global Var: 11
Final Global Var: 12
```
- Satic local variables: khi khai báo local variable với static `static int a` thì biến a nằm ở phân vùng BSS or Data tùy thuộc vào giá trị khai báo và biến a sẽ được thu hồi khi kết thúc chương trình, nếu khai báo ở dang `int a` thì biến a sẽ nằm ở phân vùng stack và sẽ được thu hồi khi kết thúc hàm.
- Ví dụ:
```c
#include <stdio.h>

// Biến toàn cục
int globalVar = 10;

void demoFunction() {
    // Biến cục bộ static
    static int staticVar = 0;
    staticVar++;
    printf("Static Var: %d, Global Var: %d\n", staticVar, globalVar);
}

int main() {
    printf("Global Var at start: %d\n", globalVar);
    demoFunction(); // In ra: Static Var: 1, Global Var: 10
    demoFunction(); // In ra: Static Var: 2, Global Var: 10
    // Thay đổi giá trị của biến toàn cục
    globalVar = 20;
    demoFunction(); // In ra: Static Var: 3, Global Var: 20
    printf("Global Var at end: %d\n", globalVar);
    return 0;
}
```
```c
Global Var at start: 10
Static Var: 1, Global Var: 10
Static Var: 2, Global Var: 10
Static Var: 3, Global Var: 20
Global Var at end: 20
```

- Static global variables:
Khi biến toàn cục được khai báo với từ khóa static thì chỉ có thể truy cập trong tệp nguồn (source file) mà nó được khai báo. Điều này giúp giới hạn phạm vi truy cập của biến, ngăn chặn các tệp nguồn khác từ việc trực tiếp truy cập hoặc thay đổi giá trị của nó. Đây là một phương tiện để ẩn thông tin và giảm sự phụ thuộc giữa các phần khác nhau của chương trình. Do được khai báo với static, giá trị của biến sẽ được khởi tạo một lần duy nhất và giữ nguyên giá trị giữa các lần gọi hàm hoặc thậm chí giữa các lần chạy chương trình khác nhau, nếu biến được khởi tạo với một giá trị cụ thể trong mã. Các biến toàn cục static được khởi tạo tự động với giá trị mặc định là 0 (đối với các kiểu số), NULL (đối với con trỏ), hoặc {0} (đối với các kiểu dữ liệu tổng hợp như mảng hoặc struct). Cũng có thể khởi tạo chúng một cách rõ ràng với giá trị khác khi khai báo. 


## **Lesson: Linked list**

Linked list bao gồm một chuỗi các "nút" (nodes), mỗi nút chứa một giá trị dữ liệu và một con trỏ (pointer) đến nút tiếp theo trong chuỗi.

<img src="https://images.viblo.asia/e531ddbd-d7e8-433a-8b89-84ad477e22d5.png">

```c
typedef struct node{
    int value;
    struct node *next;
}node;

```
`value`: đây là giá trị của node.

`struct node *next;`: Một con trỏ trỏ đến một struct node khác, cho phép liên kết các node với nhau thành một chuỗi hoặc danh sách.

- Khởi tạo các node dựa trên cấp phát tĩnh trên stack:
```c
node node1, node2, node3;
node1.value = 1;
node2.value = 2;
node3.value = 3;

node1.next = &node2; // Node 1 trỏ tới Node 2
node2.next = &node3; // Node 2 trỏ tới Node 3
node3.next = NULL;   // Node 3 là node cuối, nên nó trỏ tới NULL
```
- Khởi tạo các node dùng cấp phát động trên heap:
```c
node *createnode(int value){
    node *newnode = (node*)malloc(sizeof(node)); //cấp phát bộ nhớ cho node mới
    newnode->value = value; //gán giá trị
    newnode->next = NULL; //gán giá trị

    return newnode; //trả về con trỏ trỏ đến node mới
}
```

## **Lesson: Stack - Queue**
Stack là một data structure giúp lưu trữ, quản lý dữ liệu theo cơ chế LIFO (Last In, First Out). Stack cho phép hai thao tác cơ bản: **push (đẩy một phần tử vào ngăn xếp)** và **pop (lấy một phần tử ra khỏi ngăn xếp)**. Ngoài ra, thường còn có các thao tác khác như **peek (xem giá trị phần tử đầu ngăn xếp mà không loại bỏ nó)** và **isEmpty (kiểm tra xem ngăn xếp có trống không)**.
<img src="https://www.tutorialspoint.com/data_structures_algorithms/images/stack_representation.jpg">
- Ví dụ:
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int top; //giá trị trên cùng
    int *items; //đây là con trỏ nhưng sau khi được cấp phát động thì items này sẽ thành mảng
    int size; // kích thước của stack
} Stack;

void initialize(Stack *stack, int size){
    stack->top = -1;
    stack->items = malloc(sizeof(int) * size); //sizeof(int) * size (dấu * là phép nhân)
    stack->size = size;
}

int is_full(Stack stack){    //vì k thay đổi giá trị của stack nên chỉ truyền vào giá trị không truyền vào con trỏ
    return stack.top == stack.size -1; //vd: push 5 giá trị thì top là 4 = với size là 4 nên sẽ là truê
}

int is_empty(Stack stack){
    return stack.top == -1;
}

void push(Stack *stack, int value){
    if (!is_full(*stack))
    {
        stack->items[++stack->top] = value; //=> item[0] = 1
    }
    else{
        printf("stack overflow\n");
    }
}

int pop(Stack *stack){
    if(!is_empty(*stack)){
       return stack->items[stack->top--];
    }
    else{
        printf("stack underflow\n");
        return -1;
    }
}

int top(Stack stack){
    if(!is_empty(stack)){
        return stack.items[stack.top];
    }
    else{
        printf("stack is empty\n");
        return -1;
    }
}

int main(){
    Stack mystack;
    initialize(&mystack, 5);

    push(&mystack, 10);
    push(&mystack, 20);
    push(&mystack, 30);
    push(&mystack, 40);
    push(&mystack, 50);

    printf("top element: %d\n",top(mystack));
    push(&mystack, 60);
    printf("pop element: %d\n",pop(&mystack));
    printf("top element: %d\n",top(mystack));
    printf("pop element: %d\n",pop(&mystack));
    printf("pop element: %d\n",pop(&mystack));
    printf("pop element: %d\n",pop(&mystack));
    printf("pop element: %d\n",pop(&mystack));
    printf("top element: %d\n",top(mystack));
}
```
- Output:
```c
top element: 50
stack overflow 
pop element: 50
top element: 40
pop element: 40
pop element: 30
pop element: 20
pop element: 10
stack is empty
top element: -1
```


