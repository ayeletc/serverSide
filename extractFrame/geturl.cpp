
#include "geturl.h"

using namespace std;

/**int getVideoAddress(std::string *videoAddress);

int main (int argc, const char * argv[]) {

	std::string videoAddress;
	getVide/Users/ayelet/repo/serverSide/main.cppoAddress(&videoAddress);
	std::cout <<  "Video Address: " + videoAddress << "\n";

    return 0;
}
*/

int getVideoAddress(std::string *videoAddress) {
//what is my IP
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    
    getifaddrs(&ifAddrStruct);
	char *IPAddress = new char [16];
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            
			if (sizeof(addressBuffer) > 8 && !strstr(ifa->ifa_name, "lo") ) {
           	  	strcpy (IPAddress,addressBuffer);
			}			
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

// Concatenate
	std::string head = "rtmp://";
	std::string mid = IPAddress;
	std::string tail = ":1936/live/stream";
	*videoAddress = head + mid + tail;
     delete [] IPAddress;
//     return videoAddress;
	return 0;
}
