#include <stdio.h>
#include <string.h>
using namespace std;

#define G 34943

int main() {
	char str[2048];
	int crc;
	while (fgets(str, 2048, stdin) != NULL) {
		if (str[0] == '#')
			break;
		
		int now=0;
		/* 要抓 \n 和 \r 跳出迴圈，只用strlen(str)-2會RE */
		for (int i=0; i<strlen(str); i++){
			if (str[i] == '\n' || str[i] == '\r')
				break;
			now = ( ( (now<<8)%G ) + (int)(str[i]))%G;
		}
		now = ( ( (now<<8)%G ) << 8) %G;
		if (now != 0)
			now = G-now;
		printf ("%02X %02X\n", now>>8, now%256);
	}
	
	return 0;
}