/*
 * Lesson 08: Menu Interface
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习创建菜单界面
 * 
 * 知识点：
 * - 菜单界面设计
 * - 高亮当前选项
 * - 标题栏设计
 * - 菜单项布局
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
  
  Serial.println("Lesson 08: Menu Interface");
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
  
  // 菜单界面
  Serial.println("Displaying Menu Interface");
  gfx->fillScreen(BLACK);
  
  // 标题栏
  gfx->fillRect(0, 0, 320, 50, BLUE);
  drawCenteredText("MENU", 10, WHITE, 2);
  
  // 菜单项
  int menuY = 70;
  const char* menuItems[] = {"Settings", "Data", "About", "Exit"};
  uint16_t menuColors[] = {WHITE, CYAN, YELLOW, RED};
  
  gfx->setTextSize(2);
  for (int i = 0; i < 4; i++) {
    // 高亮当前项（第一项）
    if (i == 0) {
      gfx->fillRect(20, menuY - 5, 280, 50, CYAN);
      gfx->setTextColor(BLACK);
    } else {
      gfx->setTextColor(menuColors[i]);
    }
    
    gfx->setCursor(40, menuY);
    gfx->print("> ");
    gfx->println(menuItems[i]);
    
    menuY += 60;
  }
  
  Serial.println("Menu Interface display complete!");
}

void loop() {
  delay(1000);
}
