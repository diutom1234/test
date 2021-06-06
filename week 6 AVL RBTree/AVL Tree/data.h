typedef union {
    int i;
    long l;
    float f;
    double d;
    void *v;
    char *s;
    char c;
    unsigned char uc;
    short sh;
    unsigned short ush;
    unsigned int ui;
    int iarray[2];
    float farray[2];
    char carray[8];
    unsigned char ucarray[8];
  } Jval; 
  
extern int compare_s(Jval j1, Jval j2); 
extern void copy_s(Jval* jtarget, const Jval* jsource); 
