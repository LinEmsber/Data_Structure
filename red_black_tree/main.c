/* The simple implemenataion of red black tree.
 *
 * Reference:
 * https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
 */

#include <stdio.h>
#include <stdlib.h>

#include "rbt.h"


int main()
{
	rbt_init();

	rbt_insert(10);
	rbt_insert(80);
	rbt_insert(30);
	rbt_insert(20);
	rbt_insert(90);
	rbt_insert(50);
	rbt_insert(70);
	rbt_insert(40);

	rbt_display(root,0);
	rbt_free();


	return 0;
}
