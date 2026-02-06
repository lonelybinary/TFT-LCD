/*
 * Lesson 10: Notification Interface
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习创建通知界面
 * 
 * 知识点：
 * - 通知卡片设计
 * - 图标和文本组合
 * - 按钮设计
 * - 居中布局
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

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 10: Notification Interface");
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
  
  // 通知界面
  Serial.println("Displaying Notification Interface");
  gfx->fillScreen(BLACK);
  
  // 通知卡片（居中显示，留出边距）
  int cardX = 30;
  int cardY = 80;
  int cardW = 260;
  int cardH = 200;
  gfx->fillRect(cardX, cardY, cardW, cardH, WHITE);
  gfx->drawRect(cardX, cardY, cardW, cardH, BLACK);
  
  // 图标区域（左侧）
  int iconX = cardX + 30;
  int iconY = cardY + cardH / 2;
  gfx->fillCircle(iconX, iconY, 25, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(iconX - 8, iconY - 10);
  gfx->println("!");
  
  // 通知内容（中间区域，统一字体大小）
  gfx->setTextColor(BLACK);
  gfx->setTextSize(2);
  gfx->setCursor(cardX + 70, cardY + 40);
  gfx->println("New Message");
  gfx->setCursor(cardX + 70, cardY + 80);
  gfx->println("You have 3");
  gfx->setCursor(cardX + 70, cardY + 120);
  gfx->println("unread items");
  
  // 关闭按钮（右上角）
  int btnX = cardX + cardW - 25;
  int btnY = cardY + 10;
  gfx->fillRect(btnX, btnY, 20, 20, RED);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(btnX + 5, btnY + 2);
  gfx->print("X");
  
  Serial.println("Notification Interface display complete!");
}

void loop() {
  delay(1000);
}
