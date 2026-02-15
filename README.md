# mygit-CLI

A minimal version control system built in C++ to understand Git internals — including HEAD tracking, snapshot commits, and metadata persistence.

---

## Features

- Initialize a repository
- Stage files
- Create snapshot-based commits
- Maintain a HEAD pointer
- Store commit metadata (message + timestamp)
- View commit history

---

## How It Works

- `.mygit/HEAD` stores the latest commit ID.
- Staged files are copied into `.mygit/staging/`.
- Each commit creates a snapshot inside `.mygit/commits/<id>/`.
- Metadata is stored in `meta.txt`.

---

---

## Project Structure

mygit-CLI/
│
├── main.cpp
├── Repository.h / Repository.cpp
├── Commit.h / Commit.cpp
└── .mygit/ (generated at runtime)


---

## Tech Stack

- C++17
- std::filesystem
- File I/O
- CLI argument parsing

---

## Purpose

Built to understand how Git manages snapshots, commit tracking, and repository structure internally.
---

## Future Improvements

- Add parent commit tracking
- Implement branching support
- Improve timestamp formatting
- Add hash-based commit IDs


