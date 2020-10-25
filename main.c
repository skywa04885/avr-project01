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

  // Prepares the distance sensor
  vma306_t vma;
  vma.pin  = &PINF;
  vma.port = &PORTF;
  vma.ddr  = &DDRF;
  vma.echo = PF7;
  vma.trig = PF6;
  vma306_init(&vma);
  LOGD("VMA306 Initialized", MAIN_LABEL);

  // Initializes the color sensor
  color_sensor_t color_sensor;
  color_sensor.ddr = &DDRL;
  color_sensor.port = &PORTL;
  color_sensor.pin = &PINL;
  color_sensor.s0 = PL5;
  color_sensor.s1 = PL3;
  color_sensor.s2 = PL2;
  color_sensor.s3 = PL0;
  color_sensor.out = PL4;
  color_sensor_init(&color_sensor);

  // Initializes the buzzer
  buzzer_t buzzer;
  buzzer.port = &PORTH;
  buzzer.ddr = &DDRH;
  buzzer.n = PH6;
  buzzer_init(&buzzer);

  char buffer[64];
  uint32_t i = 0;
  uint16_t prev = 0;
  for (;;) {
    color_sensor_ret_t ret = color_sensor_read(&color_sensor);
    
    a1602_return_home();
    a1602_clear();
    sprintf(buffer, "R:%-3u,G:%-3u", ret.r, ret.g, ret);
    a1602_write(buffer);

    for (uint8_t i = 0; i < (40 - strlen(buffer)); ++i) {
      a1602_instruct(A1602_CDS_DEF | A1602_CDS_MLR);
      _delay_us(A1602_DLY_COS);
    }

    sprintf(buffer, "B:%-3u", ret.b);
    a1602_write(buffer);

    switch (color_sensor_make_sense(&ret)) {
      case CRES_BLUE: status_c_blue_on(); break;
      case CRES_GREEN: status_c_green_on(); break;
      case CRES_RED: status_c_red_on(); break;
    }

    _delay_ms(50);
    /*
    uint16_t mm = vma306_read(&vma);

    if (mm < 30) {
      buzzer_buzz(&buzzer, 700, 100);
      buzzer_buzz(&buzzer, 900, 70);
      buzzer_buzz(&buzzer, 1100, 60);
    }

    if (mm > prev + 3 || mm < prev - 3) {
      prev = mm;

      a1602_return_home();
      a1602_clear();
      sprintf(buffer, "%ucm", mm);
      a1602_write(buffer);
    }
    _delay_ms(10);
    */
    /*
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
    */
  }
}