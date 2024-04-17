# Advanced C/C++
## **Lesson 2: Stdarg - Assert**
**Thư viện Stdarg:** được dùng để viết một hàm mà số lượng đối số có thể biến đổi (variable arguments). Trong hàm sum dưới đây
```c
int sum(int a, int b){
    return a+b;
}
```
Chỉ có thể truyền vào 2 đối số là a và b, nếu muốn truyền nhiều hơn thì giải pháp là dùng **variadic function**. `printf` là 1 hàm có thể truyền nhiều tham số vào và nó là variadic function.

- Ví dụ:
```c
#include<stdio.h>
#include<stdarg.h>

int sum(int args_num, ...){ //args_num là số lượng tham số được truyền vào
    va_list args; // nơi đối số sẽ đc lưu
    va_start(args, args_num); //khởi tạo va_list bằng cách dùng va_start, và nó sẽ lấy tham số đầu tiên args_num

    
    int s= 0;   
    
    for(int i = 0; i < args_num; i++){
        int x = va_arg(args, int); //truyền vào va_list và kiểu dữ liệu
         s += x;
    }
    va_end(args);
    return s;
}

int main(){
    printf("sum is %d", sum(3,1,2,4));
    return 0;
}
```
- Output:
```c
sum is 7
```
**Assert:** là một thư viện của c, chứa thông tin để chẩn đoán hỗ trợ gỡ lỗi chương trình. Dùng thư viện này để debug chương trình vì:
- Projects quá lớn và nhiều file không thể dùng printf để debug.
- MCU không có màn hình Console

Nếu kết quả của Assert trả về false bộ debug sẽ báo lỗi.
```c
#include <stdio.h>
#include <assert.h>

int main() {
    int x = 5;

    assert(x != 5);

    // Chương trình sẽ tiếp tục thực thi nếu điều kiện là đúng.
    printf("X is: %d", x);
    
    return 0;
}
```
ví dụ trên sẽ báo lỗi vì x = 5 không thỏa điều kiện của assert

## **Lesson 3: Pointer**
**Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.**
```
#include <stdio.h>

int main() {
    int *ptr;
    printf("Size of pointer: %d bytes\n", sizeof(ptr));
    return 0;
}
```
**Function Pointer:** là một loại con trỏ trong ngôn ngữ lập trình C và C++. Nó tham chiếu đến một hàm thay vì một giá trị dữ liệu như các loại con trỏ khác. Mục đích chính của con trỏ hàm là cho phép chương trình chọn hàm để thực thi tại thời điểm chạy.

Cụ thể, khi ta khai báo một con trỏ hàm, ta sẽ cần chỉ định kiểu dữ liệu của hàm mà con trỏ đó sẽ tham chiếu đến, bao gồm kiểu trả về và các tham số của hàm. Sau đó, ta có thể gán con trỏ hàm này cho một hàm cụ thể. Khi gọi con trỏ hàm, chương trình sẽ thực thi hàm mà con trỏ đang tham chiếu đến.
>Syntax:
`return_type (* pointer_name) (arg_1_datatype, arg_2_datatype, ...);`

>Example:
`int (*ptr)(int, int);`
```
#include<stdio.h>

void sum(int a, int b){
    printf("phep toan la %d", a+b);
}

void minus(int a, int b){
    printf("phep toan la %d", a-b);
}

void multiply(int a, int b){
    printf("phep toan la %d", a*b);
}

void div(int a, int b){
    printf("phep toan la %d", a/b);
}

int main(){
    void (*pheptoan)(int, int) = &div; // khai báo
    pheptoan(10,5);
    return 0;
}
```
```
#include<stdio.h>

void swap(int *xp, int *yp){
    int temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = n-1; j > i; j--){
            if(arr[j] < arr[j-1]){
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Mang truoc khi sap xep: \n");
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("Mang sau khi sap xep: \n");
    printArray(arr, n);
    return 0;
}

/* i = 0
   64 34 25 12 22 11 90
   i                  j 
   đầu tiên so sách 90 và 11, tiếp đó là các cặp liền kề đến khi đến vị trí i thì stop
   i = 1
   11 64 34 25 12 22 90
       i

   i = 2
   11 12 64 34 25 22 90
          i

   i = 3
   11 12 22 64 34 25 90
             i

   i = 4
   11 12 22 25 64 34 90
                i

   i = 5
   11 12 22 25 34 64 90
                   i
*/
```
```
Mang truoc khi sap xep: 
64 34 25 12 22 11 90 
Mang sau khi sap xep:
11 12 22 25 34 64 90
```
**Null Pointer:**
**Const Pointer and Pointer to Const:**
**Void Pointer:**
**Pointer to Pointer:**

## **Lesson 4: Memory Layout**
Memory layout của một chương trình C bao gồm 5 phần:

Text segment  (i.e. instructions)

Initialized data segment 

Uninitialized data segment  (bss) 

Heap 

Stack


<img src="https://media.geeksforgeeks.org/wp-content/uploads/memoryLayoutC.jpg">

**Text Segment (Code Segment):** Là khu vực bộ nhớ chứa mã máy của chương trình sau khi được biên dịch. Đây là phần chứa các lệnh và hàm thực thi của chương trình. Khu vực này thường được đánh dấu là chỉ đọc để ngăn chặn việc sửa đổi mã thực thi.

**Initialized Data Segment (DS):** chứa **global variables** và **static variables** **đã được khởi tạo với giá trị khác 0**.
các biến này có thể đọc và ghi, các biến ở DS chỉ được thu hồi khi chương trình kết thúc (thoát ra khỏi hàm main, với MCU thì khi bị ngắt nguồn)
- Ví dụ:
```c
int global = 100; //global được khởi tạo với giá trị 100
int foo() {
    static int number = 10; //biến static number được khởi với giá trị 10
    return 0;
}
```
**Uninitialized Data Segment (BSS):** là nơi lưu trữ **global variables, static variables không được khởi tạo hoặc khởi tạo với giá trị bằng 0.**
các biến này có thể đọc và ghi, các biến ở BSS chỉ được thu hồi khi chương trình kết thúc (thoát ra khỏi hàm main, với MCU thì khi bị ngắt nguồn)
- Ví dụ:
```c
int global; //không được khởi tạo giá trị 
int foo() {
    static int number = 0; //biến static number được khởi tạo với giá trị bằng 0
    return 0;
}
```
**Heap (Dynamic Memory Allocation):** Trong C/C++ chúng ta có thể hoàn toàn control được quá trình cấp phát hoặc giải phóng bộ nhớ bằng các lệnh như malloc, calloc, relloc, free, new, delete, ... Vùng nhớ được cấp phát chính là HEAP, vùng nhớ này sẽ phình lên ( grows upward ) mỗi khi bạn cấp phát. Khi sử dụng xong các bạn phải free(delete trong c++) vùng nhớ này. Nếu quên không delete sẽ gây ra hiện tượng Memory Leak.

Bộ nhớ Heap được dùng để lưu trữ vùng nhớ cho những biến con trỏ được cấp phát động bởi các hàm malloc - calloc - realloc (trong C).

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

Chứa các biến cục bộ và tham số truyền vào hàm, các biến và tham số này đc khởi tạo khi hàm của biến cục bộ or biến môi trường (tham số truyền vào) được gọi ra từ hàm main. Khi một hàm được gọi, một frame (nghĩa là frame sẽ lưu trữ thông tin về biến cục bộ của hàm, các giá trị tham số) mới sẽ được tạo trên stack để lưu trữ các biến cục bộ của hàm đó. Khi hàm kết thúc, frame  đó sẽ bị loại bỏ khỏi stack, và bất kỳ biến cục bộ nào trong frame đó cũng sẽ bị hủy.

Có thể đọc và ghi giá trị khi còn ở trong hàm

Sau khi ra khỏi hàm vùng nhớ sẽ thu hồi frame này.

 ví dụ dưới đây:
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


## **Lesson 8: Struct - Union**
**Struct:** là một cấu trúc dữ liệu để tạo ra một kiểu dữ liệu mới bằng cách kết hợp nhiều kiểu dữ liệu khác lại với nhau. Cấu trúc này cho phép bạn tự định nghĩa các kiểu dữ liệu phức tạp bằng cách kết hợp các kiểu dữ liệu cơ bản của C như int, float, char, v.v.
Một struct trong C có thể bao gồm một hoặc nhiều biến thành viên (member variables), mỗi biến thành viên có thể là bất kỳ kiểu dữ liệu nào trong C. Điều này cho phép bạn tạo ra các đối tượng dữ liệu phức tạp hơn so với việc sử dụng các kiểu dữ liệu cơ bản.
- Ví dụ:
```c
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef struct ex{
    uint8_t a; //1 byte
    uint16_t b; //2 byte
    uint32_t c; //4 byte
}ex;
/* cách tính kích thước của struct
    đầu tiền xem thành viên có kiểu dữ liệu lớn nhất, unit32_t (4byte) lấy làm cơ sở để quét
    uint8_t a              |    a    |    b    |    b   |padding| 
    unit16_t b             |    c    |    c    |    c   |   c   | 
    unit32_t c

=> Struct này sẽ có kích thước là 8 byte
 */


typedef struct ex1{
    uint8_t a; //1 byte
    uint32_t c; //4 byte
    uint16_t b; //2 byte
}ex1;

/* cách tính kích thước của struct
    đầu tiền xem thành viên có kiểu dữ liệu lớn nhất, unit32_t (4byte) lấy làm cơ sở để quét
    uint8_t a              |    a    |padding|padding|padding| 
    unit32_t c             |    c    |   c   |   c   |   c   | 
    unit16_t b             |    b    |   b   |padding|padding|

=> Struct này sẽ có kích thước là 12 byte
 */

int main(){
    printf("size of struct ex %zu\n", sizeof(ex));
    printf("size of struct ex1 %zu\n", sizeof(ex1));
    return 0;
}
```
- Output:
```c
size of struct ex 8
size of struct ex1 12
```
**Data Structure Alignment trong C/C++** https://cppdeveloper.com/c-nang-cao/data-alignment-trong-c-c/

**Union:** là một cấu trúc dữ liệu giúp lập trình viên kết hợp nhiều kiểu dữ liệu khác nhau vào cùng một vùng nhớ. Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng. Điều này được ứng dụng nhằm tiết kiệm bộ nhớ.
- Ví dụ
```c
typedef union uni
{ 
     uint8_t arr1[5];
     uint16_t arr2[9];
     uint32_t arr3[3];
}uni;
/* lấy kiểu dữ liệu lớn nhất để quét, trong vd trên thì unit32_t là lớn nhất 4 bytes
arr1[5] = 8 bytes
arr2[9] = 20 bytes
arr3[3] = 12 bytes

=> kích thước uni = 20 bytes
 */
```
## **Lesson 9: JSON**
**JSON:** 
## **Lesson 10: Linked list**

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
**Stack:** là một data structure giúp lưu trữ, quản lý dữ liệu theo cơ chế LIFO (Last In, First Out). Stack cho phép hai thao tác cơ bản: **push (đẩy một phần tử vào ngăn xếp)** và **pop (lấy một phần tử ra khỏi ngăn xếp)**. Ngoài ra, thường còn có các thao tác khác như **peek (xem giá trị phần tử đầu ngăn xếp mà không loại bỏ nó)** và **isEmpty (kiểm tra xem ngăn xếp có trống không)**.
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

**Queue:** được sử dụng để lưu trữ và quản lý dữ liệu theo cơ chế FIFO (First In First Out). Queue cho phép thực hiện hai hoạt động cơ bản: **enqueue** (thêm một phần tử vào cuối hàng đợi) và **dequeue** (loại bỏ một phần tử từ đầu hàng đợi). Queue được quản lý thông qua hai con trỏ: **front** và **rear**. Phần tử được thêm vào **(enqueue) tại rear** và được loại bỏ **(dequeue) từ front**.
- ví dụ:
```c
#include<stdio.h>
#include<stdlib.h>

typedef struct Queue{
    int *items; //khai báo con trỏ để sau đó cấp phát bộ nhớ => items sẽ thành mảng
    int size; 
    int front, rear;
}Queue;

void initialize(Queue *queue, int size){
    queue->items = malloc(sizeof(int) * size);
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}

int is_empty(Queue queue){
    return queue.front == -1;
}

int is_full(Queue queue){
    return (queue.rear + 1) % queue.size == queue.front; 
    /*
        rear đang là (4+1) % size là 5 sẽ = 1, dư 0
        => 0 == 0 nghĩa là queue đã  full
    */
}

void enqueue(Queue *queue, int value){
    if(!is_full(*queue)){
        if(is_empty(*queue)){
            queue->front = queue->rear = 0; //front và rear sẽ bằng 0 nếu queue đang rỗng
        }else{
            queue->rear = (queue->rear +1) % queue->size;
            /*
                (0+1)/5 = 0, dư 1 => rear = 1 vì lấy phần dư (%)
                (1+1)/5 =0, dư 2 => rear = 2
                (2+1)/5 =0, dư 3 => rear = 3
                (3+1)/5 =0, dư 4 => rear = 4


            */
        }
        queue->items[queue->rear] = value;
        /*
            items[0] = 3;
            items[1] = 4;
            items[2] = 5;
            items[3] = 6;
            items[4] = 7;
        */
    }else{
        printf("queue overflow\n");
    }
}

int dequeue(Queue *queue){
    if (!is_empty(*queue))
    {
        int dequeued_value = queue->items[queue->front];
        if(queue->front == queue->rear){
            queue->front = queue->rear = -1;
        }else{
            queue->front =(queue->front +1)%queue->size;
            /*
                (0+1) % 5 = 0, dư 1 => front = 1;
                (1+1) % 5 = 0, dư 2 => front = 2;
                (2+1) % 5 = 0, dư 3 => front = 3;
                (3+1) % 5 = 0, dư 4 => front = 4;
                nếu tiếp tục dequeue thì nó sẽ vào câu lệnh queue->front = queue->rear = -1; vì front == rear
            */
        }
        return dequeued_value;
    }
    
    else{
        printf("queue underflow\n");
        return -1;
    }
    
}

int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

int main(){
    Queue myqueue;
    initialize(&myqueue, 5);

    enqueue(&myqueue, 10);
    enqueue(&myqueue, 20);
    enqueue(&myqueue, 30);
    enqueue(&myqueue, 40);
    enqueue(&myqueue, 50);
    
    printf("front element %d\n", front(myqueue));

    printf("dequeue element %d\n", dequeue(&myqueue));
    printf("front element %d\n", front(myqueue));
   
   
    return 0;
}
```
## **Lesson: Binary search - File operations - Code standards**
**Binary search:** là một thuật toán tìm kiếm giá trị trên một mảng đã được sắp xếp hoặc một dãy có thứ tự. tiếp theo so sánh giá trị cần tìm (gọi là **"key"**) với giá trị ở giữa của mảng. Dựa vào kết quả của phép so sánh, có thể loại bỏ một nửa của mảng khỏi tìm kiếm vì giá trị cần tìm không thể nằm ở đó.

**Thuật toán làm việc theo các bước sau:**

**Xác định phạm vi tìm kiếm:** Ban đầu, phạm vi tìm kiếm bao gồm toàn bộ mảng.

**Tìm phần tử giữa:** Tính chỉ số của phần tử giữa trong phạm vi tìm kiếm hiện tại. Nếu mảng có số phần tử chẵn, có hai phần tử ở giữa, có thể chọn một trong hai làm điểm giữa (thường là lựa chọn phần tử ở vị trí thấp hơn).

**So sánh giá trị cần tìm với giá trị giữa:**
Nếu giá trị cần tìm bằng giá trị ở giữa, công việc hoàn tất.
```c
if(arr[mid] == x)
        return mid;
```
Nếu giá trị cần tìm nhỏ hơn giá trị giữa, bạn loại bỏ nửa sau của mảng khỏi tìm kiếm và tiếp tục tìm kiếm trong nửa đầu.
Nếu giá trị cần tìm lớn hơn giá trị giữa, bạn loại bỏ nửa đầu của mảng và tiếp tục tìm kiếm trong nửa sau.
```c 
 if(arr[mid] > x) //loại vùng bên phải đi khi mid > x
        return binarysearch(arr, left, mid-1, x); //nên dưới đây right sẽ được thay bằng mid - 1

        return binarysearch(arr, mid+1, right, x);//nếu mid < x thì bỏ vùng bên trái nên left sẽ thay bằng mid
```

Lặp lại quy trình: Lặp lại quá trình trên với phạm vi tìm kiếm mới cho đến khi tìm thấy giá trị cần tìm hoặc cho đến khi phạm vi tìm kiếm không còn nữa (điều này có nghĩa là giá trị không tồn tại trong mảng).
- Example for a binarysearch function:
```c
int binarysearch(int *arr, int left, int right, int x){ //truyền vào mảng, vị trí trái, phải và giá trị x cần tìm
    if(right >= left){ 
        int mid = (right +left)/2;

        if(arr[mid] == x)
        return mid;

        if(arr[mid] > x) //loại vùng bên phải đi khi mid > x
        return binarysearch(arr, left, mid-1, x); //nên dưới đây right sẽ được thay bằng mid - 1

        return binarysearch(arr, mid+1, right, x);//nếu mid < x thì bỏ vùng bên trái nên left sẽ thay bằng mid +1
    }
    return -1; //vì vị trí trong mảng k có -1, khi return về -1 có nghĩa là k tìm thấy giá trị trong mảng
}
```
## **Lesson 13: Class**
**class:** là một cấu trúc dữ liệu mà user tự định nghĩa, trong đó user có thể đóng gói dữ liệu và các hàm thành viên (member functions) liên quan lại với nhau. Một class là một kiểu dữ liệu tùy chỉnh, cho phép tạo ra các đối tượng (objects) dựa trên nó.

Class cung cấp một cách để tổ chức mã nguồn của bạn theo các đối tượng có liên quan và cung cấp một cách tiếp cận để làm việc với dữ liệu và hành vi của các đối tượng đó. Class thường được sử dụng trong lập trình hướng đối tượng (OOP) để tạo ra các đối tượng có tính tổ chức và tái sử dụng cao.

```c
#include <iostream>

using namespace std;

// Khai báo class Hinhchunhat
class Hinhchunhat
{
public:
    int chieudai;
    int chieurong;

    // Phương thức tính diện tích hình chữ nhật
    int get_retangle_area()
    {
        return chieudai * chieurong;
    }

    // Phương thức hiển thị thông điệp
    void display();
};

// Định nghĩa phương thức display của class Hinhchunhat
void Hinhchunhat::display()
{
    cout << "Display Retangle" << endl;
}

// Hàm main
int main()
{
    // Tạo một đối tượng hinh1 từ class Hinhchunhat
    Hinhchunhat hinh1;

    // Gán giá trị cho các thuộc tính của đối tượng hinh1
    hinh1.chieudai = 10;
    hinh1.chieurong = 5;

    // Gọi phương thức display để hiển thị thông điệp
    hinh1.display();

    // In ra diện tích của hình chữ nhật bằng cách gọi phương thức get_retangle_area
    cout << "get_retangle_area:" << hinh1.get_retangle_area() << endl;

    return 0;
}
```
Khai báo **class Hinhchunhat** để định nghĩa một **class mới**.

Trong class này, có **hai biến dữ liệu** **chieudai** và **chieuron**g để lưu chiều dài và chiều rộng của hình chữ nhật, và **hai phương thức**:

**get_retangle_area()**: trả về diện tích của hình chữ nhật (tích của chiều dài và chiều rộng).
**display()**: hiển thị một thông điệp.
Sau đó, chúng ta **định nghĩa**  display() bên **ngoài class** bằng cách sử dụng **toán tử phạm vi ::**.

Trong hàm main(), chúng ta **tạo một đối tượng hinh1** từ class Hinhchunhat và gán giá trị cho các thuộc tính của nó.

Tiếp theo, chúng ta gọi phương thức display() để hiển thị thông điệp và get_retangle_area() để tính và in ra diện tích của hình chữ nhật.

Trong C++, phương thức và hàm có một số điểm giống nhau nhưng cũng có những khác biệt quan trọng:

Giống nhau:

Thực thi mã: Cả hai đều là các khối mã thực hiện một tác vụ cụ thể.

Tham số: Cả hai có thể chấp nhận các tham số đầu vào (argument).

Trả về giá trị: Cả hai có thể trả về một giá trị (hoặc không trả về gì).

Khác biệt:

Phạm vi (scope):

Hàm (function): Có thể được định nghĩa bên ngoài các lớp và không thuộc về bất kỳ class nào. Hàm có thể được gọi từ bất kỳ nơi nào trong chương trình.
Phương thức (method): Là các hàm đặc biệt được định nghĩa trong phạm vi của một class. Phương thức chỉ có thể được gọi trên đối tượng của class đó.
Tham số ẩn (implicit parameter):

Hàm (function): Không có tham số ẩn.
Phương thức (method): Thường có một tham số ẩn là con trỏ this, cho biết đối tượng trên đó phương thức được gọi.
Access Control:

Hàm (function): Không có quyền truy cập trực tiếp vào dữ liệu thành viên của một class, trừ khi chúng được truyền vào như tham số hoặc được truy cập thông qua các phương thức công cộng.
Phương thức (method): Có thể truy cập trực tiếp vào dữ liệu thành viên (nếu được khai báo public hoặc protected) của class mà nó thuộc về.
Trong ngôn ngữ lập trình C, khái niệm của phương thức không tồn tại, chỉ có hàm. Nhưng trong C++, hàm được định nghĩa bên trong class được gọi là phương thức.

**Constructor:** là một phương thức đặc biệt của một class, được gọi khi một đối tượng của lớp đó được tạo ra. Constructor thường được sử dụng để khởi tạo các biến thành viên của đối tượng và thực hiện các công việc khởi tạo khác.

Trong C++, constructor có tên giống với tên của lớp và không có kiểu trả về (thậm chí không có kiểu void). Constructor có thể có hoặc không có tham số. Nếu một lớp không định nghĩa constructor, C++ sẽ tự động tạo một constructor mặc định (default constructor) không nhận tham số.

Dưới đây là một ví dụ đơn giản về một lớp với constructor trong C++:
```c
#include <iostream>

class Hinhchunhat {
private:
    int chieudai;
    int chieurong;

public:
    // Constructor không tham số
    Hinhchunhat() {
        chieudai = 0;
        chieurong = 0;
        std::cout << "Constructor duoc goi!" << std::endl;
    }

    // Constructor có tham số
    Hinhchunhat(int dai, int rong) {
        chieudai = dai;
        chieurong = rong;
        std::cout << "Constructor duoc goi voi tham so!" << std::endl;
    }

    // Phương thức để hiển thị thông tin
    void display() {
        std::cout << "Chiều dài: " << chieudai << ", Chiều rộng: " << chieurong << std::endl;
    }
};

int main() {
    // Sử dụng constructor không tham số
    Hinhchunhat hinh1;

    // Sử dụng constructor có tham số
    Hinhchunhat hinh2(4, 3);

    // Hiển thị thông tin của các hình chữ nhật
    std::cout << "Thông tin hình 1: ";
    hinh1.display();
    std::cout << "Thông tin hình 2: ";
    hinh2.display();

    return 0;
}
```

## **Lesson 14: OOPs Concepts**

**Encapsulation:** là một nguyên tắc trong lập trình hướng đối tượng (OOP) mà mục tiêu là che dấu các chi tiết bên trong một đối tượng và chỉ cho phép truy cập thông qua các phương thức công khai (public methods) hoặc giao diện công khai. Điều này giúp bảo vệ dữ liệu và chức năng của đối tượng khỏi sự can thiệp bên ngoài và tạo ra một giao diện dễ sử dụng.
Các yếu tố chính của Encapsulation bao gồm:

Thuộc tính và Phương thức: Dữ liệu và các hành vi của một đối tượng được đóng gói vào cùng một cấu trúc, được gọi là lớp (class) trong OOP. Thuộc tính (properties) đại diện cho dữ liệu và phương thức (methods) đại diện cho hành vi.

Access Modifiers: Encapsulation sử dụng các phạm vi truy cập (access modifiers) như public, private và protected để quản lý việc truy cập đến các thành phần của một đối tượng. Thuộc tính và phương thức được khai báo là private chỉ có thể truy cập bên trong cùng một lớp, trong khi public có thể truy cập từ bên ngoài lớp.

Giao diện công khai (Public Interface): Các phương thức công khai (public methods) cung cấp một giao diện cho các đối tượng bên ngoài để tương tác với đối tượng. Các phương thức này đại diện cho hành vi được cho phép và cung cấp một cách an toàn để thực hiện các thao tác trên dữ liệu của đối tượng.

Che dấu chi tiết bên trong: Chi tiết cài đặt của một đối tượng được che dấu khỏi người sử dụng bên ngoài. Điều này giúp bảo vệ dữ liệu và chức năng của đối tượng khỏi sự can thiệp trực tiếp, và chỉ cho phép truy cập thông qua giao diện công khai.

- Ví dụ:
```
#include<iostream>
#include<string>

using namespace std;

class Student
{
private:
    string Name;
    double GPA;
    int StudentID;
public:
    Student(string name); // Constructor

    string getName(){ // dùng method để truy cập vào property
        return Name;
    }

    void setName(string name){ // dùng method để thay đổi tên 
        Name = name;
    }

    double getGPA()
    {
        return GPA;
    }

    void setGPA(double gpa)
    { // dùng method để thay đổi tên 
        GPA = gpa;
    }

    int getStudentID()
    {
        return StudentID;
    }
};

Student::Student(string name)
{
    Name = name;
    static int id = 1000;
    StudentID = id;
    id++;
}

int main(){
    Student sv1("trung");
    Student sv2("trang");
    Student sv3("john");
    //sv1.setName("john"); //toán tử . được sử dụng khi bạn truy cập các thành phần của một đối tượng trực tiếp.
    cout << "Student name: " << sv1.getName() << endl; // Gọi phương thức getName() để lấy giá trị của thuộc tính Name và in ra màn hình

    sv1.setGPA(0);
    cout << "Student GPA: " << sv1.getGPA() << endl; 

    cout << "Student ID: " << sv1.getStudentID() << endl;

    cout << "Student ID: " << sv2.getStudentID() << endl;

    cout << "Student ID: " << sv3.getStudentID() << endl;



    return 0;
}
```
```
Student name: trung
Student GPA: 0
Student ID: 1000
Student ID: 1001
Student ID: 1002
```
**Inheritance:** Trong C++, có thể kế thừa các thuộc tính và phương thức từ lớp này sang lớp khác.
> Lớp dẫn xuất (con) - lớp kế thừa từ lớp khác

> Lớp cơ sở (cha) - lớp được kế thừa từ
Để kế thừa từ một lớp, ta dùng ký hiệu `:`

Trong ví dụ bên dưới, lớp Car (con) kế thừa các thuộc tính và phương thức từ lớp Vehicle (cha):
```
#include<iostream>
#include<string>

using namespace std;

class Vehicle{
    public:    
        string brand = "Ford";
        void honk() {
        cout << "Tuut, tuut! \n" ;
    }
};

class Car: public Vehicle {
  public: 
    string model = "Mustang";
};

int main() {
  Car myCar;
  myCar.honk();
  cout << myCar.brand + " " + myCar.model;
  return 0;
}
```
In C++, there are three access specifiers:
- public - members are accessible from outside the class
- private - members cannot be accessed (or viewed) from outside the class
- protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes. You will learn more about Inheritance later.
 protected, is similar to private, but it can also be accessed in the inherited class


Khi bạn kế thừa từ lớp cơ sở với access specifier là protected, các thành viên và phương thức public của lớp cơ sở sẽ trở thành protected trong lớp dẫn xuất. Điều này có nghĩa là bạn vẫn có thể kế thừa các thành viên và phương thức từ lớp cơ sở, nhưng chúng sẽ không được truy cập trực tiếp từ bên ngoài lớp dẫn xuất.

Để truy cập các thành viên và phương thức của lớp cơ sở từ bên ngoài lớp dẫn xuất, bạn cần cung cấp một giao diện công khai thông qua các phương thức public trong lớp dẫn xuất.

Dưới đây là một ví dụ minh họa:
```
#include <iostream>
using namespace std;

// Lớp cơ sở (base class)
class Base {
protected:
    int protectedMember;
public:
    void publicFunction() {
        cout << "Public function from Base" << endl;
    }
    void setProtectedMember(int value) {
        protectedMember = value;
    }
    int getProtectedMember() {
        return protectedMember;
    }
};

// Lớp dẫn xuất (derived class)
class Derived : protected Base {
public:
    void accessBaseMembers() {
        setProtectedMember(42); // Có thể truy cập từ Derived
        cout << "Protected member of Base: " << getProtectedMember() << endl; // Có thể truy cập từ Derived
        publicFunction(); // Có thể truy cập từ Derived
    }
};

int main() {
    Derived derivedObj;
    derivedObj.accessBaseMembers(); // Gọi phương thức từ lớp dẫn xuất
    // derivedObj.setProtectedMember(10); // Lỗi, không thể truy cập từ bên ngoài Derived
    // derivedObj.getProtectedMember(); // Lỗi, không thể truy cập từ bên ngoài Derived
    // derivedObj.publicFunction(); // Lỗi, không thể truy cập từ bên ngoài Derived
    return 0;
}
```

Overriding là một trong những đặc tính của kế thừa (inheritance). Đặc tính này cho phép một lớp con (derived class) cung cấp một triển khai mới cho một phương thức đã được định nghĩa trong lớp cha (base class). Khi lớp con override một phương thức, nó cung cấp một triển khai cụ thể cho phương thức đó, thay vì sử dụng triển khai mặc định được kế thừa từ lớp cha.

Overriding là một trong những cách quan trọng nhất để mở rộng và tuỳ chỉnh hành vi của các lớp trong OOP. Nó cho phép bạn sử dụng các phương thức chung được định nghĩa trong lớp cha, nhưng cung cấp triển khai cụ thể cho chúng trong các lớp con, tạo ra sự linh hoạt và tái sử dụng mã.

- Đặc điểm của overriding:

Phương thức trong lớp con có cùng tên, kiểu trả về và các tham số với phương thức trong lớp cha.

Phương thức trong lớp con sử dụng từ khóa override để ghi đè phương thức trong lớp cha.

Khi gọi phương thức từ một đối tượng của lớp con, triển khai của phương thức trong lớp con sẽ được gọi.

Overriding là một cách mạnh mẽ để tùy chỉnh và mở rộng hành vi của lớp cha trong OOP, đồng thời duy trì sự linh hoạt và tái sử dụng mã.

**Polymorphism:**
```
//OVERLOADING 
// #include<iostream>
// #include<string>

// using namespace std;

// int sum(int a, int b)
// {
//     return a+b;
// }

// double sum(double a, double b)
// {
//     return a+b;
// }

// int sum(int a, int b, int c)
// {
//     return a+b+c;
// }

// int main(){
//     cout<< "sum: "<< sum(2,3) << endl;
//     cout<< "sum: "<< sum(2.2,3.1) << endl;
//     cout<< "sum: "<< sum(2,3,4) << endl;


//     return 0;
// }

//OVERRIDING
#include <iostream>
#include <string>


using namespace std;

class Person
{
protected:
  string Name;
  int Age;
  string Home_Address;

public:
  virtual string test()
  {
    return "Hello person";
  }

  void displayInfo()
  {
    cout << test() << endl;
  }
  
};


class Student : public Person //class con kế thừa từ class student theo kiểu public
{
private:
  string School_Name;
  double GPA;
  int StudentID;

public:
  string test()
  {
    return "Hello student";
  }

};


int main()
{
  Person person1;
  person1.displayInfo();
  

  cout << "-----------------------" << endl;
  
  Student student1;
  student1.displayInfo();

  

  return 0;
}
```
## **Lesson 15: Standard template library**

Standard Template Library ( STL) là một thư viện trong ngôn ngữ lập trình C++ cung cấp một tập hợp các template classes và functions để thực hiện nhiều loại cấu trúc dữ liệu và các thuật toán phổ biến. STL đã trở thành một phần quan trọng của ngôn ngữ C++ và làm cho việc lập trình trở nên mạnh mẽ, linh hoạt và hiệu quả.

Một số thành phần chính của STL:
- Container
- Iterator
- Algorithms
- Functor

