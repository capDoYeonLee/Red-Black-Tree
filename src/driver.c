// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>
//
// #include <stdio.h>
//
// int main() {
//     int *ptr = (int *)0x12345678;  // 임의의 할당되지 않은 이상한 주소
//     *ptr = 42;                     // 해당 주소로 접근 → page fault 발생

// int *ptr = malloc(sizeof(int));  // 이 시점에는 VA만 할당됨
// *ptr = 42;                       // 여기서 처음 쓰는 순간 페이지 폴트 → 그제서야 물리 메모리에 매핑됨

//     return 0;
// }


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    size_t page_size = getpagesize();
    void *addr = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    unsigned char vec;
    mincore(addr, page_size, &vec);  // vec의 하위 비트가 1이면 메모리에 있음

    printf("접근 전: %d\n", vec & 1);

    ((char*)addr)[0] = 'A';  // 실제 접근 → 이 시점에 페이지 폴트 발생

    mincore(addr, page_size, &vec);  // 다시 확인
    printf("접근 후: %d\n", vec & 1);

    munmap(addr, page_size);
    return 0;
}
