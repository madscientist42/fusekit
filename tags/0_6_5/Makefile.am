ACLOCAL_AMFLAGS = -I m4
SUBDIRS = include example
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE_NAME@.pc
EXTRA_DIST = debian
TMP_DIR = tmp
DEBIAN_PACKAGE_DIR = pkg

pkg-deb: dist
	- rm -rf  $(TMP_DIR)
	mkdir -p $(TMP_DIR)
	test -e $(PWD)/$(DEBIAN_PACKAGE_DIR) || mkdir $(PWD)/$(DEBIAN_PACKAGE_DIR)
	mv $(PACKAGE)-$(VERSION).tar.gz $(TMP_DIR)/
	tar --directory $(TMP_DIR)/ -xf $(TMP_DIR)/$(PACKAGE)-$(VERSION).tar.gz
	cd $(TMP_DIR)/$(PACKAGE)-$(VERSION)/ ; \
	./configure ; \
	dpkg-buildpackage -us -uc -rfakeroot ; \
	mv ../*.deb $(PWD)/$(DEBIAN_PACKAGE_DIR)/ 
	rm -rf $(TMP_DIR)

