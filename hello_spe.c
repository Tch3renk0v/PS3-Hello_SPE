#include <stdio.h>

int main(unsigned long long id)
{

	/* The first parameter of an spu program will always be the spe_id of the spe
	 * thread that issued it.
	 */
	printf("Hello from spe : (0x%llx)\n", id);

	return 0;
}
