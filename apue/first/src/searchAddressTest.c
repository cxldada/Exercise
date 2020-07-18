#include "../include/apue.h"
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc,char *argv[])
{
	int i;

#if 0
	puts("------- getprotoent begin: --------");
	struct protoent *pe;
	setprotoent(1);
	while((pe = getprotoent()) != NULL)
	{
		printf("getprotoent: p_name: %s, p_proto: %d, p_aliases: ",pe->p_name,pe->p_proto);
		for(i = 0; pe->p_aliases[i] != NULL; i++)
		{
			printf("%s",pe->p_aliases[i]);
		}
		puts("");
	}
	endprotoent();
	puts("------- getprotoent end: --------");

	puts("------- getservent begin: --------");
	struct servent *se;
	setservent(1);
	while((se = getservent()) != NULL)
	{
		printf("getservent: s_name: %s, s_sport: %d, s_proto: %s, s_aliases: ",se->s_name,se->s_port,se->s_proto);
		for(i = 0; se->s_aliases[i] != NULL; i++)
		{
			printf("%s",se->s_aliases[i]);
		}
		puts("");
	}
	endservent();
	puts("------- getservent end: --------");

	struct addrinfo ai;
	struct addrinfo *ais;
	ai.ai_flags = AI_CANONNAME;
	ai.ai_family = 0;
	ai.ai_socktype = 0;
	ai.ai_protocol = 0;
	ai.ai_addrlen = 0;
	ai.ai_canonname = NULL;
	ai.ai_addr = NULL;
	ai.ai_next = NULL;
	if((i = getaddrinfo(argv[1],argv[2],&ai,&ais)) != 0)
		printf("error: %s\n",gai_strerror(i));
#endif

	exit(0);
}
