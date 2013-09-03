#include <stdio.h>

#define CPUID_SSE41_BIT (19)
#define CPUID_SSE42_BIT (20)
#define CPUID_POPCNT_BIT (23)

/* Figure 3.6 from Intel Instruction Set Reference */
char *features[] = {
	"SSE3",
	"PCLMULQDQ - Carryless Multiplication",
	"DTES64",
	"MONITOR/MWAIT",
	"DS-CPL - CPL Qualified Debug Store",
	"VMX - VM extensions",
	"SMX - Safer Mode Extensions",
	"EST - Enhanced Intel SpeedStep Technology",
	"TM2 - Thermal Monitor 2",
	"SSSE3 - SSSE3 Extensions",
	"CNXT-ID - L1 Context ID",
	"(skip)",
	"FMA - Fused Multiply Add",
	"CMPXCHG16B",
	"xPTR Update Control",
	"PDCM - Perf/Debug Capability MSR",
	"(skip)",
	"PCID - Process-context Identifiers",
	"DCA - Direct Cache Access",
	"SSE4_1",
	"SSE4_2",
	"x2APIC",
	"MOVBE",
	"POPCNT",
	"TSC-Deadline",
	"AES",
	"XSAVE",
	"OSXSAVE",
	"AVX",
	"F16C",
	"RDRAND",
};

extern unsigned int cpuidfn(unsigned int);

void prfeature(unsigned int cpuid, int i)
{
	char *yes = cpuid >> i & 1 ? "yes" : "no";

	printf("  %46s (bit %2d): %s\n", features[i], i, yes);
}

int main(void)
{
	int i;

	unsigned long n = (unsigned long) cpuidfn(1);
	printf("%016lx\n", n);
	printf("sse4.1: %s\n", (n >> CPUID_SSE41_BIT & 1) ? "yes" : "no");
	printf("sse4.2: %s\n", (n >> CPUID_SSE42_BIT & 1) ? "yes" : "no");
	printf("popcnt: %s\n", (n >> CPUID_POPCNT_BIT & 1) ? "yes" : "no");

	for (i = 0; i < sizeof features / sizeof features[0]; ++i)
		prfeature(n, i);

	return 0;
}
