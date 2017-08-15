//
//  lwIP.h
//  ZPTCPIPStack
//
//  Created by ZapCannon87 on 11/08/2017.
//  Copyright © 2017 zapcannon87. All rights reserved.
//

#ifndef lwIP_h
#define lwIP_h

#import <netinet/in.h>

#include "lwip/tcp.h"
#include "lwip/prot/tcp.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/inet_chksum.h"
#include "lwip/ip4_frag.h"
#include "lwip/ip6_frag.h"

#if LWIP_IPV4 && LWIP_IPV6
/** @ingroup socket */
#define inet_ntop(af,src,dst,size) \
(((af) == AF_INET6) ? ip6addr_ntoa_r((const ip6_addr_t*)(src),(dst),(size)) \
: (((af) == AF_INET) ? ip4addr_ntoa_r((const ip4_addr_t*)(src),(dst),(size)) : NULL))
/** @ingroup socket */
#define inet_pton(af,src,dst) \
(((af) == AF_INET6) ? ip6addr_aton((src),(ip6_addr_t*)(dst)) \
: (((af) == AF_INET) ? ip4addr_aton((src),(ip4_addr_t*)(dst)) : 0))
#elif LWIP_IPV4 /* LWIP_IPV4 && LWIP_IPV6 */
#define inet_ntop(af,src,dst,size) \
(((af) == AF_INET) ? ip4addr_ntoa_r((const ip4_addr_t*)(src),(dst),(size)) : NULL)
#define inet_pton(af,src,dst) \
(((af) == AF_INET) ? ip4addr_aton((src),(ip4_addr_t*)(dst)) : 0)
#else /* LWIP_IPV4 && LWIP_IPV6 */
#define inet_ntop(af,src,dst,size) \
(((af) == AF_INET6) ? ip6addr_ntoa_r((const ip6_addr_t*)(src),(dst),(size)) : NULL)
#define inet_pton(af,src,dst) \
(((af) == AF_INET6) ? ip6addr_aton((src),(ip6_addr_t*)(dst)) : 0)
#endif /* LWIP_IPV4 && LWIP_IPV6 */

struct tcp_info {
    
    struct tcp_pcb *pcb;
    
    struct ip_globals ip_data;
    
    struct tcp_hdr *tcphdr;
    u16_t tcphdr_optlen;
    u16_t tcphdr_opt1len;
    u8_t* tcphdr_opt2;
    u32_t seqno;
    u32_t ackno;
    u16_t tcplen;
    u8_t  flags;
    
    u32_t tcp_ticks;
    
    u16_t tcp_optidx;
    
    struct tcp_seg inseg;
    struct pbuf    *recv_data;
    u8_t           recv_flags;
    tcpwnd_size_t  recv_acked;
    
};

void tcp_input_pre(struct pbuf *p, struct netif *inp);

#endif /* lwIP_h */
