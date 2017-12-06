#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void usage(){
		printf("Usage: <Serial Port> on|off|bright|dim|blank|unblank|computer1|computer2|composite|svideo\n");
}

int main(int argc, char** argv){
        int rv=0;

	if(argc == 3){
		int fd;
		struct termios spconfig;
		const char* device = argv[1];
		const char mute[] = "MUTE ON";
		const char unmute[] = "MUTE OFF";
		const char on[] = "PWR ON";
		const char off[] = "PWR OFF";
		const char compu1[] = "SOURCE 11";
		const char compu2[] = "SOURCE 21";
		const char compos[] = "SOURCE 41";
		const char svid[] = "SOURCE 42";
		const char bright[] = "LUMINANCE 00";
		const char dim[] = "LUMINANCE 01";
		const char cr = 0X0d;
		fd = open(device, O_RDWR | O_NOCTTY | O_SYNC);
		if(fd == -1 || !isatty(fd) || tcgetattr(fd, &spconfig) < 0) {
			printf( "failed to open port %s \n",device);
			return 2;
		}
		cfmakeraw(&spconfig);
		cfsetispeed(&spconfig, B9600);
		cfsetospeed(&spconfig, B9600);
		tcsetattr(fd,TCSANOW,&spconfig);
		if(strcmp(argv[2],"off")==0){
			printf("Turning Projector Off\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,off,sizeof(off)-1);
			write(fd,&cr,1);
		} else if(strcmp(argv[2],"on")==0){
			printf("Turning Projector On\n");
			write(fd,&cr,1);
			usleep(100000);      
			write(fd,on,sizeof(on)-1);
			write(fd,&cr,1);
		} else if(strcmp(argv[2],"blank")==0){
			printf("Blanking A/V\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,mute,sizeof(mute)-1);
			write(fd,&cr,1);
		} else if(strcmp(argv[2],"unblank")==0){
			printf("Unblanking A/V\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,unmute,sizeof(unmute)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"computer1")==0){
			printf("Switching to computer 1\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,compu1,sizeof(compu1)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"computer2")==0){
			printf("Switching to computer 2\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,compu2,sizeof(compu2)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"composite")==0){
			printf("Switching to composite video\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,compos,sizeof(compos)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"svideo")==0){
			printf("Switching to s-video\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,svid,sizeof(svid)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"bright")==0){
			printf("Setting brightness to high\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,bright,sizeof(bright)-1);
			write(fd,&cr,1);
		}else if(strcmp(argv[2],"dim")==0){
			printf("Setting brightness to low\n");
			write(fd,&cr,1);
			usleep(100000);
			write(fd,dim,sizeof(dim)-1);
			write(fd,&cr,1);
		}else {
      rv=1;
		  usage();
    }
			tcdrain(fd);
			close(fd);
	}
	else{
    		rv=1;
    		usage();
	}
	return rv;
}
