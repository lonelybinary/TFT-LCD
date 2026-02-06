/*
 * Lesson 07: System Info Display
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习创建系统信息显示界面
 * 
 * 知识点：
 * - UI组件设计（标签、进度条、分隔线）
 * - 信息布局和层次结构
 * - 状态指示器设计
 * - 函数封装和代码组织
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino@1.6.4)
 */

#include <Arduino_GFX_Library.h>

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

// 绘制标签（带背景的文本）
void drawLabel(const char* text, int x, int y, uint16_t bgColor, uint16_t textColor, int textSize = 2) {
  int textWidth = strlen(text) * 6 * textSize;
  int textHeight = 8 * textSize;
  
  // 绘制背景
  gfx->fillRect(x, y, textWidth + 8, textHeight + 4, bgColor);
  
  // 绘制文本
  gfx->setTextColor(textColor);
  gfx->setTextSize(textSize);
  gfx->setCursor(x + 4, y + 4);
  gfx->println(text);
}

// 绘制进度条
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  // 绘制背景框
  gfx->drawRect(x, y, width, height, bgColor);
  
  // 计算填充宽度
  int fillWidth = (width * percent) / 100;
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}

// 居中显示文本
void drawCenteredText(const char* text, int y, uint16_t color, int size) {
  gfx->setTextSize(size);
  gfx->setTextColor(color);
  int textWidth = strlen(text) * size * 6;
  int x = (gfx->width() - textWidth) / 2;
  gfx->setCursor(x, y);
  gfx->println(text);
}

// 绘制分隔线
void drawSeparator(int y, uint16_t color) {
  gfx->drawFastHLine(20, y, gfx->width() - 40, color);
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 07: System Info Display");
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
  
  // 系统信息显示界面
  Serial.println("Displaying System Info Interface");
  gfx->fillScreen(BLACK);
  
  // 标题
  drawCenteredText("SYSTEM INFO", 20, YELLOW, 2);
  
  // 分隔线
  drawSeparator(60, CYAN);
  
  // 信息项
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(30, 100);
  gfx->print("Status: ");
  drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);
  
  gfx->setCursor(30, 160);
  gfx->print("Temp: ");
  gfx->setTextColor(CYAN);
  gfx->print("25.5");
  gfx->setTextColor(WHITE);
  gfx->println(" C");
  
  gfx->setCursor(30, 220);
  gfx->print("Battery: ");
  drawProgressBar(150, 220, 200, 20, 75, WHITE, GREEN);
  
  gfx->setCursor(30, 280);
  gfx->print("Signal: ");
  // 绘制信号强度指示器
  for (int i = 0; i < 4; i++) {
    int barHeight = (i + 1) * 8;
    uint16_t color = (i < 3) ? GREEN : gfx->color565(128, 128, 128);  // 灰色使用color565创建
    gfx->fillRect(150 + i * 12, 280 + (20 - barHeight), 10, barHeight, color);
  }
  
  Serial.println("System Info Display complete!");
}

void loop() {
  delay(1000);
}
