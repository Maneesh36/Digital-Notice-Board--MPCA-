# 📢 Smart Digital Notice Board (Arduino)

## 📌 Project Overview
This project implements a **Smart Digital Notice Board** using an Arduino and MAX7219 LED Matrix.  
It allows real-time message display with multiple modes such as scrolling text, static information, and emergency alerts.

---

## 🚀 Features
- 🔁 Dynamic Message Queue
- ✏️ Add, Edit, Delete Messages
- ↩️ Undo Functionality
- ⚡ Emergency Mode (Scrolling + Blinking)
- ℹ️ Info Mode (Static Display)
- 🎚️ Brightness Control
- ⏩ Speed Control
- 🔄 Reverse Scrolling Direction
- 🛑 Start/Stop System
- 💻 Real-time Control via Serial Monitor

---

## 🛠️ Components Used
- Arduino UNO  
- MAX7219 LED Matrix (4 modules)  
- Breadboard  
- Jumper Wires  
- USB Cable  

---

## 🔌 Circuit Connections

| Arduino Pin | LED Matrix |
|------------|------------|
| 5V         | VCC        |
| GND        | GND        |
| 11         | DIN        |
| 13         | CLK        |
| 10         | CS         |

👉 Communication Protocol: **SPI**

---

## ⚙️ How It Works
1. Arduino receives input via Serial Monitor  
2. Processes commands (add/edit/delete messages)  
3. Stores messages in a queue  
4. Displays output on LED Matrix  
5. Modes control display behavior:
   - Normal → scrolling messages  
   - Info → static display  
   - Emergency → blinking + continuous scroll  

---

## 🧪 Commands

| Command | Function |
|--------|---------|
| on / off | Start/Stop system |
| p | Pause/Resume |
| f / s | Increase/Decrease speed |
| b / d | Increase/Decrease brightness |
| r | Reverse direction |
| clear | Remove all messages |
| remove | Delete last message |
| del X | Delete message at index X |
| undo | Undo last action |
| mode normal/info/emergency | Change mode |
| emergency TEXT | Set emergency message |
| info TEXT | Set info message |
| edit X TEXT | Edit message at index X |

---

## 📸 Output
Displays scrolling text across LED matrix with different modes and real-time updates.

---

## 🧠 Concepts Used
- Embedded Systems  
- SPI Communication  
- Data Structures (Queue)  
- Real-time Input Handling  
- State-based System Design  

---

## 📎 GitHub Repository
This project is hosted here:
👉 https://github.com/Maneesh36/Digital-Notice-Board--MPCA-

---

## 👨‍💻 Author
- Maneesh
