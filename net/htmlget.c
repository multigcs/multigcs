
#include <all.h>

#ifndef WINDOWS

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>


// from http://coding.debuntu.org/c-linux-socket-programming-tcp-simple-http-client


#define USERAGENT "HTMLGET 1.0"

static int create_tcp_socket () {
	int sock;
	if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		SDL_Log("Can't create TCP socket");
		return -1;
	}
	return sock;
}

static char *get_ip (char *host) {
	struct hostent *hent;
	int iplen = 15; //XXX.XXX.XXX.XXX
	char *ip = (char *)malloc(iplen+1);
	memset(ip, 0, iplen+1);
	if ((hent = gethostbyname(host)) == NULL) {
		herror("Can't get IP\n");
		return NULL;
	}
	if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL) {
		SDL_Log("Can't resolve host: %s (%s)\n", host, ip);
		return NULL;
	}
	return ip;
}

char *build_get_query (char *host, char *page) {
	char *query;
	char *getpage = page;
	char *tpl = "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nConnection: close\r\n\r\n";
           
	if(getpage[0] == '/'){
		getpage = getpage + 1;
	}
	query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
	sprintf(query, tpl, getpage, host, USERAGENT);
	return query;
}

int htmlget (char *url, char *file) {
	struct sockaddr_in *remote;
	int sock;
	int tmpres;
	char *ip;
	char *get;
	char buf[BUFSIZ+1];
	char host[1024];
	char page[1024];
	char page2[1024];

	sscanf(url, "http://%[a-zA-Z0-9-_.]/%s", host, page2);
	sprintf(page, "/%s", page2);

	sock = create_tcp_socket();
	if (sock < 0) {
		return -1;
	}
	ip = get_ip(host);
	if (ip == NULL) {
		close(sock);
		return -1;
	}
	remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
	remote->sin_family = AF_INET;
	tmpres = inet_pton(AF_INET, ip, (void *)(&(remote->sin_addr.s_addr)));

	if( tmpres < 0)  {
		SDL_Log("Can't set remote->sin_addr.s_addr");
		close(sock);
		return -1;
	} else if (tmpres == 0) {
		SDL_Log("%s is not a valid IP address\n", ip);
		close(sock);
		return -1;
	}
	remote->sin_port = htons(80);

	if (connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0){
		SDL_Log("Could not connect");
		close(sock);
		return -1;
	}
	get = build_get_query(host, page);

	int sent = 0;
	while(sent < strlen(get)) {
		tmpres = send(sock, get+sent, strlen(get)-sent, 0);
		if(tmpres == -1) {
			SDL_Log("Can't send query");
			close(sock);
			return -1;
		}
		sent += tmpres;
	}

        FILE *fd = NULL;
        fd = fopen(file, "wb");
	if (fd == NULL) {
		SDL_Log("Error open file to write: %s\n", file);
	}

	memset(buf, 0, sizeof(buf));
	char last1 = 0;
	char last2 = 0;
	char last3 = 0;
	while((tmpres = recv(sock, buf, 1, 0)) > 0){
		if (last1 == '\r' && last2 == '\n' && last3 == '\r') {
			while((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0){
				fwrite(buf, 1, tmpres, fd);
			}
			break;
		}
		last3 = last2;
		last2 = last1;
		last1 = buf[0];
	}
	fclose(fd);

	free(get);
	free(remote);
	free(ip);
	close(sock);
	return 0;
}

#else
int htmlget (char *url, char *file) {
}
#endif
