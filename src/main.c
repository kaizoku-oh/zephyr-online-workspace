// Lib C includes
#include <stdlib.h>
#include <stdbool.h>

// Zephyr includes
#include <zephyr/kernel.h>

int main(void) {

  while (true) {
    printk("Running...\r\n");
    k_msleep(1000);
  }

  return EXIT_FAILURE;
}
