/***
 * app.h template 
 * Author: David Aledo 
 * Date: 15/01/2019
 */

// Define your parameters here:

// Example: sizes of files:
#define RFILE_SIZE 0x0A // Example file for saving input
#define WFILE_SIZE 0x0A // Example file for saving output


// Example: offsets (to the SYS_AXI_BASE address) and sizes for your IP ports:
#define IP_INS_OFFSET  0x10000 // IP INSTRUCTION PORT OFFSET
#define IP_IN_OFFSET   0x20000 // IP INPUT PORT OFFSET
#define IP_OUT_OFFSET  0x40000 // IP OUTPUT PORT OFFSET
#define IP_IN_SIZE 0x0A     // should same as rfile size    
#define IP_OUT_SIZE 0x0A    // should same as wfile size  

// INSTRUCTION CODE FOR IP
#define IP_INS_RESET 0
#define IP_INS_ADD 0xAA
#define IP_INS_MULT 0xBB
#define IP_INS_MIRROR 0xCC
