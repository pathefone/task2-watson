include $(TOPDIR)/rules.mk

PKG_NAME:=rutx-watson
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/rutx-watson
	CATEGORY:=Base system
	TITLE:=rutx-watson
	DEPENDS:=+libiotwatson +libubus +libubox +libblobmsg-json +libuci
endef

define Package/rutx-watson/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rutx-watson $(1)/usr/bin
	$(INSTALL_BIN) ./files/rutx-watson.init $(1)/etc/init.d/rutx-watson
	$(INSTALL_CONF) ./files/rutx-watson.conf $(1)/etc/config/rutx-watson
endef

$(eval $(call BuildPackage,rutx-watson))
