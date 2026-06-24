# Lesson 09: Data Monitoring Interface

## Course Objectives

Build a **dashboard** that shows several readings at once using "card" panels, with progress
bars to make the numbers easy to read at a glance.

## Key Concepts

### 1. Card-style layout

A **card** is just a bordered panel that groups related info. Draw one with an outlined
rectangle:

```cpp
gfx->drawRect(30, 100, 120, 100, CYAN);
```

#### Tips for cards
- **Place them side by side** so several fit on screen.
- **Keep them the same size** for a tidy look.
- **Leave a gap** between cards.

### 2. Showing data visually

#### Progress bars
A progress bar turns a number into an easy-to-read bar (we built this helper in Lesson 7):

```cpp
drawProgressBar(40, 170, 100, 15, 45, CYAN, GREEN);
```

#### Big numbers
Use a larger text size to make the headline value stand out:

```cpp
gfx->setTextSize(3);
gfx->println("45%");
```

### 3. Multiple cards

#### Card 1 (CPU)
- Position: left side (x = 30)
- Border: `CYAN`
- Value: 45%

#### Card 2 (MEM)
- Position: right side (x = 170)
- Border: `YELLOW`
- Value: 62%

### 4. An overall status

A single label can summarize how things are doing:

```cpp
drawLabel("OK", 150, 225, GREEN, BLACK, 2);
```

## Code Explanation

### Drawing one card

```cpp
// CPU card (left side)
gfx->drawRect(30, 100, 120, 100, CYAN);  // card border

gfx->setTextColor(CYAN);
gfx->setTextSize(2);
gfx->setCursor(40, 110);
gfx->println("CPU");           // card title

gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(40, 140);
gfx->println("45%");           // big value

drawProgressBar(40, 170, 100, 15, 45, CYAN, GREEN);  // bar
```

### The progress-bar helper

```cpp
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  gfx->drawRect(x, y, width, height, bgColor);
  int fillWidth = (width * percent) / 100;
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}
```

## Expected Result

A dashboard showing:
- A title and separator
- A CPU card (45%)
- A memory card (62%)
- An overall status label (OK)

## Extended Exercises

1. **Add more cards** — disk usage, network traffic, temperature.

2. **Update the data live**:
   ```cpp
   void updateMonitoringData() {
     // re-read CPU, memory, etc., then redraw the cards
   }
   ```

3. **Add a chart** — a line chart, bar chart, or simple gauge.

## Frequently Asked Questions

**Q: How do I resize a card?**
- Change the width and height in its `drawRect()` call, and make sure the contents still fit.

**Q: How do I fit more cards?**
- Plan their x/y positions around the screen width. You can also stack cards in rows.

## Next Step

- [Lesson 10: Notification Interface](../Lesson10_Notification/README.md) — build a notification card.
