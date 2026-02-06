# Lesson 10: Notification Interface

## Course Objectives

Learn to create a notification interface and master card design and icon-text combination.

## Key Concepts

### 1. Notification Card Design

#### Card Center Layout
Calculate card position to center it:

```cpp
int cardX = 30;
int cardY = 80;
int cardW = 260;
int cardH = 200;
gfx->fillRect(cardX, cardY, cardW, cardH, WHITE);
gfx->drawRect(cardX, cardY, cardW, cardH, BLACK);
```

#### Card Style
- **White Background**: Stand out
- **Black Border**: Clear boundary
- **Appropriate Margins**: Leave screen margins

### 2. Icon Design

#### Circular Icon Background
Use circle as icon background:

```cpp
int iconX = cardX + 30;
int iconY = cardY + cardH / 2;
gfx->fillCircle(iconX, iconY, 25, BLUE);
```

#### Icon Content
Display text on circular background:

```cpp
gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(iconX - 8, iconY - 10);
gfx->println("!");
```

### 3. Text Content Layout

#### Multi-line Text
Use different Y coordinates to display multi-line text:

```cpp
gfx->setCursor(cardX + 70, cardY + 40);
gfx->println("New Message");
gfx->setCursor(cardX + 70, cardY + 80);
gfx->println("You have 3");
gfx->setCursor(cardX + 70, cardY + 120);
gfx->println("unread items");
```

### 4. Close Button

#### Button Position
Located at top-right corner of card:

```cpp
int btnX = cardX + cardW - 25;
int btnY = cardY + 10;
gfx->fillRect(btnX, btnY, 20, 20, RED);
```

#### Button Content
Display "X" symbol:

```cpp
gfx->setTextColor(WHITE);
gfx->setTextSize(2);
gfx->setCursor(btnX + 5, btnY + 2);
gfx->print("X");
```

## Code Explanation

### Card Layout

```cpp
// Notification card (centered display, leave margins)
int cardX = 30;
int cardY = 80;
int cardW = 260;
int cardH = 200;
gfx->fillRect(cardX, cardY, cardW, cardH, WHITE);
gfx->drawRect(cardX, cardY, cardW, cardH, BLACK);
```

### Icon and Text

```cpp
// Icon area (left side)
gfx->fillCircle(iconX, iconY, 25, BLUE);
gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(iconX - 8, iconY - 10);
gfx->println("!");

// Notification content (middle area)
gfx->setTextColor(BLACK);
gfx->setTextSize(2);
gfx->setCursor(cardX + 70, cardY + 40);
gfx->println("New Message");
```

## Expected Result

Display notification interface, including:
- White notification card (centered)
- Blue circular icon (left side, with exclamation mark)
- Notification text content (middle)
- Red close button (top-right corner)

## Extended Exercises

1. **Add Multiple Notifications**:
   - Create notification list
   - Implement notification scrolling

2. **Add Animation Effects**:
   - Fade in/out
   - Slide effects

3. **Implement Interaction Functions**:
   - Click close button
   - Click notification to view details

## Frequently Asked Questions

**Q: How to adjust card size?**
- Modify `cardW` and `cardH` variables
- Ensure content fits card size

**Q: How to change icon style?**
- Use different graphics (rectangle, triangle, etc.)
- Use different icon symbols

## Next Step

After completing this course, you can:
- Create your own notification system
- Add notification management functions
- Implement notification interactions
