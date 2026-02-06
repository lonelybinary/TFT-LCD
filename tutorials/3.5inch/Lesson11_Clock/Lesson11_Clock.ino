/*
 * Lesson 11: Clock Display
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习创建时钟显示界面
 * 
 * 知识点：
 * - 模拟时钟绘制
 * - 时钟刻度绘制
 * - 时针和分针绘制
 * - 数字时间显示
 * - 居中布局
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino@1.6.4)
 */

#include <Arduino_GFX_Library.h>
#include <math.h>

// ==================== SPI LCD Pin Definitions ====================
#define TFT_CS    10
#define TFT_RST   42
#define TFT_DC    2
#define TFT_MOSI  11
#define TFT_SCLK  12
#define TFT_BACKLIGHT 41

// ==================== LCD Object ====================
// 注意：如需适配其他屏幕，请查看对应屏幕的测试程序
// 例如：0.96寸请查看 0.96inch/code/0.96inch_Test/0.96inch_Test.ino
// 详细适配指南请参考各屏幕文件夹下的ADAPTATION_GUIDE.md文件
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, 1, true);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);

// ==================== Helper Functions ====================

// 居中显示文本
void drawCenteredText(const char* text, int y, uint16_t color, int size) {
  gfx->setTextSize(size);
  gfx->setTextColor(color);
  int textWidth = strlen(text) * size * 6;
  int x = (gfx->width() - textWidth) / 2;
  gfx->setCursor(x, y);
  gfx->println(text);
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 11: Clock Display");
  Serial.println("Initializing LCD...");
  
  // Initialize backlight (PWM)
  // 注意：0.96寸使用Active Low控制（digitalWrite(TFT_BACKLIGHT, LOW)）
  // 其他屏幕使用PWM控制，请查看对应屏幕的测试程序
  ledcSetup(0, 5000, 8);
  ledcAttachPin(TFT_BACKLIGHT, 0);
  ledcWrite(0, 255);
  
  // Reset display
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // Initialize LCD
  if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
  }
  
  gfx->setRotation(0);
  
  Serial.println("LCD initialized successfully!");
  
  // ==================== Lesson Content ====================
  
  // 时钟界面
  Serial.println("Displaying Clock Interface");
  gfx->fillScreen(BLACK);
  
  // 时钟圆心位置（屏幕正中间：320/2=160, 480/2=240）
  int centerX = 160;  // 屏幕宽度中心
  int centerY = 240;  // 屏幕高度中心
  int radius = 100;   // 时钟半径，确保不超出屏幕
  
  // 外圈
  gfx->drawCircle(centerX, centerY, radius, WHITE);
  
  // 时钟刻度（12个刻度）
  for (int i = 0; i < 12; i++) {
    float angle = i * PI / 6 - PI / 2;
    int x1 = centerX + (radius - 5) * cos(angle);
    int y1 = centerY + (radius - 5) * sin(angle);
    int x2 = centerX + (radius - 20) * cos(angle);
    int y2 = centerY + (radius - 20) * sin(angle);
    gfx->drawLine(x1, y1, x2, y2, WHITE);
  }
  
  // 时针（指向3点）
  gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);
  
  // 分针（指向12点）
  gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
  
  // 中心点
  gfx->fillCircle(centerX, centerY, 5, WHITE);
  
  // 时间文本（显示在时钟下方）
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  drawCenteredText("12:00", 380, WHITE, 3);
  
  Serial.println("Clock Display complete!");
}

void loop() {
  delay(1000);
}
