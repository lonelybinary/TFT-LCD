# Lesson 08: Menu Interface

## Course Objectives

Build a **menu** — a list of options with one item highlighted as "selected". You'll learn to
store items in an array and highlight the current choice.

## Key Concepts

### 1. A title bar

A filled rectangle across the top makes a clean title bar:

```cpp
gfx->fillRect(0, 0, 320, 50, BLUE);
drawCenteredText("MENU", 10, WHITE, 2);
```

### 2. Laying out the menu items

#### Store items in arrays
Keep the menu text and each item's color in matching arrays:

```cpp
const char* menuItems[] = {"Settings", "Data", "About", "Exit"};
uint16_t menuColors[] = {WHITE, CYAN, YELLOW, RED};
```

#### Space the items evenly
Move down a fixed amount for each item:

```cpp
menuY += 60;  // 60 pixels between items
```

### 3. Highlighting the selected item

To show which item is selected, draw a colored bar behind it and switch the text to a
contrasting color:

```cpp
if (i == 0) {  // item 0 is selected
  gfx->fillRect(20, menuY - 5, 280, 50, CYAN);  // highlight bar
  gfx->setTextColor(BLACK);                     // dark text on light bar
} else {
  gfx->setTextColor(menuColors[i]);             // normal color
}
```

### 4. A selection arrow

A `">"` in front of each item makes the list feel like a menu:

```cpp
gfx->print("> ");
gfx->println(menuItems[i]);
```

## Code Explanation

### The menu-drawing loop

```cpp
gfx->setTextSize(2);
for (int i = 0; i < 4; i++) {
  // Highlight the selected item (item 0 here)
  if (i == 0) {
    gfx->fillRect(20, menuY - 5, 280, 50, CYAN);
    gfx->setTextColor(BLACK);
  } else {
    gfx->setTextColor(menuColors[i]);
  }

  gfx->setCursor(40, menuY);
  gfx->print("> ");
  gfx->println(menuItems[i]);

  menuY += 60;  // move down for the next item
}
```

## Expected Result

A menu screen showing:
- A blue title bar
- Four menu items
- The first item highlighted with a cyan bar
- The other items in their own colors

## Extended Exercises

1. **Move the selection** (e.g. with a button later on):
   ```cpp
   int currentMenu = 0;
   void navigateMenu(int direction) {
     // change currentMenu, then redraw
   }
   ```

2. **Make items do something** — run an action when an item is chosen, or open a submenu.

3. **Polish it** — add icons, animation, or a nicer highlight style.

## Frequently Asked Questions

**Q: How do I change the number of menu items?**
- Edit the `menuItems` and `menuColors` arrays, then update the loop count and spacing to match.

**Q: How do I scroll a long menu?**
- Track an offset and only draw the items that fit on screen, shifting the list as the
  selection moves.

## Next Step

- [Lesson 09: Data Monitoring Interface](../Lesson09_DataMonitoring/README.md) — build a dashboard with cards.
