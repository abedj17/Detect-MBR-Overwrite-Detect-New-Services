#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include<fstream>
#include<string>

using std::isprint;
using std::cout;
using std::cin;
using std::move;
using std::size_t;
using std::string;

constexpr size_t MBR_SIZE = 512;
constexpr size_t BYTES_PER_LINE = 4;
constexpr size_t NUMBER_OF_LINES = MBR_SIZE / BYTES_PER_LINE;

// Converts 4 least significant bits of 'c' to corresponding
// hexadecimal string.
static string fourBitsToString(char c)
{
    string s = " ";

    if (c >= 0 && c <= 9) {
        s[0] = '0' + c;
    } else {
        c -= 10;
        s[0] = 'A' + c;
    }

    return move(s);
}

// Converts a character to its hexadecimal representation.
static string charToHex(char c)
{
    char lo = c & 0xf;
    char hi = (c >> 4) & 0xf;
    string s;
    char chars[] = {hi, lo};

    for (char ch : chars) {
        s += fourBitsToString(ch);
    }

    return std::move(s);
}

// Prints the MBR to file.
static void PrintMBR_f(char buffer[MBR_SIZE], std::ofstream &output_file)
{
    size_t byteIndex = 0;
    string lineSeparator;
    string columnSeparator;

    for (size_t i = 0; i < NUMBER_OF_LINES; i++) {
        output_file << lineSeparator;
        lineSeparator = '\n';
        columnSeparator = "";

        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            string ch = charToHex(buffer[byteIndex++]);
            output_file << columnSeparator << ch;
            columnSeparator = " ";
        }

        output_file << ' ';

        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            char c = buffer[byteIndex - BYTES_PER_LINE + j];
            output_file << (isprint((unsigned int) c) ? c : '.');
        }
    }
    output_file << "\n##########################################" << std::endl;
}

// Prints the MBR to console.
string PrintMBR(char buffer[MBR_SIZE])
{
    string mystring;
    size_t byteIndex = 0;
    string lineSeparator;
    string columnSeparator;

    for (size_t i = 0; i < NUMBER_OF_LINES; i++) {
        mystring += lineSeparator;
        lineSeparator = '\n';
        columnSeparator = "";

        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            string ch = charToHex(buffer[byteIndex++]);
            mystring += columnSeparator + ch;
            columnSeparator = " ";
        }

        mystring += ' ';

        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            char c = buffer[byteIndex - BYTES_PER_LINE + j];
            mystring += (isprint((unsigned int) c) ? c : '.');
        }
    }
    mystring += "\n##########################################" ;
    return mystring;
}


// Reads the entire master boot record (MBR) into lpBuffer.
// Expects lpBuffer to point to a memory point that may
// hold at leasst 512 bytes.
static DWORD ReadMBR(PCHAR lpBuffer)
{

    HANDLE diskHandle = CreateFile(
            TEXT("\\\\.\\PhysicalDrive0"),
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

    char* buffer = new char[MBR_SIZE];
    if (diskHandle == INVALID_HANDLE_VALUE){
        cout << "error while reading the mbr!!!\n";
        return -1;
    }

    ReadFile(
            diskHandle,
            lpBuffer,
            MBR_SIZE,
            NULL,
            NULL);



    return GetLastError();
}

int main() {

    char buffer[MBR_SIZE];
    string line,mystring,mystring2;
    std::ofstream oldfile;

    
    // writing the buffer into the file buffer.txt
    oldfile.open("buffer.txt");
    ReadMBR(buffer);
    PrintMBR_f(buffer, oldfile);
    oldfile << std::endl;
    oldfile.close();



    // reading the MBR into mystring var.
    //ReadMBR(buffer);
    //mystring = PrintMBR(buffer);
    //cout << mystring;





    cin.get();
    return 3;
}