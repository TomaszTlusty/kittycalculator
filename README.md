<!--
  NOTE TO YOU (delete this whole comment before shipping):
  This is a SKELETON, not a finished README. Replace every [bracketed] prompt
  with your own words, your own photos, and real values. Hack Club rejects
  AI-written READMEs, so the prose, photos and BOM links have to be yours.
  The technical bits (wiring table, "how it works", BOM rows) are facts about
  your build that I've pre-filled to save you time — check them and edit freely.

  Suggested repo layout:
    README.md
    JOURNAL.md
    firmware/cat_eyes_lcd.ino
    cad/            <- your enclosure source + exported STL
    photos/         <- build photos, CAD screenshot, wiring diagram
-->

# Kitty Calculator

[One or two sentences, your own words: what is this? e.g. "A small desk
companion — a 3D-printed cat whose 16x2 LCD shows blinking pixel eyes,
driven by an Arduino."]

## What it does

[Describe the behaviour of YOUR finished build: the eyes blink, look around,
react to a keypad press, etc. Write what it actually does once it's working.]

## Demo

[Link to a short video of the working hardware. Upload the clip to this repo
and paste the link here — "eyes blinking" is enough.]

## Photos

[Insert real photos once you have them:]

![Assembled build](photos/assembled.jpg)
![Inside / wiring](photos/wiring.jpg)
![Enclosure in CAD](photos/cad.png)

## How it works

The 16x2 LCD is a *character* display (HD44780). It can't address single pixels,
but it has 8 user-definable 5x8 characters. Each cat eye is one custom character;
the firmware swaps an "open" glyph and a "closed" glyph to make it blink.

[Add anything specific to your version — extra expressions, keypad interaction, etc.]

## Wiring

4-bit parallel mode:

| LCD pin        | Connects to              |
| -------------- | ------------------------ |
| VSS (1)        | GND                      |
| VDD (2)        | 5V                       |
| V0 (3)         | 10k pot wiper (contrast) |
| RS (4)         | D12                      |
| RW (5)         | GND                      |
| E (6)          | D11                      |
| D4 (11)        | D5                       |
| D5 (12)        | D4                       |
| D6 (13)        | D3                       |
| D7 (14)        | D2                       |
| A (15)         | 5V (via ~220Ω)           |
| K (16)         | GND                      |

> If you instead solder an I2C backpack onto the LCD, ignore the table above:
> it becomes SDA→A4, SCL→A5, VCC→5V, GND→GND, and you switch to the
> `LiquidCrystal_I2C` library. Update this section to match what you built.

[Add a wiring diagram image — make one in Fritzing or annotate a clear photo:]

![Wiring diagram](photos/wiring-diagram.png)

## Firmware

See [`firmware/cat_eyes_lcd.ino`](firmware/cat_eyes_lcd.ino). Open it in the
Arduino IDE, pick your board and port, and upload.

[Note what you changed or added so it's clearly yours — new glyphs, animations,
keypad handling, etc.]

## Bill of Materials (BOM)

| #  | Part                                   | Qty  | Link     | Approx. price |
| -- | -------------------------------------- | ---- | -------- | ------------- |
| 1  | Arduino Uno clone                      | 1    | [link]   | [zł]          |
| 2  | 4x4 matrix keypad shield               | 1    | [link]   | [zł]          |
| 3  | 16x2 character LCD (HD44780, blue)     | 1    | [link]   | [zł]          |
| 4  | 10k potentiometer (contrast)           | 1    | [link]   | [zł]          |
| 5  | Jumper wires (M-M / M-F)               | ~10  | [link]   | [zł]          |
| 6  | 3D-printed enclosure (your design)     | 1    | cad/     | filament      |
| 7  | M3 screws + standoffs                  | a few| [link]   | [zł]          |
| 8  | USB-B cable                            | 1    | [link]   | [zł]          |

<!-- Polish suppliers you can link: Botland, Kamami, Nettigo, or AliExpress.
     Put in the actual links you used, and the prices you actually paid. -->

## Build notes

[A few honest lines: how you built it, what went wrong, what you'd change.
Good raw material for the journal too.]

## License

[Optional — e.g. MIT for the code, CC-BY for the CAD. Your call.]
