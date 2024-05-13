/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\GlueCode\GlueCode.liquid */
extern "C" void cstmInitializeTCPWriteBuffer(const char*, int, int);
extern "C" void cstmInitializeTCPWriteThread();
	
extern "C" void cstmInitializeBufferInfo(int, int, int);
extern "C" void cstmInitializeProcessBucket();
extern "C" void cstmInitializeModuleBucket(const unsigned char* ptrModuleId);

extern "C" void cstm_Init_EBFD7A6C9EFF22E2273EAC48B4F14C94(void);

static unsigned char moduleId_0[] = {0x8A,0x2A,0xEC,0x78,0x8E,0xAE,0x82,0x01,0x6E,0x0E,0xBD,0xE1,0x09,0x39,0x8C,0x68};

extern "C" int cstm_Init_8A2AEC788EAE82016E0EBDE109398C68(){
	    cstmInitializeBufferInfo(1, 1, 10);
    cstmInitializeTCPWriteBuffer("127.0.0.1", 7000, 5000);
	
    cstmInitializeProcessBucket();
    cstmInitializeModuleBucket(moduleId_0);
    cstm_Init_EBFD7A6C9EFF22E2273EAC48B4F14C94();
    
    cstmInitializeTCPWriteThread();
	    
    return 0;
}

static int codescroll_init_dummy = cstm_Init_8A2AEC788EAE82016E0EBDE109398C68();


/* Empty CodeSnippet */

