# Lesson 10: Notification Interface

## Course Objectives

Build a **notification card** — the kind of pop-up you see on a phone, with an icon, a
message, and a close button.

## Key Concepts

### 1. The notification card

#### A centered panel
Use a filled rectangle for the card, with a border around it:

```cpp
int cardX = 30;
int cardY = 80;
int cardW = 260;
int cardH = 200;
gfx->fillRect(cardX, cardY, cardW, cardH, WHITE);  // white panel
gfx->drawRect(cardX, cardY, cardW, cardH, BLACK);  // black border
```

#### Card style choices
- **White background** so it stands out.
- **Black border** for a clear edge.
- **Margins** around the card so it doesn't touch the screen edges.

### 2. An icon

#### A circular icon background
A filled circle makes a nice icon badge:

```cpp
int iconX = cardX + 30;
int iconY = cardY + cardH / 2;
gfx->fillCircle(iconX, iconY, 25, BLUE);
```

#### Symbol inside the icon
Print a symbol (like `"!"`) on top of the circle:

```cpp
gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(iconX - 8, iconY - 10);  // nudge so it centers
gfx->println("!");
```

### 3. Laying out the message

Print each line of the message at a different y position:

```cpp
gfx->setCursor(cardX + 70, cardY + 40);
gfx->println("New Message");
gfx->setCursor(cardX + 70, cardY + 80);
gfx->println("You have 3");
gfx->setCursor(cardX + 70, cardY + 120);
gfx->println("unread items");
```

### 4. A close button

#### Position it in the top-right corner
Compute its spot relative to the card so it always sits in the corner:

```cpp
int btnX = cardX + cardW - 25;
int btnY = cardY + 10;
gfx->fillRect(btnX, btnY, 20, 20, RED);
```

#### An "X" inside it

```cpp
gfx->setTextColor(WHITE);
gfx->setTextSize(2);
gfx->setCursor(btnX + 5, btnY + 2);
gfx->print("X");
```

## Code Explanation

### The card

```cpp
// Centered card with margins
int cardX = 30;
int cardY = 80;
int cardW = 260;
int cardH = 200;
gfx->fillRect(cardX, cardY, cardW, cardH, WHITE);
gfx->drawRect(cardX, cardY, cardW, cardH, BLACK);
```

### Icon and text

```cpp
// Icon (left side)
gfx->fillCircle(iconX, iconY, 25, BLUE);
gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(iconX - 8, iconY - 10);
gfx->println("!");

// Message (middle)
gfx->setTextColor(BLACK);
gfx->setTextSize(2);
gfx->setCursor(cardX + 70, cardY + 40);
gfx->println("New Message");
```

## Expected Result

A notification screen showing:
- A centered white card
- A blue circular icon with a "!" (left side)
- The message text (middle)
- A red close button with an "X" (top-right corner)

## Extended Exercises

1. **Show several notifications** — make a list and let it scroll.

2. **Add animation** — fade the card in/out or slide it onto the screen.

3. **Make it interactive** — react when the close button or the card is pressed (you'd add a
   button or touch input for this).

## Frequently Asked Questions

**Q: How do I resize the card?**
- Change `cardW` and `cardH`. Because the icon, text, and button are positioned relative to
  the card, they'll move with it — just check everything still fits.

**Q: How do I change the icon?**
- Swap the circle for another shape (rectangle, triangle), or print a different symbol.

## Next Step

- [Lesson 11: Clock Display](../Lesson11_Clock/README.md) — the final project: an analog clock face.
