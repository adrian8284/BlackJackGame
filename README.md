
# 🃏 Blackjack Game (Work in Progress)

A personal Blackjack game project written in C++, designed for modularity and scalability using Object-Oriented Programming principles. The game currently runs in the terminal, with plans to add a GUI and deploy it on a personal website for public play.

---

## 🔧 Features (So Far)
- Core Blackjack gameplay (hit, stand, bust, draw, win/lose logic)
- CLI-based interface
- OOP structure (in progress): `Deck`, `Card`, `Player`, `Dealer`, `Game`, and `GameUI` classes
- Persistent cash balance and win streak logic
- Win/loss flavor text and badge system (e.g. “LUCKY”, “IN THE HOLE”, etc.)

---

## 🧠 In Progress
- Full OOP cleanup and modular logic separation (currently in `mainModular.cpp`, not runnable yet)
- GUI implementation (framework TBD)
- Visual card rendering (text-based or graphic)
- Hosting on personal website for portfolio use

---

## 🚀 How to Run
> **Note:** This is a C++ project.

1. Compile using g++ or your preferred compiler:
```bash
g++ -std=c++11 -o blackjack mainBlackJack.cpp
```

2. Run the program:
```bash
./blackjack
```

🚧 `mainModular.cpp` is currently a work in progress and may not compile or run properly yet.

---

## 📌 To Do
- [ ] Finalize class structure and hand rendering
- [ ] Improve player-dealer interaction loop
- [ ] Add persistent score saving
- [ ] Create GUI (possibly using SFML or Qt)
- [ ] Add animations or effects (even in CLI)
- [ ] Deploy as playable web app or downloadable binary

---

## 🤔 Why This Project?
This is more than just a game—it's a learning playground. It challenges me to write better code, understand how to modularize logic, and eventually build a complete product from backend logic to frontend experience.
