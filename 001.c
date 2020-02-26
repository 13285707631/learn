#include	"unp.h"
#include<stdio.h>
#include<string.h>
struct serv_msg
{
	char length;
	char **s;
}msg1;
struct cli_msg
{
	char length;
	char s[MAXLINE];
}msg;

void
zyt_dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int                     n;
	socklen_t       len;
	char            mesg[MAXLINE];
	struct cli_msg cli_c;
	for (; ; ) {
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		memset(&cli_c,0,sizeof(cli_c));
		memcpy(&cli_c, mesg, sizeof(cli_c));
		//printf("%d\n", mesg[0]);
		//Fputs(mesg, stdout);
		//char m_zyt[MAXLINE - 1];
		//strncpy(m_zyt, mesg + 1, MAXLINE - 1);
		//printf("%s\n", m_zyt);
		printf("³¤¶È:%d\n", cli_c.length);
		printf("ÄÚÈÝ:%s\n", cli_c.s);
		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

	zyt_dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
