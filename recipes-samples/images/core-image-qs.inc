# Build up test image here
IMAGE_INSTALL += "\
        liboqs \
        liboqs-ptest \
        liboqs-tests \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

