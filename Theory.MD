# Pipe
Pipe: là 1 phương thức giao tiếp 1 chiều, có 2 đầu: 1 đầu đọc & 1 đầu nghe
    Bản chất của việc tạo pipe: là 1 virtual file (đơn giản nó chỉ là 1 vùng nhớ nằm trên RAM => khi restart thiết bị thì data trong vùng này sẽ mất đi).
    related-process: thể hiện các mối quan hệ giữa các process với nhau, 1 process ghi vào "virtual file" (là pipe) thì một related-process có thế đọc dữ liệu
từ nó
## Hoạt động của Pipe: 
    + Read pipe: 
        khi đọc 1 file rỗng thì đầu đọc sẽ block cho đến khi có dữ liệu được "write" vào pipe
        fds[0] : read 
        fds[1] : write