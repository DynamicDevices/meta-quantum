DESCRIPTION = "C library for prototyping and experimenting with quantum-resistant cryptography"
SECTION = "crypto"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=4b93ef2da47496727a4e8a59f443844e"

EXTRA_OECMAKE = " -DBUILD_SHARED_LIBS=ON -DOQS_DIST_BUILD=OFF -DOQS_DLOPEN_OPENSSL=OFF"
#EXTRA_OECMAKE += " -DOQS_USE_OPENSSL=${@bb.utils.contains('DISTRO_FEATURES', 'openssl', ' -DOQS_USE_OPENSSL=ON', ' -DOQS_USE_OPENSSL=OFF', d)}"
# Force OpenSSL ON
EXTRA_OECMAKE += " -DOQS_USE_OPENSSL=ON"

S = "${WORKDIR}/git"

PACKAGE_BEFORE_PN = "${PN}-tests"
FILES:${PN}-tests = "${bindir}/*"
RPROVIDES:${PN} += "${PN}-tests"
RDEPENDS:${PN} += "${PN}-tests"

DEPENDS = "openssl"

inherit pkgconfig cmake ptest

RDEPENDS:${PN}-ptest += "${PN}-tests"
