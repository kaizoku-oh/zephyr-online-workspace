/* Lib C */
#include <stdlib.h>
#include <stdbool.h>

/* Zephyr */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

/* Golioth */
#include <golioth/client.h>
#include <samples/common/net_connect.h>
#include <samples/common/sample_credentials.h>

static K_SEM_DEFINE(connected, 0, 1);
static struct golioth_client *client = NULL;
static const struct device *temperature_dev = DEVICE_DT_GET(DT_NODELABEL(die_temp));

static void on_client_event(struct golioth_client *client, enum golioth_client_event event, void *arg);

int main(void)
{
  int ret = 0;
  struct sensor_value value = {0};
  const struct golioth_client_config *client_config = golioth_sample_credentials_get();

  /* Connect to LAN (get an IP address from DHCP) */
  net_connect();

  /* Create client and start connecting to Golith cloud */
  client = golioth_client_create(client_config);
  golioth_client_register_event_callback(client, on_client_event, NULL);

  /* Wait forever for connection flag */
  k_sem_take(&connected, K_FOREVER);

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

static void on_client_event(struct golioth_client *client, enum golioth_client_event event, void *arg)
{
  bool is_connected = (event == GOLIOTH_CLIENT_EVENT_CONNECTED);

  if (is_connected)
  {
    k_sem_give(&connected);
  }
  LOG_INF("Golioth client %s", is_connected ? "connected" : "disconnected");
}
