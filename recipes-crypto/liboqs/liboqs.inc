FILESEXTRAPATHS:prepend = "${THISDIR}/${PN}:"

DESCRIPTION = "C library for prototyping and experimenting with quantum-resistant cryptography"
SECTION = "crypto"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=4b93ef2da47496727a4e8a59f443844e"

ORG="open-quantum-safe"
BRANCH="0.10.1-release"
SRC_URI = "git://github.com/${ORG}/liboqs.git;protocol=https;branch=${BRANCH} \
	   file://run-ptest \
           file://01-check-installed-library.patch \
"

EXTRA_OECMAKE = " -DBUILD_SHARED_LIBS=ON -DOQS_DIST_BUILD=OFF -DOQS_DLOPEN_OPENSSL=OFF -DOQS_USE_OPENSSL=ON"

S = "${WORKDIR}/git"

DEPENDS = "openssl"

inherit pkgconfig cmake ptest

PTEST_ENABLED = "1"

do_install_ptest() {
    mkdir ${D}/${PTEST_PATH}/build
    cp ${WORKDIR}/run-ptest ${D}/${PTEST_PATH}
    cp -r ${B}/include ${D}/${PTEST_PATH}/build/include
    cp -r ${S}/src ${D}/${PTEST_PATH}/src
    cp -r ${S}/docs ${D}/${PTEST_PATH}/docs
    cp -r ${S}/scripts ${D}/${PTEST_PATH}/scripts
    cp -r ${S}/tests ${D}/${PTEST_PATH}/tests
    cp -r ${B}/tests ${D}/${PTEST_PATH}/build/tests
}

RDEPENDS:${PN}-ptest += "bash python3 python3-pytest python3-pytest-xdist binutils"
