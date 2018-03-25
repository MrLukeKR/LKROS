#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKCYAN 3
#define DARKRED 4
#define DARKMAGENTA 5
#define DARKORANGE 6
#define GREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define CYAN 11
#define LIGHTRED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15
#define VIDEOBUFFER 0xb8000

int currX, currY = 0;

void print();
void scrollUp();
void printLn();
void main();
void incX();
void incY();

void entry(){
	main();
}


void writeChar(unsigned char c, unsigned int forecolour, unsigned int backcolour, int x, int y){
	char *videoBuffer = (char*)(VIDEOBUFFER + (2* (y * 80 + x))); //Multiply by two as each character has a byte for colour and a byte for ASCII value
	int colour = 0;
	*videoBuffer++ = c;
	
	if ((forecolour >=0 && forecolour <= 15) && (backcolour>=0 && backcolour<=15))
		colour = forecolour + (16 * backcolour);

	*videoBuffer= colour;
}

void scrollUp(){
	char *videoBuffer = (char*)VIDEOBUFFER;
	for (int i=0;i<(80*24)*2;i++){
		*videoBuffer=*(videoBuffer+(80*2));
		videoBuffer+=1;
	}
	for (int j=0;j<(80)*2;j++){
		*videoBuffer=0;
		videoBuffer+=1;
		*videoBuffer=WHITE;
		videoBuffer+=1;
	} // WASTES 1 LINE - need to fix this
}

void incX(){
	if (currX==80){
		incY();
		currX=0;
	}else
		currX+=1;
}

void incY(){
	if (currY==24){
		scrollUp();
	}else
		currY+=1;
}

void carriageReturn(){
	currX=0;
	incY();
}

void clearScreen(){
	char *videoBuffer = (char*)VIDEOBUFFER;
	unsigned int i=0;
	for (int i=1;i<=80*25*2;i++){
		*videoBuffer=0;
		videoBuffer+=1;
	}
}

int count_memory(void)
{
   register unsigned long *mem;
   unsigned long bse_end;
   unsigned long   mem_count;
   unsigned long   a;
   unsigned short   memkb;
   unsigned long   mem_end;

   mem_count=0;
   memkb=0;

   do
   {
      memkb++;
      mem_count+=1024*1024;
      mem=(unsigned long*)mem_count;

      a=*mem;

      *mem=0x55AA55AA;

      // the empty asm calls tell gcc not to rely on whats in its registers
      // as saved variables (this gets us around GCC optimisations)
      asm("":::"memory");
      if(*mem!=0x55AA55AA)
         mem_count=0;
      else
      {
         *mem=0xAA55AA55;
         asm("":::"memory");
         if(*mem!=0xAA55AA55)
            mem_count=0;
      }
      asm("":::"memory");
      *mem=a;
   }while(memkb<4096 && mem_count!=0);
   mem_end=memkb<<20;
   mem=(unsigned long*)0x413;
   bse_end=((*mem)&0xFFFF)<<6;
   return   memkb;
}

void printInt(int forecolour, int backcolour, int number){
			if (number ==0)
				print(forecolour, backcolour, "0");
			if (number ==1)
				print(forecolour, backcolour, "1");
			if (number ==2)
				print(forecolour, backcolour, "2");
			if (number ==3)
				print(forecolour, backcolour, "3");
			if (number ==4)
				print(forecolour, backcolour, "4");
			if (number ==5)
				print(forecolour, backcolour, "5");
			if (number ==6)
				print(forecolour, backcolour, "6");
			if (number ==7)
				print(forecolour, backcolour, "7");
			if (number ==8)
				print(forecolour, backcolour, "8");
			if (number ==9)
				print(forecolour, backcolour, "9");
}

void printMem(){
	char asc;
	int reverse = 0;
	int n;
	n=count_memory();

	while (n != 0)
	   {
	      reverse = reverse * 10;
	      reverse = reverse + n%10;
	      n       /= 10;
	   }	

	if (reverse ==0)
		print(WHITE, DARKRED, "NO MEMORY DETECTED");
	while(reverse>0){
			asc = reverse%10;
			reverse/=10;
			printInt(DARKGREEN,BLACK,asc);
	}
	printLn(DARKGREEN,BLACK,"MB");
}


void memDetect(){
	print(GREY,BLACK,"Detecting Random Access Memory... ");
	printMem();
	//NEED TO IMPLEMENT MEMORY DETECTION - DEVICE DRIVERS!!
//	printLn(DARKGREEN,BLACK, count);
	
}

void hrSetup(){
	print(GREY,BLACK,"    Initialising Heart Rate Monitor... ");
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
	
	//NEED TO IMPLEMENT IO DETECTION - DEVICE DRIVERS!!
}
void tempSetup(){
	print(GREY,BLACK,"    Initialising Temperature Monitor... ");
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
	
	//NEED TO IMPLEMENT IO DETECTION - DEVICE DRIVERS!!
}

void bciSetup(){
	print(GREY,BLACK,"    Initialising Brain-Computer Interface... ");
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
	
	//NEED TO IMPLEMENT IO DETECTION - DEVICE DRIVERS!!
}


void ioDetect(){
	print(GREY,BLACK,"Detecting I/O Devices... ");
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
	hrSetup();
	tempSetup();
	bciSetup();
	//NEED TO IMPLEMENT IO DETECTION - DEVICE DRIVERS!!
}

void storageDetect(){
	print(GREY,BLACK,"Detecting Storage Devices... ");
	//NEED TO IMPLEMENT STORAGE DETECTION - DEVICE DRIVERS!!
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
}

void networkDetect(){
	print(GREY,BLACK,"Detecting Networking Devices... ");
	//NEED TO IMPLEMENT NETWORK DETECTION - DEVICE DRIVERS!!
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
}

void graphicsDetect(){
	print(GREY,BLACK,"Detecting GPU Devices... ");
	//NEED TO IMPLEMENT GPU DETECTION - DEVICE DRIVERS!!
	printLn(DARKRED,BLACK,"NOT IMPLEMENTED");
}

void printLn(int forecolour, int backcolour, char* message){
	print(forecolour, backcolour, message);
	carriageReturn();
}	

void print(int forecolour, int backcolour, char* message){
	while (*message!=0){
		writeChar(*message,forecolour,backcolour,currX,currY);
		message++;
		incX();
	}
}

void wait(){
	for (int i =0; i<99999; i++){
		for (int j =0; j<200; j++){
		
		}
	}
}

void startup(){
	memDetect();
	storageDetect();
	networkDetect();
	graphicsDetect();
	ioDetect();
}

void printSystemInfo(){
	printLn(WHITE,BLACK, "                       *********************************");
	printLn(WHITE,BLACK, "                       * UNNAMED OPERATING SYSTEM v0.1 *");
	printLn(WHITE,BLACK, "                       *       Copyright LKR 2016      *");
	printLn(WHITE,BLACK, "                       *  Latest : 05/05/2016 03:06AM  *");
	printLn(WHITE,BLACK, "                       *********************************");

	carriageReturn();
	printLn(DARKRED,BLACK,"                                    WARNING");
	printLn(GREY,BLACK,"               Extremely limited functionality - may be unstable!");
	carriageReturn();
}

void main(){
	clearScreen();
	printSystemInfo();
	startup();

	while(1){
	}
}
