#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../address_map_arm.h"

/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void * map_physical (int, unsigned int, unsigned int);
void close_physical (int);
int unmap_physical (void *, unsigned int);

/* This program increments the contents of the red LED parallel port */
int main(void)
{
   volatile int * KEYCODE_ptr;
   volatile int * KEYCODE_RST_ptr;
   volatile int * INITIAL_SCREEN_ptr;
   volatile int * CARD_SELECT_ptr;
   volatile int * MY_CARD_1_ptr;
   volatile int * MY_CARD_2_ptr;
   volatile int * MY_CARD_3_ptr;
   volatile int * MY_CARD_USED_ptr;
   volatile int * ENEMY_CARD_USED_ptr;
   volatile int * ENEMY_CARD_VISIBLE_ptr;
   volatile int * MY_HP_ptr;
   volatile int * MY_SHIELD_ptr;
   volatile int * TIME_ptr;
   volatile int * ROUND_ptr;
   volatile int * ENEMY_HP_ptr;
   volatile int * ENEMY_SHIELD_ptr;
   volatile int * BUFF_ptr;
   volatile int * ULT_INFO_ptr;

   int fd = -1;               // used to open /dev/mem for access to physical addresses
   void *LW_virtual;          // used to map physical addresses for the light-weight bridge

   // Create virtual memory access to the FPGA light-weight bridge
   if ((fd = open_physical (fd)) == -1)
      return (-1);
   if ((LW_virtual = map_physical (fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)) == NULL)
      return (-1);

   // Set virtual address pointer to I/O port
   KEYCODE_ptr = (unsigned int *) (LW_virtual + 0x00000010);
   KEYCODE_RST_ptr = (unsigned int *) (LW_virtual + 0x00000000);
   INITIAL_SCREEN_ptr = (unsigned int *) (LW_virtual + 0x00000020);
   CARD_SELECT_ptr = (unsigned int *) (LW_virtual + 0x00000030);
   MY_CARD_1_ptr = (unsigned int *) (LW_virtual + 0x00000040);
   MY_CARD_2_ptr = (unsigned int *) (LW_virtual + 0x00000050);
   MY_CARD_3_ptr = (unsigned int *) (LW_virtual + 0x00000060);
   MY_CARD_USED_ptr = (unsigned int *) (LW_virtual + 0x00000070);
   ENEMY_CARD_USED_ptr = (unsigned int *) (LW_virtual + 0x00000080);
   ENEMY_CARD_VISIBLE_ptr = (unsigned int *) (LW_virtual + 0x00000090);
   MY_HP_ptr = (unsigned int *) (LW_virtual + 0x000000a0);
   MY_SHIELD_ptr = (unsigned int *) (LW_virtual + 0x000000b0);
   TIME_ptr = (unsigned int *) (LW_virtual + 0x000000c0);
   ROUND_ptr = (unsigned int *) (LW_virtual + 0x000000d0);
   ENEMY_HP_ptr = (unsigned int *) (LW_virtual + 0x000000e0);
   ENEMY_SHIELD_ptr = (unsigned int *) (LW_virtual + 0x000000f0);
   BUFF_ptr = (unsigned int *) (LW_virtual + 0x00000100);
   ULT_INFO_ptr = (unsigned int *) (LW_virtual + 0x00000110);

   *INITIAL_SCREEN_ptr = 0x01;
   *CARD_SELECT_ptr = 0x01;
   *MY_CARD_1_ptr = 0x82;
   *MY_CARD_2_ptr = 0x00;
   *MY_CARD_3_ptr = 0x85;
   *MY_CARD_USED_ptr = 0x86;
   *ENEMY_CARD_USED_ptr = 0x01;
   *ENEMY_CARD_VISIBLE_ptr = 0x07;
   *MY_HP_ptr = 12;
   *MY_SHIELD_ptr = 7;
   *TIME_ptr = 20;
   *ROUND_ptr = 5;
   *ENEMY_HP_ptr = 18;
   *ENEMY_SHIELD_ptr = 0;
   *BUFF_ptr = 1;
   *ULT_INFO_ptr = 0;

   while (1) {
      unsigned int keycode = *KEYCODE_ptr;
      if (keycode & 0x01000000) {
         printf("keycode:%x \n", keycode - 0x01000000);
         *KEYCODE_RST_ptr = 0x00000001;
         usleep(1000);
         *KEYCODE_RST_ptr = 0x00000000;
      }
      usleep(1000);
   }

   unmap_physical (LW_virtual, LW_BRIDGE_SPAN);   // release the physical-memory mapping
   close_physical (fd);   // close /dev/mem
   return 0;
}

// Open /dev/mem, if not already done, to give access to physical addresses
int open_physical (int fd)
{
   if (fd == -1)
      if ((fd = open( "/dev/mem", (O_RDWR | O_SYNC))) == -1)
      {
         printf ("ERROR: could not open \"/dev/mem\"...\n");
         return (-1);
      }
   return fd;
}

// Close /dev/mem to give access to physical addresses
void close_physical (int fd)
{
   close (fd);
}

/*
 * Establish a virtual address mapping for the physical addresses starting at base, and
 * extending by span bytes.
 */
void* map_physical(int fd, unsigned int base, unsigned int span)
{
   void *virtual_base;

   // Get a mapping from physical addresses to virtual addresses
   virtual_base = mmap (NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
   if (virtual_base == MAP_FAILED)
   {
      printf ("ERROR: mmap() failed...\n");
      close (fd);
      return (NULL);
   }
   return virtual_base;
}

/*
 * Close the previously-opened virtual address mapping
 */
int unmap_physical(void * virtual_base, unsigned int span)
{
   if (munmap (virtual_base, span) != 0)
   {
      printf ("ERROR: munmap() failed...\n");
      return (-1);
   }
   return 0;
}
