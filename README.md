# threadPoolTask

Introduction
This README file documents the usage and execution of a multithreaded C application that encrypts/decrypts strings given by the user. The application works by allocating a thread to a string of 1024 characters for the encryption/decryption process.

Requirements
gcc
make

## Getting Started

These instructions will guide you on how to install and run the software on your local machine. 

### Prerequisites

Before you start, make sure you have the following installed on your Ubuntu machine:

- GCC compiler 
- Make
- Git (Optional, for cloning the repository)

You can install these using the following commands:

```bash
sudo apt update
sudo apt install build-essential
sudo apt install git
```

# Clone the project

```
git clone https://github.com/dolev146/threadPoolTask.git
```


# Compilation
To compile the program, you need to use make. In the root directory of the project, execute the following command in the terminal:

```
make
```

This will compile the code and generate the executable file named coder.

# Usage
The general syntax for executing the program is as follows:

./coder key [-e/-d]


Where:

key is the encryption/decryption key.
-e flag is for encryption.
-d flag is for decryption.

# Example
If you want to encrypt a string, run the program as follows:


```
./coder 3 -e
```


Then, type in the input string that you want to encrypt. You can stop the input process by pressing ctrl + d.

If you want to decrypt a string, run the program as follows:

```
./coder 3 -d
```

Then, type in the input string that you want to decrypt. You can stop the input process by pressing ctrl + d.

#Input from File
You can also provide input from a file. To do this, use the < operator followed by the filename. For instance, to decrypt text from text.txt, you would use:


```
./coder 1 -d < text.txt
```


















