#include <pcap/pcap.h>
//#include <stdio.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

EMSCRIPTEN_KEEPALIVE int testFilter( const char *bpfFilterExpr, /*out*/ char *outMsgBuf, int outMsgLen ) {
	struct bpf_program bpfProgram;

	pcap_t *p = pcap_open_dead( /*LINKTYPE_ETHERNET*/ DLT_EN10MB, 65536 );
	int compilationStatus = pcap_compile( p, &bpfProgram, bpfFilterExpr, 1, /*PCAP_NETMASK_UNKNOWN*/ 0xffffffff );
	if (compilationStatus == -1) {
		//printf( "Error compiling filter: %s\n", pcap_geterr(p) );
		outMsgBuf && strncpy( outMsgBuf, pcap_geterr(p), outMsgLen );
	}
	pcap_close( p );

	//printf("Filter \"%s\" compilation status is: %d\n", bpfFilterExpr, compilationStatus);
	return compilationStatus;
}

// testFilter( "icmp and not icmp", NULL, 0 );
// testFilter( "icmp or tcp", NULL, 0 );

// Note: if using main, be sure to add -s NO_EXIT_RUNTIME=1 
// in order for emcc to be able to run the other functions after it exits
//EMSCRIPTEN_KEEPALIVE int main() {
//	return testFilterGood();
//}
