## About The Project

MiniDBMS is a lightweight SQL-inspired Database Management System built entirely in C from scratch. The project was developed to understand the core principles behind modern relational database systems, including query processing, data storage, schema management, and execution engines.

The database implements a complete query execution pipeline where SQL-like commands are tokenized, parsed into internal data structures, validated against table metadata, and executed through a custom storage engine. Data is stored persistently using file-based storage, allowing records and table schemas to be retained between program executions.

Currently, MiniDBMS supports essential database operations such as table creation, data insertion, and data retrieval through SELECT queries. The project follows a modular architecture consisting of a Lexer, Parser, Executor Engine, and Storage Engine, closely resembling the design of real-world database systems.

Built without external database libraries, MiniDBMS provides practical experience with systems programming concepts such as file handling, memory management, data structures, parsing techniques, and software architecture. It serves as both a learning platform for database internals and a foundation for implementing advanced features such as filtering, indexing, joins, query optimization, and transactions in future versions.

# Installation

## Prerequisites
Before running MiniDBMS, ensure the following are installed on your system:
* GCC Compiler
* Make (optional)
* Linux/macOS Terminal or Windows Command Prompt

Verify GCC installation:
```bash
gcc --version
```

---

## Clone Repository
```bash
git clone https://github.com/yourusername/MiniDBMS.git
cd MiniDBMS
```

---

## Build Project
Compile all source files:

```bash
gcc *.c -o mini_dbms
```

Or, if using multiple directories:

```bash
gcc src/*.c -Iinclude -o mini_dbms
```

---

## Run
```bash
./mini_dbms
```

You should see:
```text
mini_sql >
```

The database is now ready to accept SQL-like commands.

# Project Structure
```text
MiniDBMS/
│
├── src/
│   ├── lexer.c
│   ├── parser.c
│   ├── executor.c
│   ├── storage.c
│   └── main.c
│
├── include/
│   ├── lexer.h
│   ├── parser.h
│   ├── executor.h
│   └── storage.h
│
├── database/
│   ├── students.tbl
│   └── students.meta
│
├── README.md
└── Makefile
```

# Usage
MiniDBMS provides a command-line SQL interface.

Example:
```text
mini_sql >
```

Users can execute SQL-like commands directly from the terminal.

---

## Creating a Table
```sql
CREATE TABLE students (
    id INT,
    name TEXT,
    age INT
);
```

Output:

```text
Table created successfully.
```

---

## Inserting Data

```sql
INSERT INTO students
VALUES (1, 'Aniket', 22);
```

Output:

```text
1 row inserted.
```

---

## Retrieving All Records

```sql
SELECT * FROM students;
```

Output:

```text
id              name            age
---------------------------------------
1               Aniket          22
```

---

## Retrieving Specific Columns

```sql
SELECT id, name
FROM students;
```

Output:

```text
id              name
-------------------------
1               Aniket
```

# Supported Queries

Current Version:

✅ CREATE TABLE
✅ INSERT INTO
✅ SELECT *
✅ SELECT column1, column2

Future Versions:

🔄 UPDATE
🔄 DELETE
🔄 JOIN
🔄 INDEXING
🔄 TRANSACTIONS

# Example Session

```text
mini_sql > CREATE TABLE students (id INT, name TEXT, age INT );

Table created successfully.

mini_sql > INSERT INTO students
           VALUES (1, 'Aniket', 22);

1 row inserted.

mini_sql > INSERT INTO students VALUES (2, 'John', 21);

1 row inserted.

mini_sql > SELECT * FROM students;

id              name            age
---------------------------------------
1               Aniket          22
2               John            21
```

# Technical Highlights

* Built entirely in C
* Custom SQL lexer and parser
* Abstract Syntax Tree (AST) generation
* Metadata-driven execution engine
* File-based storage engine
* Modular architecture
* Persistent data storage
* Dynamic query execution
* Schema management
* Command-line SQL interface

# Limitations

Current version focuses on core database concepts and does not yet include:

* Query optimization
* Indexing
* Concurrency control
* Transactions
* Multi-table joins
* Network access

These features are planned for future development.

# Educational Value

This project was developed to understand how real database systems such as MySQL, PostgreSQL, and SQLite work internally.

Through the implementation of MiniDBMS, concepts such as lexical analysis, parsing, query execution, storage management, metadata handling, and systems programming were explored from first principles.

The project serves as a foundation for future work involving database engines, operating systems, compilers, and storage systems.
