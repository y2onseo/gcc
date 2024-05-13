/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\GlueCode\GlueCode.liquid */
extern "C" void cstmInitializeTCPWriteBuffer(const char*, int, int);
extern "C" void cstmInitializeTCPWriteThread();
	
extern "C" void cstmInitializeBufferInfo(int, int, int);
extern "C" void cstmInitializeProcessBucket();
extern "C" void cstmInitializeModuleBucket(const unsigned char* ptrModuleId);

extern "C" void cstm_Init_07543B1572FFDDAD0EEE1A0780731B85(void);

static unsigned char moduleId_0[] = {0xD5,0x77,0x90,0xA1,0x71,0x97,0x6D,0xCC,0xCC,0x19,0xCB,0x88,0xD8,0xB0,0x57,0x14};

extern "C" int cstm_Init_D57790A171976DCCCC19CB88D8B05714(){
	    cstmInitializeBufferInfo(1, 1, 1);
    cstmInitializeTCPWriteBuffer("127.0.0.1", 7000, 5000);
	
    cstmInitializeProcessBucket();
    cstmInitializeModuleBucket(moduleId_0);
    cstm_Init_07543B1572FFDDAD0EEE1A0780731B85();
    
    cstmInitializeTCPWriteThread();
	    
    return 0;
}

static int codescroll_init_dummy = cstm_Init_D57790A171976DCCCC19CB88D8B05714();


/* Empty CodeSnippet */

