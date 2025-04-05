# payfair-cipher
This project implements the Playfair cipher, a classical symmetric encryption method



---

# Playfair Cipher

## Description
This project implements the Playfair cipher, a classical symmetric encryption method. The program uses a 5x5 table to encrypt and decrypt messages, where the letter "W" is replaced by "V" and consecutive repeating letters in the message are replaced with "X".

## Features
- Supports encryption and decryption of text.
- Uses a key to generate the Playfair table.
- Processes the text by removing spaces and handling letter replacements.
- Automatically adds the letter "X" if the message length is odd.

## How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/playfair-cipher.git
   ```

2. Navigate to the project directory:

   ```bash
   cd playfair-cipher
   ```

3. Compile the program:

   ```bash
   gcc -o playfair_cipher playfair_cipher.c
   ```

4. Run the program:

   ```bash
   ./playfair_cipher
   ```

   Example:

   - Input: Key "SeCReT", Text "Hello world"
   - Output: Encrypted and decrypted text.

## Example Usage
### Encrypt:
```c
playfair_encrypt("SeCReT", "Hello world")
```

### Output:
```
"IS JZ JQ XN TK JC"
```

### Decrypt:
```c
playfair_decrypt("SeCReT", "IS JZ JQ XN TK JC")
```

### Output:
```
"HELLO WORLD"
```

