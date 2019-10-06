#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <x86_64-linux-gnu/sys/stat.h>
#include <sys/io.h>
#include <string.h>
#include <time.h>

struct parameter{//definition of the stucture of parameters for syscall 0&1
	int nr;
	int fd;
	void *buf;
	size_t nbyte;
};

extern int errno;

void check(){// if error occurs, print the error code and set errno to 0 again
	printf("%d", errno);
	perror("error");
	errno = 0;
	

}


void paraGen(char* buf, int n){//generates parameter, n means how many times you want to test
	srand((unsigned)time(NULL));
	struct parameter para;
	for(int i=0; i<n;i++){
		para.nr = (rand() % 2); //0 or 1, read or write
		para.fd = (rand() % 3)+ 3; // from 3 to 5, read only, write only, not valid
		para.buf = buf; //initialize buf, makes the buffer valid, may set it to unvalid values if it is needed
		para.nbyte = 10;//(rand() % 3)+ strlen(buf)-1; //range [buffer_size-1, buffer_size+1], see what will happen with a valid size or a smaller/bigger size.
		
		size_t z = syscall(para.nr,para.fd,para.buf,para.nbyte);
		printf("system(%d, %d, \"%s\", %d):",para.nr, para.fd, para.buf, para.nbyte );
		if(para.nr==1){
			printf("you have written %zu words from the buffer\n",z);}
		else{
			printf("you have read %zu words to the buffer\n",z);}
		//check;// if we use the check function,check will not be called. Strange phenomenon
		printf("%d: %s\n", errno, strerror(errno));
		perror("error");
		errno = 0;	
	}

}
int main(){
	char* buf1 = malloc(10*sizeof(char));//assign space for buf1
	strcpy(buf1, "I am happy");//set value
	int handle=open("hello.txt", O_RDONLY );//open hello.txt to read
	int handle1 = open("TEXT.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);//printf("%d,%d\n", handle,handle1);//open text.txt to write
	paraGen(buf1, 10);//call paraGen function to test
}









int test()//diferent cases that may happen when parameters are set right or wrong
{       char* buf1 = malloc(10*sizeof(char));
	strcpy(buf1, "I am happy");
	
	int handle=open("hello.txt", O_RDONLY );	
	int handle1 = open("TEXT.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);printf("%d,%d\n", handle,handle1);
	char buf[10]={'I',' ','a','m',' ','h','a','p','p','y'};
	printf("buf(malloc):%s\n",buf1);
	printf("buf:%s\n",buf);
        struct parameter a;
	a.nr = 1;
	a.fd = handle1;
	a.buf = buf1;
	a.nbyte = 20;
        errno = 0;

        size_t x = write(handle1,"my name is jack\n",10);//check; check function is ignored, we have to copy it to below
        printf("you have writed %zu words to the buffer\n",x);	printf("%d", errno);
	perror("error");
	errno = 0;
////////////////////


	

        x = write(handle1,a.buf,30);
        printf("you have writed %zu words to the buffer\n",x);//printf("%s\n",a.buf);printf("%s\n",buf1);
	check();
////////////////////
        x = write(1,a.buf,30);
        printf("you have writed %zu words to the buffer\n",x);//printf("%s\n",a.buf);printf("%s\n",buf1);
	check();
  
//        exit(EXIT_FAILURE);

       // size_t y = syscall(1,1,"my name is Jack!\n",20);
        //printf("you have writed %d words to the buffer\n",y);
        size_t z = syscall(1,1,1,20);
        printf("you have writed %zu words to the buffer\n",z);

	check();
	z = syscall(0,handle,buf1,1000);
	printf("you have read %zu words to the buffer\n",z);
	printf("read from file:%s\n",buf1);
	check();
        exit(0);
}















/*void paraGen(char* buf){//generates parameter[10]
	srand((unsigned)time(NULL));
	struct parameter para[10];
	for(int i=0; i<5;i++){
		para[i].nr = (rand() % 2); //0 or 1, read or write
		para[i].fd = (rand() % 3)+ 3; // from 3 to 5, read only, write only, not valid
		para[i].buf = buf; //initialize buf, makes the buffer valid, may set it to unvalid values if it is needed
		para[i].nbyte = 10;//(rand() % 3)+ strlen(buf)-1; //range [buffer_size-1, buffer_size+1], see what will happen with a valid size or a smaller/bigger size.
		size_t z = syscall(para[i].nr,para[i].fd,para[i].buf,para[i].nbyte);
		if(para[i].nr==1){
			printf("you have written %zu words from the buffer\n",z);}
		else{
			printf("you have read %zu words to the buffer\n",z);}
			printf("%d", errno);
	perror("error");
	errno = 0;	
	}

}*/
