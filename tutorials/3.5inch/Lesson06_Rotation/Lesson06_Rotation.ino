/*
 * Lesson 06: Rotation
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习如何旋转屏幕显示方向
 * 
 * 知识点：
 * - setRotation() 函数
 * - 不同旋转角度的效果
 * - 旋转对坐标的影响
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
  
  Serial.println("Lesson 06: Rotation");
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
  
  Serial.println("LCD initialized successfully!");
  
  // ==================== Lesson Content ====================
  
  // Part 1: 显示所有旋转角度
  Serial.println("Displaying all rotation angles...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    // 设置旋转角度
    gfx->setRotation(rotation);
    
    // 清屏
    gfx->fillScreen(BLACK);
    
    // 显示旋转角度信息
    gfx->setTextColor(WHITE);
    gfx->setTextSize(3);
    gfx->setCursor(50, 50);
    gfx->print("Rot: ");
    gfx->println(rotation);
    
    // 显示当前屏幕尺寸
    gfx->setTextSize(2);
    gfx->setCursor(50, 120);
    gfx->print("W: ");
    gfx->print(gfx->width());
    gfx->print(" H: ");
    gfx->println(gfx->height());
    
    // 绘制坐标轴
    int centerX = gfx->width() / 2;
    int centerY = gfx->height() / 2;
    
    // X轴（红色）
    gfx->drawLine(0, centerY, gfx->width(), centerY, RED);
    gfx->setTextColor(RED);
    gfx->setTextSize(2);
    gfx->setCursor(gfx->width() - 40, centerY - 30);
    gfx->print("X");
    
    // Y轴（绿色）
    gfx->drawLine(centerX, 0, centerX, gfx->height(), GREEN);
    gfx->setTextColor(GREEN);
    gfx->setCursor(centerX + 10, 20);
    gfx->print("Y");
    
    // 原点标记
    gfx->fillCircle(0, 0, 5, YELLOW);
    gfx->setTextColor(YELLOW);
    gfx->setTextSize(1);
    gfx->setCursor(10, 10);
    gfx->print("(0,0)");
    
    // 在四个角显示标记
    gfx->fillCircle(0, 0, 3, CYAN);
    gfx->fillCircle(gfx->width()-1, 0, 3, CYAN);
    gfx->fillCircle(0, gfx->height()-1, 3, CYAN);
    gfx->fillCircle(gfx->width()-1, gfx->height()-1, 3, CYAN);
    
    delay(3000);
  }
  
  // Part 2: 在不同旋转角度显示相同内容
  Serial.println("Displaying same content at different rotations...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    gfx->setRotation(rotation);
    gfx->fillScreen(BLACK);
    
    // 显示文本
    gfx->setTextColor(WHITE);
    gfx->setTextSize(4);
    
    // 居中显示
    int textWidth = 6 * 4 * 4;  // "TEST" 4个字符，size=4
    int x = (gfx->width() - textWidth) / 2;
    int y = (gfx->height() - 32) / 2;
    
    gfx->setCursor(x, y);
    gfx->println("TEST");
    
    // 显示旋转角度
    gfx->setTextSize(2);
    gfx->setTextColor(CYAN);
    gfx->setCursor(20, 20);
    gfx->print("Rotation: ");
    gfx->println(rotation);
    
    delay(3000);
  }
  
  // Part 3: 旋转对图形的影响
  Serial.println("Showing graphics at different rotations...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    gfx->setRotation(rotation);
    gfx->fillScreen(BLACK);
    
    int centerX = gfx->width() / 2;
    int centerY = gfx->height() / 2;
    
    // 绘制矩形
    gfx->drawRect(centerX - 60, centerY - 40, 120, 80, RED);
    
    // 绘制圆形
    gfx->drawCircle(centerX, centerY, 50, GREEN);
    
    // 绘制线条（指向右上角）
    gfx->drawLine(centerX, centerY, centerX + 60, centerY - 60, BLUE);
    
    // 显示角度
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2);
    gfx->setCursor(20, 20);
    gfx->print("Rot: ");
    gfx->println(rotation);
    
    delay(3000);
  }
  
  // Part 4: 旋转角度说明
  Serial.println("Rotation angle reference...");
  gfx->setRotation(0);  // 恢复默认
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 50);
  gfx->println("Rotation:");
  gfx->setCursor(50, 100);
  gfx->println("0 = 0 deg");
  gfx->setCursor(50, 150);
  gfx->println("1 = 90 deg");
  gfx->setCursor(50, 200);
  gfx->println("2 = 180 deg");
  gfx->setCursor(50, 250);
  gfx->println("3 = 270 deg");
  
  delay(5000);
  
  Serial.println("Rotation demonstration complete!");
}

void loop() {
  delay(1000);
}
