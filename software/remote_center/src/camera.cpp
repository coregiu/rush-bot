#include "camera.h"

void initCamera() {
  delay(1000);
  Serial.println("\nGOOUUU V1.3 ESP32-S3 CAM 初始化...");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("初始化失败: 0x%x", err);
    return;
  }

  sensor_t *s = esp_camera_sensor_get();
  Serial.println("------------------------");
  Serial.print("摄像头型号: ");
  if (s->id.PID == OV2640_PID)      Serial.println("OV2640 ✅");
  else if (s->id.PID == OV3660_PID) Serial.println("OV3660 ✅");
  else                              Serial.println("未知");
  Serial.printf("ID: 0x%04X\n", s->id.PID);
  // Serial.printf("分辨率: %dx%d\n", s->width, s->height);
  Serial.println("------------------------");
}