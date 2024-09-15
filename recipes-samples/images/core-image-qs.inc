# Build up test image here
IMAGE_INSTALL += "\
        liboqs \
        liboqs-tests \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

