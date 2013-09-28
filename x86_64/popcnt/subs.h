/* does CPUID say our CPU can handle POPCNT instruction? */
extern int canpopcnt(void);

/* call with 64-bit aligned address and n evenly divisible by 8 */
extern unsigned int countbits(uint16_t *a, unsigned long n);
