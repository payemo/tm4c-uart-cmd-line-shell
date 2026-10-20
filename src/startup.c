#include <stdint.h>

extern uint32_t _estack;

extern uint32_t _etext;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

extern int main(void);

void ResetISR(void);
void NmiSR(void);

__attribute__((section(".isr_vector")))
const void *vtable[] = {
  &_estack,
  ResetISR,
  NmiSR,
};

void ResetISR(void)
{
  uint32_t *src, *dst;

  for (src = &_etext, dst = &_data; dst < &_edata; ++src, ++dst) {
    *dst = *src;
  }

  for (dst = &_bss; dst < &_ebss; ++dst) {
    *dst = 0;
  }

  main();
}

void NmiSR(void)
{
  while(1) {
  }
}
