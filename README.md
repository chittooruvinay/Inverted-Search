# Inverted-Search
🔍 Inverted Search – Data Structures Project (C)

A C-based implementation of an Inverted Search Engine using Data Structures. This project indexes words from multiple text files and allows fast searching by mapping each word to the files in which it appears, along with occurrence counts.

📌 Features

Indexes multiple text files into a searchable database

Fast keyword-based searching using an inverted index

Displays file names and word frequencies

Supports create, update, search, display, and save operations

Prevents duplicate file indexing

Persistent storage using backup files

🧠 How It Works
🗂️ Database Creation

Read multiple input text files

Extract words from each file

Store words in a hash table

Each word node maintains a linked list of file nodes with counts

🔎 Search Operation

User enters a keyword

Hash function locates the index

Displays list of files containing the word and frequency

🔄 Update Operation

Adds new files to the existing database

Updates word occurrences without rebuilding the entire index

💾 Save & Load

Database can be saved to a backup file

Database can be reloaded later without reprocessing files

🧩 Data Structures Used

Hash Table

Singly Linked Lists

Dynamic Memory Allocation

🛠️ Technologies Used

C Programming

File Handling

Hashing Techniques

Data Structures

📖 About

This project simulates the core working of a search engine using an inverted index. It enables efficient text searching across multiple files and demonstrates strong understanding of hashing, linked lists, and file-based data persistence.
