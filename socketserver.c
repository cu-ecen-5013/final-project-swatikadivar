#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<linux/fs.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<libgen.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<syslog.h>
#include<pthread.h>
#include<sys/queue.h>
#include<sys/time.h>
#include<time.h>
#include<stdbool.h>

#define MAXRECVSTRING 30
#define PORTNO 9000
#define PORT "9000"

#define BACKLOG 10
int sockfd, newfd;
char s[INET6_ADDRSTRLEN];
int operation_switch =1;
pthread_mutex_t *socklock;

//Signal HAndler function
void handle_sig(int sig)
{
  operation_switch=0;
  if(sig == SIGINT)
    syslog(LOG_DEBUG,"Caught SIGINT Signal exiting\n");
  if(sig == SIGTERM)
    syslog(LOG_DEBUG,"Caught SIGTERM Signal exiting\n");  
  shutdown(newfd,SHUT_RDWR);
  _exit(0);
}





void* threadhandler1(void* thread_param)
{
	while(operation_switch)
	{
		/// LOG MSG TO SYSLOG: "Accepted connection from XXX"
		syslog(LOG_INFO, "Accepted connection from %s\n", s);
		
		int k=0, rc=0;
		char rdBuff[80] = {'\0'};

		time_t r_time;
		struct tm *timeinfo;
		char buf[30];
		time(&r_time);

		k = rand()%70;
		
		timeinfo = localtime(&r_time);
		strftime(buf, 80,"%x-%H:%M %p ", timeinfo);
		
		sprintf(rdBuff, "%s sensor 1: %d\n",buf, k);
		printf("%d %s\n",k,rdBuff);
		rc = send(newfd, rdBuff, strlen(rdBuff), MSG_DONTWAIT);
		if( rc < 0){
		  perror("Couldnt send sensor results to file\n");
		}
	
		usleep(5000);
	}
	return NULL;
}

void* threadhandler2(void* thread_param)
{
	while(operation_switch){
			/// LOG MSG TO SYSLOG: "Accepted connection from XXX"
		syslog(LOG_INFO, "Accepted connection from %s\n", s);
		
		int k=0,rc=0;
		char rdBuff[80] = {'\0'};

		time_t r_time;
		struct tm *timeinfo;
		char buf[30];
		time(&r_time);

		k = rand()%70;
		
		timeinfo = localtime(&r_time);
		strftime(buf, 80,"%x-%H:%M %p ", timeinfo);
		
		sprintf(rdBuff, "%s sensor 1: %d\n",buf, k);
		printf("%d %s\n",k,rdBuff);
		rc = send(newfd, rdBuff, strlen(rdBuff), MSG_DONTWAIT);
		if( rc < 0){
		  perror("Couldnt send sensor results to file\n");
		}
	
		usleep(5000);
	}
	return NULL;
}

// This routine returns client socket address
//ref:https://beej.us/guide/bgnet/html/#cb20-1
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {                   
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);   // for IPv6
}
  
int main(int argc, char *argv[])
{
  signal(SIGTERM,handle_sig);
  signal(SIGINT,handle_sig);

  if(pthread_mutex_init(socklock, NULL) != 0)
  {
	  syslog(LOG_ERR, "mutex init failed.");
	  return -1; 
  }
	  
  struct sockaddr_storage opp_addr;
  struct addrinfo ref, *res, *p;
  memset(&ref, 0, sizeof(ref));
  ref.ai_family = AF_UNSPEC;
  ref.ai_socktype = SOCK_STREAM;
  ref.ai_flags = AI_PASSIVE;

  if(getaddrinfo(NULL, PORT, &ref, &res) != 0)
  {
    syslog(LOG_ERR, "getaddrinfo failed.");
    return -1;
  }

	  /// socket and bind
	for(p = res; p != NULL; p = p->ai_next)
	{
	
	  if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
	  {
			perror("Socket failed");
	  }
	
	  if(bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)
	  {
			perror("bind failed");
	  }
	
	  break;
	}
	
	if(p == NULL)
	{
	  syslog(LOG_ERR, "Socket bind failed.");
		return -1;
	}
	
	freeaddrinfo(res);

//int opt;
//
///// start daemon if -d given in argument
//if((opt = getopt(argc, argv, "d")) == 'd')
//{
//	daemon(0, sockfd);
//}


	/// socket listen
	if(listen(sockfd, BACKLOG) < 0)
	{
	  syslog(LOG_ERR, "Socket listen failed.");
	  return -1;
	}
  
//int i = 0;
	pthread_t thread1, thread2; 

  while(operation_switch)
  {

		socklen_t addr_size = sizeof(opp_addr);
		
		/// accept socket connection
	newfd = accept(sockfd, (struct sockaddr *)&opp_addr, &addr_size);
	if(newfd < 0)
	{
			syslog(LOG_ERR, "Socket accept failed.");
		if(!operation_switch) 
		{
			break;
		}
         exit (EXIT_FAILURE);
	}
		
	inet_ntop(opp_addr.ss_family, get_in_addr((struct sockaddr *)&opp_addr),
                  s, sizeof s);
	
  
	
	/// create pthread and pass socket id, and global mutex in thread arguments
	if((pthread_create(&thread1, NULL, &threadhandler1, NULL)) != 0)
	{
	  syslog(LOG_ERR, "pthread create failed.");
	  return -1;
	}
	
	/// create pthread and pass socket id, and global mutex in thread arguments
	if((pthread_create(&thread2, NULL, &threadhandler2, NULL)) != 0)
	{
	  syslog(LOG_ERR, "pthread create failed.");
	  return -1;
	}	
	
 }
 
 pthread_join(thread1, NULL);
 pthread_join(thread2, NULL);
}
  //shutdown(socket_client,SHUT_RDWR);
  
