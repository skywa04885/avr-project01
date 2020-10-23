#include "main.h"

void setup() {
  // Initializes USART and the data streams
  usart_init();
  usart_setup_streams();

  // Inits the status module
  status_init();
  LOGD("status_init(): success", MAIN_LABEL);

  // Inits the a1602 display
  a1602_init();
  LOGD("a1602_init(): success", MAIN_LABEL);

  // Prints the final message
  LOGD("Setup(): success", MAIN_LABEL);
}

void __attribute__ (( noreturn )) main() {
  setup();

  // Clears the display
  a1602_instruct(A1602_DOO_DEF | A1602_DOO_ENA | A1602_DOO_ENC | A1602_DOO_ECP);
  a1602_instruct(A1602_FNS_DEF | A1602_FNS_ULF | A1602_FNS_UL2  | A1602_FNS_U8B);
  a1602_return_home();
  a1602_clear();
  a1602_write("Booting ...");
  LOGD("Updated display", MAIN_LABEL);
  _delay_ms(1000);

  // Prepares the temp
  dht11_t dht;
  dht.ddr = &DDRG;
  dht.port = &PORTG;
  dht.pin = &PING;
  dht.n = PG5;
  dht11_init(&dht);
  LOGD("DHT11 Initialized", MAIN_LABEL);

  char buffer[64];
  uint32_t i = 0;
  for (;;) {
    // Reads the sensor data, after which we will display it
    dht11_ret_t sensor_data = dht11_read(&dht);

    // Returns the screen to start position, and clears it
    a1602_return_home();
    a1602_clear();

    if (sensor_data.success) {
      // Displays the temparature
      sprintf(buffer, "%cTemp: %d.%d%c", 
        (sensor_data.sum != sensor_data.csum ? '^' : A1602_CARR), 
        sensor_data.t_int, sensor_data.t_dec, A1602_CDEG);
      a1602_write(buffer);

      // Shifts to the next line on the display
      for (uint8_t i = 0; i < (40 - strlen(buffer)); ++i) {
        a1602_instruct(A1602_CDS_DEF | A1602_CDS_MLR);
        _delay_us(A1602_DLY_COS);
      }

      // Displays the humidity
      sprintf(buffer, "%cHumi: %d.%d%%", 
        (sensor_data.sum != sensor_data.csum ? '^' : A1602_CARR), 
        sensor_data.h_int, sensor_data.h_dec);
      a1602_write(buffer);

      // Moves the cursor to the end of the screen ( not visible to us )
      for (uint8_t i = 1; i < (40 - strlen(buffer)); ++i) {
        a1602_instruct(A1602_CDS_DEF | A1602_CDS_MLR);
        _delay_us(A1602_DLY_COS);
      }
    } else {
      a1602_write("[DHT11]: Error !");
    }

    _delay_ms(2000);
  }
}