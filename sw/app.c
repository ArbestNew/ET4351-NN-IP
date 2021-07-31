/*******************************************************************************
* app.c template
* 
* It defines the main function of the embedded sofware application and a 
* interrupt handler function.
* 
* version 1.0 
*   author: unknown
*   date: unknown
* version 2.0
*   author: David Aledo
*   date: 15/01/2019
********************************************************************************/

// Necessary libraries. Don't remove them!
#include "app.h"
#include "mmap.h"
#include "isrsupport.h"
#include "dbg_console.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// Add your libraries here:

// Debug stuff. Don't touch it!
#define halt() DBGC_HALT = 1

// debug setting
#define PRINT_DATA_DETAIL 1

// Declare your peripheral poiters and initialize them to their BASE addresses:
uint32_t *RFILE = (uint32_t *)SYS_RFILE_RAM_BASE; // Example of a file for reading
// uint8_t *RFILE = (uint8_t *)SYS_RFILE_RAM_BASE; // Example of a file for reading in text mode
uint32_t *WFILE = (uint32_t *)SYS_WFILE_RAM_BASE; // Example of a file for writing
// uint8_t *WFILE = (uint8_t *)SYS_WFILE_RAM_BASE; // Example of a file for writing in text mode
// uint32_t *RWNUM = (uint32_t *)SYS_RWNUM_RAM_BASE; // Example of a file for r/w

int Iflag = 1; // Interruption flag

int main()
{

    enableIRQ(); // Enable interruptions

    print_str("\n\n ===== SOFTWARE BEGIN ===== \n\n");

    /*** Place your code here: ***/
    // Example code:
    uint32_t i = 0;
    // add some delay before running real code
    for (i = 0; i < 100; i++)
    {
        uint32_t j = 0;
    }

    // Example code for reading and writing a file mapped into the memory map and directly:
    // This is a text file that contain numbers:
    // uint32_t aux;
    // for (i = 0; i < SYS_RWNUM_RAM_SIZE; i++)
    // {
    //     aux = RWNUM[i];
    //     aux *= 3;
    //     RWNUM[i] = aux;
    // }

    // Example code for reading a file mapped into the memory map and directly
    // send its contents to a input port of an IP connected to the AXI bus:
    SEND_IP_INPUT();

#if PRINT_DATA_DETAIL
    PRINT_INPUT();
#endif
    // Example code for printing the data read from file:
    // print_str("[Read] rfile.txt file:\n");
    // for (i = 0; i < 20/* RFILE_SIZE*4 too long */; i++)
    // {
    //     if( RFILE[i] == '\0' )
    //     {
    //         print_str("\nFound end of line at i = "); print_int(i); print_str("\n");
    //         break;
    //     }
    //     print_char((char)RFILE[i]);
    // }

    // Example code of writing in an IP register a starting run flag:
    SYS_MEM32((SYS_AXI_BASE)) = 0x80; // Example run IP flag
    print_str("\nSEND IP RUN!\n");

    while (Iflag)
        ; // Whait for an interruption

    print_str("\nRECEIVE IP IRQ!\n");

    //// Example code for printing the data returned by the IP:
    //print_str("Read from the IP:\n");
    //for(i = 0; i < 20/* WFILE_SIZE too long */; i++)
    //{
    //if( (char)SYS_MEM32((SYS_AXI_BASE + IPOUT_OFFSET + (4*i) )) == '\0' )
    //{
    //print_str("Found end of line at i = "); print_int(i); print_str("\n");
    //break;
    //}
    //print_char((char)SYS_MEM32((SYS_AXI_BASE + IPOUT_OFFSET + (4*i) )));
    //}

    // Example code for writing a file mapped into the memory map with data
    // directly read from an output port of an IP connected to the AXI bus:
    // for (i = 0; i < WFILE_SIZE; i++)
    // {
    //     WFILE[i] = SYS_MEM32((SYS_AXI_BASE + IP_OUT_OFFSET + (4*i) ));
    // }
    RECEIVE_IP_OUTPUT();
#if PRINT_DATA_DETAIL
    PRINT_OUTPUT();
#endif

    // Example code for printing the data returned by the IP:
    // print_str("Read from the IP:\n");
    // for (i = 0; i < 20/* WFILE_SIZE*4 too long */; i++)
    // {
    //     //if( (char)SYS_MEM32((SYS_AXI_BASE + IPOUT_OFFSET + (4*i) )) == '\0' )
    //     if ( WFILE[i] == '\0' )
    //     {
    //         print_str("\nFound end of line at i = "); print_int(i); print_str("\n");
    //         break;
    //     }
    //     print_char(WFILE[i]);
    //     //print_char((char)SYS_MEM32((SYS_AXI_BASE + IPOUT_OFFSET + (4*i) )));
    //     //print_int(SYS_MEM32((SYS_AXI_BASE + IPOUT_OFFSET + (4*i) ))); print_str(" ");
    // }

    print_str("\nIP I/O Done!\n");

    print_str("\n\n ===== SOFTWARE END ===== \n\n");

    halt();

    return (1);
}

// Example of interrupt handler function:

//void handle_interrupt(void) __attribute__ ((interrupt("IRQ"))) ;
void handle_interrupt(void)
{
    disableIRQ();
    SYS_MEM32((SYS_AXI_BASE) + 0) = 0x00; // stop IP
    //print_str("***********\nIRQ received\n***********\n "); // There should not be print calls on interrupt handles
    Iflag = 0;
}

void IP_RUN_ADD(void)
{
    print_str("\n************\nRUN IP INSTUCTION -> ADD\n");
    SYS_MEM32(SYS_AXI_BASE + IP_INS_OFFSET) = IP_INS_ADD;
    while (Iflag)
        ;
    print_str("Finished\n************\n");
}

void IP_RUN_MULT(void)
{
    print_str("\n************\nRUN IP INSTUCTION -> MULT\n");
    SYS_MEM32(SYS_AXI_BASE + IP_INS_OFFSET) = IP_INS_MULT;
    while (Iflag)
        ;
    print_str("Finished\n************\n");
}

void IP_RUN_MIRROR(void)
{
    print_str("\n************\nRUN IP INSTUCTION -> MIRROR\n");
    SYS_MEM32(SYS_AXI_BASE + IP_INS_OFFSET) = IP_INS_MIRROR;
    while (Iflag)
        ;
    print_str("Finished\n************\n");
}

void SEND_IP_INPUT(void)
{
    print_str("\nSEND IP INPUT:");
    print_hex_uint((SYS_AXI_BASE) + IP_IN_OFFSET);
    print_str(" -> ");
    print_hex_uint((SYS_AXI_BASE) + IP_IN_OFFSET + 4 * RFILE_SIZE);
    print_str("\n");

    uint32_t i = 0;
    for (i = 0; i < RFILE_SIZE; i++)
    {
        // print_uint(RFILE[i]);
        // print_str(" ");
        SYS_MEM32((SYS_AXI_BASE) + IP_IN_OFFSET + (4 * i)) = RFILE[i];
    }

    // print_str("      RFILE -> IP DONE\n************\n\n");
    // for (i = 0; i < RFILE_SIZE; i++) {
    //     print_uint(RFILE[i]); print_str(" ");
    // }
}

void RECEIVE_IP_OUTPUT(void)
{
    print_str("\nRECEIVE IP OUTPUT:\n");
    print_hex_uint((SYS_AXI_BASE) + IP_OUT_OFFSET);
    print_str(" -> ");
    print_hex_uint((SYS_AXI_BASE) + IP_OUT_OFFSET + 4 * WFILE_SIZE);
    print_str("\n");

    uint32_t i = 0;
    for (i = 0; i < WFILE_SIZE; i++)
    {
        WFILE[i] = SYS_MEM32((SYS_AXI_BASE) + IP_OUT_OFFSET + (4 * i));
    }

    // print_str("      IP -> WFILE DONE\n************\n\n");
    // for (i = 0; i < WFILE_SIZE; i++) {
    //     print_uint(WFILE[i]); print_str(" ");
    // }
}

void PRINT_INPUT(void)
{

    uint32_t i = 0;
    print_str("\nINPUT DATA (");
    print_uint(RFILE_SIZE);
    print_str("):\n");
    for (i = 0; i < RFILE_SIZE; i++)
    {
        if (RFILE[i] == '\0')
        {
            print_str("\nTOTAL PRINTED: ");
            print_uint(i);
            break;
        }
        print_uint(RFILE[i]);
        print_str(" ");
    }
}

void PRINT_OUTPUT(void)
{

    uint32_t i = 0;
    print_str("\nOUTPUT DATA (");
    print_uint(WFILE_SIZE);
    print_str("):\n");
    for (i = 0; i < WFILE_SIZE; i++)
    {
        if (WFILE[i] == '\0')
        {
            print_str("\nTOTAL PRINTED: ");
            print_uint(i);
            break;
        }
        print_uint(WFILE[i]);
        print_str(" ");
    }
}
