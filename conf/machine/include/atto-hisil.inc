# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

KERNELVERSION = "4.4.35"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"
require conf/machine/include/arm/armv7a/tune-cortexa15.inc

require conf/machine/include/soc-family.inc

IMAGE_FSTYPES += "tar.bz2 img"

CMDLINE ?= "console=ttyAMA0,115200n8"

PREFERRED_PROVIDER_virtual/kernel = "linux-atto"
PREFERRED_VERSION_linux-atto = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

KERNEL_FILE = "boot.img"
ROOTFS_FILE = "e2d-armhf-pixel.img"
MTD_BLACK  = "mmcblk0"
MTD_KERNEL = "mmcblk0p11"
MTD_ROOTFS = "mmcblk1"

SDCARDIMG = "no"

BOX_BRAND = "atto"

DISPLAY_BRAND = "Atto.TV"

EXTRA_OECONF:append_pn-enigma2 = "--with-lcddev=/dev/null --with-alphablendingacceleration=always"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += "hdmicec blindscan-tbs alsa multitranscoding hisil HDMI eDBoxLCD 7segment textlcd bluetooth"

RCNAME = "hdbox"

#EXTRA_ALSA = "mv200"

IMAGE_CLASSES  += "atto-emmc_image"
IMAGE_FSTYPES += "attoemmc"
IMAGE_ROOTFS_SIZE ?= "589824"

MACHINE_FEATURES += "emmc mmc"

IMAGE_CMD:attoemmc:append = " \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	if [ "${SDCARDIMG}" = "yes" ]; then \
		mv -f ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.emmc.img ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${IMAGE_NAME}.sdcard.img; \
	else \
		rm -f ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.emmc.img; \
	fi; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD:prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGEDIR = "atto/${MACHINE}"
