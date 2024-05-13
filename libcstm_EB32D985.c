/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\Library\BufferStructDefine.liquid */
#include <stdlib.h>

typedef struct cvBufferInfo{
	int bucketCount;
	int size;
	unsigned char* buffer;
	char* fileOutput;
	int index;
	struct cvBufferInfo* next;
} CvBufferInfo;

CvBufferInfo* head = 0;
CvBufferInfo* tail = 0;

static void CreateBufferInfo(int size, int bucketCount){
    CvBufferInfo* last = head;
	CvBufferInfo* newBufferInfo = (CvBufferInfo*) calloc( 1, sizeof(CvBufferInfo));

	newBufferInfo->size = size;
	newBufferInfo->bucketCount = bucketCount;

	if(head == 0){
		head = newBufferInfo;
		tail = head;
		return;
	}

	while(last->next != 0){
		last = last->next;
	}
	last->next = newBufferInfo;
	tail = newBufferInfo;
}

/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\Library\MinGW\TcpTransportFunctions_MinGW.liquid */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <winsock2.h>
#include <string.h>
#include <windows.h>

static const char* cv_ip;
static int cv_port;
static int cv_interval;

#ifdef __cplusplus
extern "C"
#endif
void cstmInitializeTCPWriteBuffer(const char* ip, int port, int interval) {
	cv_ip = ip;
	cv_port = port;
	cv_interval = interval;
	tail->buffer = (unsigned char*)calloc(tail->size, sizeof(char));
}

static SOCKET sockfd = 0;
static int lastConnection = 0;

static int initWinsock() {
	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
		return -1;
	}
}

static int createSocket() {
	if(sockfd > 0){
		return sockfd;
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET) {
		return 0;
	}
	
	return sockfd;
}

static int connectTCP() {
	if (lastConnection > 0) {
		return lastConnection;
	}
	
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(cv_port);
	addr.sin_addr.s_addr = inet_addr(cv_ip);

	if (connect(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("[fail to connect]");
		return -1;
	}
	else {
		printf("success to connect\n");
		return 1;
	}
}

static void updateConnectionState(int send1, int send2) {
	if (send1 < 0 || send2 < 0) {
		close(sockfd);
		sockfd = 0;
		lastConnection = 0;
	}
	else {
		lastConnection = 1;
	}
}

pthread_mutex_t cv_mutex = PTHREAD_MUTEX_INITIALIZER;

static void dumpBufferToTCP() {
	pthread_mutex_lock(&cv_mutex);

	if (createSocket() < 0) {
		pthread_mutex_unlock(&cv_mutex);
		return;
	}

	if (connectTCP() < 0) {
		pthread_mutex_unlock(&cv_mutex);
		return;
	}

	CvBufferInfo *current = head;
	while (current != 0) {
		int sendLen = htonl(current->size);

		int send1 = send(sockfd, (const char*)&sendLen, sizeof(int), 0);
		int send2 = send(sockfd, (const char*)current->buffer, current->size, 0);

		updateConnectionState(send1, send2);

		current = current->next;
	}

	pthread_mutex_unlock(&cv_mutex);
}

static void cleanUp() {
	dumpBufferToTCP();
	WSACleanup();
}

static void* runDumpThread(void *arg) {
	while (1) {
		dumpBufferToTCP();
		Sleep(cv_interval);
	}
	return 0;
}

#ifdef __cplusplus
extern "C"
#endif
void cstmInitializeTCPWriteThread() {
	static void (*cvExitFunc)() = 0;
	if (cvExitFunc == NULL) {
		initWinsock();
		if (atexit(cleanUp) == 0) {
			cvExitFunc = cleanUp;
		}
	}

	static pthread_t cv_threadId;
	int tid = pthread_create(&cv_threadId, NULL, &runDumpThread, NULL);
	if (tid != 0) {
		perror("fail to create dump thread");
		exit(0);
	}
}


/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\Library\MinGW\Memcpy_MinGW.liquid */
#include <string.h>
static void cv_memcpy(void* dst, const void* source, size_t size){
	memcpy(dst, source, size);
}

/* C:\QualityScroll-Cover-SE\conf\Template\Base\ByteOrderConverion_ManuallySwap.liquid */
#define cv_htonl(A) ((((A) & 0xff000000) >> 24) | (((A) & 0x00ff0000) >> 8) | (((A) & 0x0000ff00) << 8) | (((A) & 0x000000ff) << 24))

/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\Library\WriteInt_32Bit.liquid */
static void cv_writeInt(int value){
	cv_memcpy(tail->buffer + tail->index, &value, 4);
	tail->index += 4;
}

/* C:\QualityScroll-Cover-SE\conf\Template\DynamicMemory\Library\InitializeFunctions.liquid */
static void cv_writeBuffer(const void* value, unsigned int length){
	cv_memcpy(tail->buffer + tail->index, value, length);
	tail->index += length;
}

#ifdef __cplusplus
extern "C" 
#endif
void cstmInitializeBufferInfo(int moduleCount, int tuCount, int probeCount){
	int ps_bucket_size = 33;
	int md_bucket_size = 21 * moduleCount;
	int tu_bucekt_size = 25 * tuCount + probeCount;

	int bufferSize = ps_bucket_size + md_bucket_size + tu_bucekt_size;
	int bucketCount = 1 + moduleCount + tuCount;
	CreateBufferInfo(bufferSize, bucketCount);
}

#ifdef __cplusplus
extern "C" 
#endif
void cstmInitializeProcessBucket(){
	// header
	tail->buffer[tail->index++] = 0x54;
	tail->buffer[tail->index++] = 0x4d;
	tail->buffer[tail->index++] = 0x43;
	tail->buffer[tail->index++] = 0x01;

	// PID
	cv_writeInt(cv_htonl(-2));

	// start time + end time
	tail->index += 8;

	// total bucket count
	cv_writeInt(cv_htonl(tail->bucketCount));

	// process bucket
	cv_writeInt(cv_htonl(1 + 4 + 4));
	tail->buffer[tail->index++] = 0x70;
	cv_writeInt(cv_htonl(4));
	cv_writeBuffer("cvse", 4);
}

#ifdef __cplusplus
extern "C" 
#endif
void cstmInitializeModuleBucket(const unsigned char* ptrModuleId)
{
	// module bucket
	cv_writeInt(cv_htonl(17));
	tail->buffer[tail->index++] = 0x6D;
	cv_writeBuffer(ptrModuleId, 16);
}

static void mergeBit(unsigned char *src, unsigned int size)
{
	unsigned int i = 0;
	for( i = 0; i < size; i++ ) {
		tail->buffer[tail->index++] |= src[i];
	}
}

#ifdef __cplusplus
extern "C" 
#endif
void cstmInitializeTu(const char* tuId, unsigned char* localStaticBuffer, long bufferSize, unsigned char** bufferPtr)
{
	// write tu bucket
	int bucket_length = 1 + 16 + 4 + bufferSize;
	cv_writeInt(cv_htonl(bucket_length));
	tail->buffer[tail->index++] = 0x74;
	cv_writeBuffer(tuId, 16);
	cv_writeInt(cv_htonl((int) bufferSize));

	// swap local static buffer
	*bufferPtr = tail->buffer + tail->index;
	mergeBit(localStaticBuffer, bufferSize);

	// when skip to merge bit
	// tail->index += bufferSize;
}

/* Empty CodeSnippet */

