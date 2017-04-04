#ifndef __includes_h__
#define __includes_h__
#include "common.h"
#include <execinfo.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <future>
#include <time.h>
#include <signal.h>
#include <dlfcn.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <math.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include<netdb.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<sys/socket.h>
#include<net/if.h>
#include<net/ethernet.h>
#include<netinet/in.h>
#include<sys/ioctl.h>
#include<sys/ipc.h>
#include <sys/stat.h>


#define TCP_SOCKET_WRITE_BUFFER_SIZE    1024*1024*10
#define TCP_SOCKET_READ_BUFFER_SIZE         1024*1024*10
#define RAW_SOCKET_BUFFER_SIZE                                          65536
#define SOCKET_READ_BUFFER_SIZE         1024*1024*10
#define SOCKET_WRITE_BUFFER_SIZE        1024*1024*10
#define TCP_SOCKET_WRITE_BUFFER_SIZE    1024*1024*10
#define TCP_SOCKET_READ_BUFFER_SIZE     1024*1024*10
#define MULTICAST_GROUP_PORT            3333
#define USER_MULTICAST_GROUP_PORT       4444
#define MULTICAST_PACKET_SIZE           8000
#define BAG_WAIT                        10
#define MINIMUM_WRITE_WAIT              100
#define SECONDARY_WRITE_WAIT_DELTA      100
#define WRITE_WAIT_DELTA                1000
#define INITIAL_WRITE_WAIT              1
#define MAX_CONSTELLATION_SIZE              60
#define PAGE_RENDER_MODE_FLATTENED              100
#define PAGE_RENDER_MODE_NOT_FLATTENED          200
#define PAGE_RENDER_MODE_BOTH                   300
#define MAX_LOOP                                10000
#define STRING_NODE_TYPE                        'S'
#define SHORT_NODE_TYPE                         'H'
#define INTEGER_NODE_TYPE                       'I'
#define LONG_NODE_TYPE                          'l'
#define FLOAT_NODE_TYPE                         'F'
#define DOUBLE_NODE_TYPE                        'D'
#define CHAR_NODE_TYPE                          'C'
#define BOOL_NODE_TYPE                          'B'
#define BYTE_NODE_TYPE                          'Y'
#define LIST_NODE_TYPE                          'L'
#define XML_NODE_TYPE                           'X'
#define VOID_NODE_TYPE                          'V'
#define SERVICE_NODE_TYPE                       's'
#define SHARED_LIB_NODE_TYPE                    'r'

#endif


//~ Formatted by Jindent --- http://www.jindent.com
