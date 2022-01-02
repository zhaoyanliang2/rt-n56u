all:

romfs:
	cp lib/libm-0.9.33.2.so         $(ROMFSDIR)/lib/libm-0.9.33.2.so
	ln -s /lib/libm-0.9.33.2.so     $(ROMFSDIR)/lib/libm.so.0
	cp usr/sbin/bwmon               $(ROMFSDIR)/usr/sbin/bwmon
	chmod 777                       $(ROMFSDIR)/usr/sbin/bwmon
	mkdir                           $(ROMFSDIR)/www/bwmon
	cp www/bwmon/bwmon.css          $(ROMFSDIR)/www/bwmon/bwmon.css
	ln -s /tmp/bwmon/usage_stats.js $(ROMFSDIR)/www/bwmon/usage_stats.js
	cp www/Main_BWMon.asp           $(ROMFSDIR)/www/Main_BWMon.asp
	unlink                          $(ROMFSDIR)/www/state.js
	cp www/state.js                 $(ROMFSDIR)/www/state.js

clean:
