# Lesson 08: Menu Interface

## Course Objectives

Learn to create a menu interface and master menu item layout and highlight display.

## Key Concepts

### 1. Title Bar Design

Use filled rectangle to create title bar:

```cpp
gfx->fillRect(0, 0, 320, 50, BLUE);
drawCenteredText("MENU", 10, WHITE, 2);
```

### 2. Menu Item Layout

#### Menu Item Array
Use array to store menu items and colors:

```cpp
const char* menuItems[] = {"Settings", "Data", "About", "Exit"};
uint16_t menuColors[] = {WHITE, CYAN, YELLOW, RED};
```

#### Menu Item Spacing
Maintain appropriate vertical spacing:

```cpp
menuY += 60;  // Each menu item spacing 60 pixels
```

### 3. Highlight Current Option

Use background color to highlight currently selected menu item:

```cpp
if (i == 0) {
  gfx->fillRect(20, menuY - 5, 280, 50, CYAN);
  gfx->setTextColor(BLACK);
} else {
  gfx->setTextColor(menuColors[i]);
}
```

### 4. Menu Item Indicator

Use ">" symbol to represent menu items:

```cpp
gfx->print("> ");
gfx->println(menuItems[i]);
```

## Code Explanation

### Menu Loop

```cpp
gfx->setTextSize(2);
for (int i = 0; i < 4; i++) {
  // Highlight current item
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
```

## Expected Result

Display menu interface, including:
- Blue title bar
- 4 menu items
- First item highlighted (cyan background)
- Different colored menu items

## Extended Exercises

1. **Add Menu Navigation**:
   ```cpp
   int currentMenu = 0;
   void navigateMenu(int direction) {
     // Handle menu navigation
   }
   ```

2. **Add Menu Functions**:
   - Click menu item to execute corresponding operation
   - Add submenus

3. **Optimize Visual Effects**:
   - Add icons
   - Add animation effects
   - Improve highlight style

## Frequently Asked Questions

**Q: How to change number of menu items?**
- Modify `menuItems` and `menuColors` array size
- Adjust loop count and spacing

**Q: How to implement menu scrolling?**
- Use offset to adjust menu item positions
- Only display visible menu items

## Next Step

After completing this course, you can:
- Create your own menu system
- Add menu interaction functions
- Implement multi-level menus
