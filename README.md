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
