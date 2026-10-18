#include <stdint.h>

extern uint32_t _estack;

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
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

  for (src = &_sidata, dst = &_sdata; dst < &_edata; ++src, ++dst) {
    *dst = *src;
  }

  dst = &_sbss;

  for (dst = &_sbss; dst < &_ebss; ++dst) {
    *dst = 0;
  }

  main();

  while (1) {
  }
}

void NmiSR(void)
{
  while(1) {
  }
}
