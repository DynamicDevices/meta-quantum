DESCRIPTION = "C library for prototyping and experimenting with quantum-resistant cryptography"
SECTION = "crypto"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=4b93ef2da47496727a4e8a59f443844e"

SRC_URI = "git://github.com/open-quantum-safe/liboqs.git;protocol=https;branch=0.10.1-release"
SRCREV = "306140ebb577180e7bc704714e82949f7b9d33cf"

EXTRA_OECMAKE += " -DBUILD_SHARED_LIBS=ON -DOQS_DIST_BUILD=OFF -DOQS_USE_OPENSSL=OFF"

S = "${WORKDIR}/git"

PACKAGES += "${PN}-tests"
FILES:${PN}-tests = "/tests/"
RPROVIDES:${PN} += "${PN}-tests"
RDEPENDS:${PN} += "${PN}-tests"

inherit pkgconfig cmake
