#include <iostream>
#include <stdio.h>
#include <vector>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>

#include <cstring>
using namespace std;


int myexec(const char *cmd, std::vector<std::string> &resvec) {
    resvec.clear();
    FILE *pp = popen(cmd, "r");
    if (!pp) {
        return -1;
    }
    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0';
        }
        resvec.push_back(tmp);
    }
    pclose(pp);
    return resvec.size();
}

int main(int argc, const char * argv[]) {
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t clientAddrLen;
    int nFd=0,linkFd=0;
    int nRet=0;
    int nReadLen=0;
    char szBuff[BUFSIZ]= {0};

    nFd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==nFd) {
        perror("socket:");
        return -1;
    }

    memset(&serverAddr,0,sizeof(struct sockaddr_in));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddr.sin_port=htons(8888);

    int isReuse=1;
    setsockopt(nFd,SOL_SOCKET,SO_REUSEADDR,(const char*)&isReuse,sizeof(isReuse));

    nRet=bind(nFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(-1==nRet) {
        perror("bind:");
        return -1;
    }

    listen(nFd,1);

    clientAddrLen=sizeof(struct sockaddr_in);
    linkFd=accept(nFd,(struct sockaddr*)&clientAddr,&clientAddrLen);
    if(-1==linkFd) {
        perror("accept:");
        return -1;
    }

    printf("connect %s %d successful\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));

    while(1) {
        memset(szBuff,0,BUFSIZ);
        nReadLen=read(linkFd,szBuff,BUFSIZ);
        if(nReadLen>0) {
            printf("read date: %s\n",szBuff);

//*************************************
            string tmppp=szBuff;
            cout<<tmppp<<endl;
            std::vector<std::string> *vect = new std::vector<std::string>();
            pid_t pid = getpid();
            char *cmd = new char[1024];
            string aaa="mosquitto_pub -t mqtt -m \"";
            string bbb=tmppp+"\"";
            string tmpp=aaa+bbb;
            cout<<"the cmd is "<<tmpp<<endl;
            sprintf(cmd, tmpp.c_str(),pid);
            std::cout<< cmd << std::endl;
            int a = myexec(cmd, *vect);

            std::cout<< a << std::endl;

            int i = 0;
            int count = vect->size();
            for (; i < count; i++) {
                std::cout<< (*vect)[i] <<std::endl;
            }
//*************************************

        }
    }

    return 0;
}
