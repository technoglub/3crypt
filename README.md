# 3crypt
A simple command-line program for encrypting and decrypting files on OpenBSD, FreeBSD, GNU/Linux, and Microsoft Windows, built upon the
Threefish block cipher and the Skein cryptographic hash function, providing 512 bits of symmetric security.

![Alt text](/../screenshots/plaintext.png?raw=true "Before 3crypt Encryption")
![Alt text](/../screenshots/ciphertext.png?raw=true "After 3crypt Encryption")

## Buildtime Dependencies
### (Required on all supported systems)
-   [ssc](https://github.com/stuartcalder/ssc) header and library files.
-   __meson__ frontend build system.
-   __ninja__ backend build system.
### (Required on OpenBSD, FreeBSD, and GNU/Linux)
-   __ncurses__ header and library files.
### (Required on GNU/Linux only)
-   __GCC 7+__ compiler.
### (Required on Microsoft Windows only)
-   __Windows Vista/Server 2008__ or later.
-   __Visual Studio 2019__ development suite.
## How To Encrypt Files
```
3crypt -e -i $filename
```
or
```
3crypt --encrypt --input-file $filename
```
## How To Decrypt Files
```
3crypt -d -i $filename
```
or
```
3crypt --decrypt --input-file $filename
```
## How To Build 3crypt With Meson
### BSD and Linux build instructions
1. build and install [ssc](https://github.com/stuartcalder/ssc).
2. git clone [3crypt](https://github.com/stuartcalder/3crypt) anywhere.
3. cd into the 3crypt project directory.
	- On BSD systems execute the following...
```
$ meson --backend=ninja builddir
```
	- On Linux systems execute the following...
```
$ meson --backend=ninja --prefix=/usr builddir
```
4. cd into builddir, and execute the following...
```
$ ninja
# ninja install
```
5. 3crypt should now be successfully installed on your system.
### On Microsoft Windows systems
1. Build and install [ssc](https://github.com/stuartcalder/ssc).
2. git clone [3crypt](https://github.com/stuartcalder/3crypt) anywhere.
3. Open a command-prompt, **specifically** you must open __"x64 Native Tools Command Prompt for VS 2019"__.
	* If you open a regular cmd.exe console, you will not be able to build 3crypt.
4. cd into the 3crypt project directory, and execute the following...
```
meson --backend=ninja builddir
```
5. cd into builddir, and execute the following...
```
ninja
```
6. 3crypt should now be successfully installed on your Windows system.
7. You may now [add 3crypt to your PATH](https://stackoverflow.com/questions/9546324/adding-directory-to-path-environment-variable-in-windows), or invoke it directly by executing the following...
```
C:\bin\3crypt --encrypt --input-file plaintext --output-file ciphertext
```
