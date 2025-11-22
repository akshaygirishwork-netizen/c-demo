#define IODIR0 (*(volatile unsigned int *)0xE0028000)
#define IOSET0 (*(volatile unsigned int *)0xE0028004)
#define IOCLR0 (*(volatile unsigned int *)0xE0028008)

int main(void) {
    IODIR0 |= (1 << 17);

    while (1) {
        IOSET0 = (1 << 17);
        for (volatile int i = 0; i < 50000; i++);
        IOCLR0 = (1 << 17);
        for (volatile int i = 0; i < 50000; i++);
    }
}

