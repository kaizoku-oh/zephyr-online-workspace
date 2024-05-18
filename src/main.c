/* Lib C */
#include <stdlib.h>
#include <stdbool.h>

/* Zephyr */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

static const struct device *temperature_dev = DEVICE_DT_GET(DT_NODELABEL(die_temp));

int main(void)
{
  int ret = 0;
  struct sensor_value value = {0};

  /* Check if internal temperature sensor is ready to be used */
  if (!device_is_ready(temperature_dev)) {
    LOG_ERR("Temperature device is not ready");
    while (true);
  }

  /* Periodically fetch data from sensor */
  while (true)
  {
    ret = sensor_sample_fetch(temperature_dev);
    if (ret) {
      LOG_ERR("Failed to fetch sample (%d)", ret);
      while (true);
    }
    ret = sensor_channel_get(temperature_dev, SENSOR_CHAN_DIE_TEMP, &value);
    if (ret) {
      LOG_ERR("Failed to get data (%d)", ret);
      while (true);
    }
    LOG_INF("CPU temperature: %.1f °C", sensor_value_to_double(&value));
    k_msleep(1000);
  }

  return EXIT_FAILURE;
}
