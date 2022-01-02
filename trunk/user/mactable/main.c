#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/wireless.h>
#include "ralink_priv.h"
#include <stdio.h>

#define RTPRIV_IOCTL_GET_MAC_TABLE        0x8BEF
#define RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT 0x8BFF

int wl_ioctl(const char *ifname, int cmd, struct iwreq *pwrq)
{
	int ret = 0;
	int s;

	/* open socket to kernel */
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return errno;
	}

	/* do it */
	strncpy(pwrq->ifr_name, ifname, IFNAMSIZ);
	if ((ret = ioctl(s, cmd, pwrq)) < 0)
		perror(pwrq->ifr_name);

	/* cleanup */
	close(s);
	return ret;
}

void wl_list()
{
	char *ifname = 0;
	struct iwreq wrq;
	char mac_table_data[4096];

	ifname = "rai0";
	memset(mac_table_data, 0, sizeof(mac_table_data));
	wrq.u.data.pointer = mac_table_data;
	wrq.u.data.length = sizeof(mac_table_data);
	wrq.u.data.flags = 0;

	if (wl_ioctl(ifname, RTPRIV_IOCTL_GET_MAC_TABLE, &wrq) >= 0) {
		char *ptr = (char*)wrq.u.data.pointer;
		unsigned long count = *(int*)ptr;
		ptr += 4;

		for (int i = 0; i < count ; i ++) {
			RT_802_11_MAC_ENTRY *entry = (RT_802_11_MAC_ENTRY*)ptr;
			printf("%s\t%02X:%02X:%02X:%02X:%02X:%02X\t%d\t%d\t%d\n", ifname,
				   entry->Addr[0], entry->Addr[1], entry->Addr[2],
				   entry->Addr[3], entry->Addr[4], entry->Addr[5],
				   entry->AvgRssi0, entry->AvgRssi1, entry->AvgRssi2
			);
			ptr += 28;
		}
	}

	ifname = "ra0";
	memset(mac_table_data, 0, sizeof(mac_table_data));
	wrq.u.data.pointer = mac_table_data;
	wrq.u.data.length = sizeof(mac_table_data);
	wrq.u.data.flags = 0;
	if (wl_ioctl("ra0", RTPRIV_IOCTL_GET_MAC_TABLE, &wrq) >= 0) {
		char *ptr = (char*)wrq.u.data.pointer;
		unsigned long count = *(int*)ptr;
		ptr += 4;

		for (int i = 0; i < count ; i ++) {
			RT_802_11_MAC_ENTRY *entry = (RT_802_11_MAC_ENTRY*)ptr;
			printf("%s\t%02X:%02X:%02X:%02X:%02X:%02X\t%d\t%d\t%d\n", ifname,
				   entry->Addr[0], entry->Addr[1], entry->Addr[2],
				   entry->Addr[3], entry->Addr[4], entry->Addr[5],
				   entry->AvgRssi0, entry->AvgRssi1, entry->AvgRssi2
			);
			ptr += 28;
		}
	}
}

int main()
{
	wl_list();
	return 0;
}
