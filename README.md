# 📢 Smart Digital Notice Board (Arduino)

## 📌 Project Overview
Smart Digital Notice Board using Arduino and MAX7219 LED Matrix to display real-time messages with multiple modes.

---

## 🚀 Features
- Dynamic Message Queue
- Add / Edit / Delete Messages
- Undo Functionality
- Emergency Mode (Blink + Scroll)
- Info Mode (Static Display)
- Brightness & Speed Control
- Reverse Scrolling
- Real-time Serial Control

---

## 🛠️ Components Used
- Arduino UNO  
- MAX7219 LED Matrix  
- Breadboard  
- Jumper Wires  
- USB Cable  

---

## 🔌 Circuit Connections

| Arduino | LED Matrix |
|--------|-----------|
| 5V     | VCC       |
| GND    | GND       |
| 11     | DIN       |
| 13     | CLK       |
| 10     | CS        |

SPI Communication is used.

---

## ⚙️ Working
- User sends input via Serial Monitor  
- Arduino processes commands  
- Messages stored in queue  
- Display updates based on mode  

---

## 🧪 Commands

| Command | Function |
|--------|---------|
| on/off | Start/Stop |
| p | Pause |
| f/s | Speed control |
| b/d | Brightness |
| r | Reverse |
| clear | Remove all |
| remove | Delete last |
| del X | Delete index |
| undo | Undo |
| mode normal/info/emergency | Change mode |
| emergency TEXT | Emergency message |
| info TEXT | Info message |
| edit X TEXT | Edit message |

---

## 👨‍💻 Author
Maneesh
