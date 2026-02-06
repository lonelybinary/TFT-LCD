/*
 * Lesson 03: Text Size
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习如何控制文本大小
 * 
 * 知识点：
 * - setTextSize() 函数
 * - 不同大小的效果
 * - 大小对位置的影响
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
  
  Serial.println("Lesson 03: Text Size");
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
  
  // Part 1: 显示不同大小的文本
  Serial.println("Displaying different text sizes...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  
  // Size 1 (默认大小)
  gfx->setTextSize(1);
  gfx->setCursor(20, 20);
  gfx->println("Size 1");
  
  // Size 2
  gfx->setTextSize(2);
  gfx->setCursor(20, 50);
  gfx->println("Size 2");
  
  // Size 3
  gfx->setTextSize(3);
  gfx->setCursor(20, 100);
  gfx->println("Size 3");
  
  // Size 4
  gfx->setTextSize(4);
  gfx->setCursor(20, 180);
  gfx->println("Size 4");
  
  delay(3000);
  
  // Part 2: 大小对比
  Serial.println("Comparing text sizes...");
  gfx->fillScreen(BLACK);
  
  int y = 20;
  for (int size = 1; size <= 5; size++) {
    gfx->setTextSize(size);
    gfx->setTextColor(WHITE);
    gfx->setCursor(20, y);
    gfx->print("Size ");
    gfx->print(size);
    
    // 显示相同文本，不同大小
    gfx->setTextColor(CYAN);
    gfx->print(" ABC");
    
    y += size * 8 + 5;  // 根据大小调整Y位置
  }
  
  delay(3000);
  
  // Part 3: 数字大小显示
  Serial.println("Displaying numbers in different sizes...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 20);
  gfx->println("Numbers:");
  
  // 小数字
  gfx->setTextSize(2);
  gfx->setCursor(50, 60);
  gfx->println("123");
  
  // 中等数字
  gfx->setTextSize(3);
  gfx->setCursor(50, 120);
  gfx->println("456");
  
  // 大数字
  gfx->setTextSize(4);
  gfx->setCursor(50, 220);
  gfx->println("789");
  
  delay(3000);
  
  // Part 4: 混合大小文本
  Serial.println("Displaying mixed size text...");
  gfx->fillScreen(BLACK);
  
  // 标题（大）
  gfx->setTextSize(3);
  gfx->setTextColor(YELLOW);
  gfx->setCursor(80, 30);
  gfx->println("TITLE");
  
  // 副标题（中）
  gfx->setTextSize(2);
  gfx->setTextColor(CYAN);
  gfx->setCursor(50, 100);
  gfx->println("Subtitle");
  
  // 正文（小）
  gfx->setTextSize(1);
  gfx->setTextColor(WHITE);
  gfx->setCursor(20, 150);
  gfx->println("Body text line 1");
  gfx->setCursor(20, 170);
  gfx->println("Body text line 2");
  gfx->setCursor(20, 190);
  gfx->println("Body text line 3");
  
  delay(3000);
  
  // Part 5: 动态大小变化
  Serial.println("Animating text size...");
  gfx->fillScreen(BLACK);
  
  for (int size = 1; size <= 5; size++) {
    gfx->fillScreen(BLACK);
    gfx->setTextSize(size);
    gfx->setTextColor(WHITE);
    
    // 居中显示
    int textWidth = 4 * size * 6;  // 估算宽度
    int x = (gfx->width() - textWidth) / 2;
    int y = (gfx->height() - size * 8) / 2;
    
    gfx->setCursor(x, y);
    gfx->println("SIZE");
    
    delay(1000);
  }
  
  Serial.println("Text size demonstration complete!");
}

void loop() {
  delay(1000);
}
